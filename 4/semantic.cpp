#include "ast.hpp"
#include "magic_enum.hpp"
#include <unordered_map>

bool ASTNode::semantic_action_start(SemanticAnalyzer *sa) const { return true; }

bool ASTNode::semantic_action_end(SemanticAnalyzer *sa) const { return true; }

bool ASTDecl::semantic_action_start(SemanticAnalyzer *sa) const {
  unordered_map<string, ttype> variables = this->get_variables();
  for (const auto &var : variables) {
    if (!sa->add_variable(var.first, var.second))
      return false;
  }
  return true;
}

vector<string> ASTExpr::get_referred_vars() const {
  vector<string> referredVars;

  for (const auto *child : this->children) {
    if (const auto *idNode = dynamic_cast<const ASTId *>(child)) {
      referredVars.push_back(idNode->name);
    } else if (const auto *exprNode = dynamic_cast<const ASTExpr *>(child)) {
      vector<string> childReferredVars = exprNode->get_referred_vars();
      referredVars.insert(referredVars.end(), childReferredVars.begin(),
                          childReferredVars.end());
    }
  }

  return referredVars;
}

bool ASTExpr::semantic_action_start(SemanticAnalyzer *sa) const {
  vector<string> referred_vars = get_referred_vars();
  for (auto var : referred_vars) {
    if (!sa->find_all(var))
      return false;
  }
  return true;
}

bool ASTFnDeclarator::semantic_action_start(SemanticAnalyzer *sa) const {
  sa->enter_scope(this->to_str());
  pair<bool, unordered_map<string, ttype>> variables = this->get_variables();
  if (!variables.first)
    return false;
  for (const auto &var : variables.second) {
    if (!sa->add_variable(var.first, var.second))
      return false;
  }
  return true;
}

bool ASTBlockItemList::semantic_action_start(SemanticAnalyzer *sa) const {
  auto prev_symbols = unordered_map<string, SymbolInfo>{};
  if (sa->peek()->context == "FunctionDeclarator") {
    prev_symbols = sa->peek()->table;
    sa->exit_scope();
  }

  sa->enter_scope(this->to_str());
  for (auto vt : prev_symbols) {
    if (!sa->add_variable(vt.first, vt.second.type_))
      return false;
  }
  return true;
}

bool ASTBlockItemList::semantic_action_end(SemanticAnalyzer *sa) const {
  sa->exit_scope();
  return true;
}

/* Semantic Analyzer */

bool SemanticAnalyzer::analyze(ASTProgram *p) {
  enter_scope("Root");
  bool result = analyze_node(p);
  exit_scope();
  return result;
}

bool SemanticAnalyzer::analyze_node(ASTNode *node) {
  if (node == nullptr)
    return true;

  if (!node->semantic_action_start(this))
    return false;

  for (auto &child : node->children) {
    if (!analyze_node(child))
      return false;
  }

  if (!node->semantic_action_end(this))
    return false;

  return true;
};

bool SemanticAnalyzer::find(string variable) {
  return symbol_table.back().table.find(variable) !=
         symbol_table.back().table.end();
};

bool SemanticAnalyzer::find_all(string variable) {
  for (auto it = symbol_table.rbegin(); it != symbol_table.rend(); ++it) {
    if (it->table.find(variable) != it->table.end()) {
      return true;
    }
  }
  return false;
};

void SemanticAnalyzer::enter_scope(string context) {
  symbol_table.push_back(SymbolTable{context, {}});
}

void SemanticAnalyzer::exit_scope() {
  if (!symbol_table.empty()) {
    cout << "Symbol Table before exiting: " << symbol_table.back().context
         << endl;
    for (const auto &entry : symbol_table.back().table) {
      string t_str = string(magic_enum::enum_name(entry.second.type_).data());
      cout << entry.first << " : " << t_str
           << ", Count: " << entry.second.num_occurrence
           << ", Pointer: " << entry.second.ptr
           << ", IsConst: " << entry.second.is_const << endl;
    }
    symbol_table.pop_back();
  }
}

bool SemanticAnalyzer::add_variable(string variable, ttype type, int ptr,
                                    bool is_const) {
  auto &currentScopeTable = symbol_table.back().table;
  auto it = currentScopeTable.find(variable);
  if (it != currentScopeTable.end())
    return false;

  int totalDeclarations = 0;

  for (const auto &scope : symbol_table) {
    auto var_found = scope.table.find(variable);
    if (var_found != scope.table.end()) {
      totalDeclarations =
          max(totalDeclarations, var_found->second.num_occurrence);
    }
  }
  currentScopeTable[variable] = {type, ptr, is_const, totalDeclarations + 1};
  return true;
}

SymbolTable *SemanticAnalyzer::peek() { return &this->symbol_table.back(); }
