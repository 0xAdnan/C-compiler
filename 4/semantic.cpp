#include "ast.hpp"
#include "magic_enum.hpp"
#include <llvm-19/llvm/IR/LLVMContext.h>
#include <llvm-19/llvm/IR/Value.h>
#include <unordered_map>

void SymbolInfo::add_value(ASTConst *constNode) {
  switch (constNode->ct) {
  case const_type::i_const:
    value = constNode->value_i;
    break;
  case const_type::f_const:
    value = constNode->value_f;
    break;
  }
}

/************************************************************************/
/*                               Utilites                               */
/************************************************************************/
void unexpected_tree(string node_name) {
  printf("Unexpected Tree Structure: %s\n", node_name.c_str());
  exit(1);
}

/*                               Declaration Utils                       */
map<string, SymbolInfo> ASTDecl::get_variables() const {
  map<string, SymbolInfo> variables;

  auto typeNode = dynamic_cast<ASTType *>(this->children[0]);
  if (typeNode == nullptr)
    unexpected_tree(this->to_str());

  ttype variableType = typeNode->t;

  for (auto it = children.begin() + 1; it != children.end(); ++it) {
    if (auto idNode = dynamic_cast<ASTId *>(*it)) {
      SymbolInfo si;
      si.type_ = variableType;
      /* si.value = cg->create_alloca(idNode->name, variableType); */
      /* si.value = cg->createGlobalVariable(idNode->name, variableType); */
      si.value = nullptr;
      variables[idNode->name] = si;
    } else if (auto initDecl = dynamic_cast<ASTInitDecl *>(*it)) {
      auto idNode = dynamic_cast<ASTId *>(initDecl->children[0]);
      auto constNode =
          dynamic_cast<ASTConst *>(initDecl->children[1]->children[0]);
      if (idNode == nullptr || constNode == nullptr)
        unexpected_tree(this->to_str());

      SymbolInfo si;
      si.type_ = variableType;
      si.add_value(constNode);
      /* si.value = cg->create_alloca(idNode->name, variableType); */

      variables[idNode->name] = si;
    } else if (auto initDeclList = dynamic_cast<ASTInitDeclList *>(*it)) {
      for (auto *child : initDeclList->children) {
        if (auto *idNode = dynamic_cast<ASTId *>(child)) {
          SymbolInfo si;
          si.type_ = variableType;
          /* si.value = cg->create_alloca(idNode->name, variableType); */
          /* si.value = cg->createGlobalVariable(idNode->name, variableType); */
        } else if (auto *initDecl = dynamic_cast<ASTInitDecl *>(child)) {
          if (!initDecl->children.empty()) {
            if (auto *idNode = dynamic_cast<ASTId *>(initDecl->children[0])) {
              string varName = idNode->name;
              if (initDecl->children.size() > 1) {
                if (auto *constNode = dynamic_cast<ASTConst *>(
                        initDecl->children[1]->children[0])) {
                  SymbolInfo si;
                  si.type_ = variableType;
                  si.add_value(constNode);
                  /* si.value = cg->create_alloca(varName, variableType); */
                  variables[varName] = si;
                } else {
                  SymbolInfo si;
                  si.type_ = variableType;
                  /* si.value = cg->create_alloca(varName, variableType); */
                  /* si.value = cg->createGlobalVariable(varName,
                   * variableType);*/
                  si.add_value(constNode);
                  variables[varName] = si;
                }
              } else {
                SymbolInfo si;
                si.type_ = variableType;
                /* si.value = cg->create_alloca(varName, variableType); */
                /* si.value = cg->createGlobalVariable(varName, variableType);
                 */
                variables[varName] = si;
              }
            }
          }
        }
      }
    } else {
      unexpected_tree(this->to_str());
    }
  }
  return variables;
}

