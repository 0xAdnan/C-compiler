#include "ast.hpp"
#include "magic_enum.hpp"

bool ASTNode::semantic_action_start(SemanticAnalyzer *sa) const { return true; }

bool ASTNode::semantic_action_end(SemanticAnalyzer *sa) const { return true; }

bool ASTDecl::semantic_action_start(SemanticAnalyzer *sa) const {
  unordered_map<string, ttype> variables = this->get_variables();
  for (const auto &var : variables) {
    sa->add_variable(var.first, var.second);
  }
  return true;
}

bool ASTFnDeclarator::semantic_action_start(SemanticAnalyzer *sa) const {
  sa->enter_scope();
  pair<bool, unordered_map<string, ttype>> variables = this->get_variables();
  if (!variables.first)
    return false;
  for (const auto &var : variables.second) {
    sa->add_variable(var.first, var.second);
  }
  return true;
}

bool ASTFnDeclarator::semantic_action_end(SemanticAnalyzer *sa) const {
  sa->exit_scope();
  return true;
}

bool ASTBlockItemList::semantic_action_start(SemanticAnalyzer *sa) const {
  sa->enter_scope();
  return true;
}

bool ASTBlockItemList::semantic_action_end(SemanticAnalyzer *sa) const {
  sa->exit_scope();
  return true;
}

/* Semantic Analyzer */

bool SemanticAnalyzer::analyze(ASTProgram *p) {
  enter_scope();
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
  for (auto it = symbol_table.rbegin(); it != symbol_table.rend(); ++it) {
    if (it->find(variable) != it->end()) {
      return true;
    }
  }
  return false;
};

bool SemanticAnalyzer::find_all(string variable) {
  for (auto it = symbol_table.rbegin(); it != symbol_table.rend(); ++it) {
    if (it->find(variable) != it->end()) {
      return true;
    }
  }
  return false;
};

void SemanticAnalyzer::enter_scope() { symbol_table.push_back({}); }

void SemanticAnalyzer::exit_scope() {
  if (!symbol_table.empty()) {
    cout << "Before exiting: " << endl;
    for (const auto &symbol_map : symbol_table) {
      for (const auto &entry : symbol_map) {
        string t_str = string(magic_enum::enum_name(entry.second).data());
        cout << entry.first << " : " << t_str << endl;
      }
    }
    symbol_table.pop_back();
  }
}

bool SemanticAnalyzer::add_variable(string variable, ttype type) {
  if (!symbol_table.empty()) {
    symbol_table.back()[variable] = type;
    return true;
  } else {
    return false;
  }
}