string ASTParamDecl::get_var_name() const {
  if (children.size() >= 1) {
    ASTId *id = dynamic_cast<ASTId *>(children[1]);
    if (id != nullptr)
      return id->name;
    ASTIdDeclarator *idDecl = dynamic_cast<ASTIdDeclarator *>(children[1]);
    if (idDecl != nullptr) {
      ASTId *id = dynamic_cast<ASTId *>(idDecl->children[1]);
      if (id != nullptr)
        return id->name;
    }
  }
  unexpected_tree("ASTParamDecl");
}

ttype ASTParamDecl::get_type() const {
  if (children.size() >= 1) {
    ASTType *t = dynamic_cast<ASTType *>(children[0]);
    if (t == NULL) {
      cout << "Not supporting long long yet" << endl;
      exit(1);
    }
    return t->t;
  }
  cout << "Error Happened" << endl;
  exit(1);
}
pair<bool, unordered_map<string, SymbolInfo>>
ASTParamList::get_variables() const {
  unordered_map<string, SymbolInfo> variables = {};

  for (auto child : children) {
    ASTParamDecl *pd = dynamic_cast<ASTParamDecl *>(child);
    string var_name = pd->get_var_name();
    ttype var_type = pd->get_type();
    if (variables.find(var_name) == variables.end()) {
      SymbolInfo si;
      si.type_ = var_type;
      si.value = nullptr;
      variables[var_name] = si;
    } else
      return make_pair(false, unordered_map<string, SymbolInfo>{});
  }

  return make_pair(true, variables);
}

pair<bool, unordered_map<string, SymbolInfo>>
ASTFnDeclarator::get_variables() const {
  if (this->children.size() == 1)
    return make_pair(true, unordered_map<string, SymbolInfo>{});

  ASTParamList *pl = dynamic_cast<ASTParamList *>(this->children[1]);
  return pl->get_variables();
}
bool ASTNode::semantic_action_start(SemanticAnalyzer *sa) const { return true; }

bool ASTNode::semantic_action_end(SemanticAnalyzer *sa) const { return true; }

bool ASTDecl::semantic_action_start(SemanticAnalyzer *sa) const {
  map<string, SymbolInfo> variables = this->get_variables();
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
  pair<bool, unordered_map<string, SymbolInfo>> variables =
      this->get_variables();
  if (!variables.first)
    return false;
  for (const auto &var : variables.second) {
    if (!sa->add_variable(var.first, var.second))
      return false;
  }
  return true;
}

bool ASTBlockItemList::semantic_action_start(SemanticAnalyzer *sa) const {
  auto prev_symbols = map<string, SymbolInfo>{};
  if (sa->peek()->context == "FunctionDeclarator") {
    prev_symbols = sa->peek()->table;
    sa->exit_scope();
  }

  sa->enter_scope(this->to_str());
  for (auto vt : prev_symbols) {
    if (!sa->add_variable(vt.first, vt.second))
      return false;
  }
  return true;
}

bool ASTBlockItemList::semantic_action_end(SemanticAnalyzer *sa) const {
  sa->exit_scope();
  return true;
}

bool ASTForStmt::semantic_action_start(SemanticAnalyzer *sa) const {
  sa->enter_scope("ForLoop");
  return true;
};
bool ASTForStmt::semantic_action_end(SemanticAnalyzer *sa) const {
  sa->exit_scope();
  return true;
};

/* Semantic Analyzer */
bool SemanticAnalyzer::analyze(ASTProgram *p) {
  enter_scope("Root");
  bool result = analyze_node(p);
  exit_scope();

  cg->emit();
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

bool SemanticAnalyzer::add_variable(string variable, SymbolInfo si) {
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
  si.num_occurrence = totalDeclarations + 1;
  currentScopeTable[variable] = si;

  llvm::Value *llvmVal;
  if (symbol_table.back().context == "Root")
    llvmVal = cg->createGlobalVariable(variable, si.type_, si.value);
  else
    llvmVal = cg->create_alloca(variable, si.type_, si.value);

  return true;
}

SymbolTable *SemanticAnalyzer::peek() { return &this->symbol_table.back(); }
