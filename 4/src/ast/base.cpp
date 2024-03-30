//
// Created by satyam on 29/3/24.
//

#include "base.h"


void ASTNode::add_child(ASTNode *child) {
  this->children.push_back(child);
}


void ASTNode::dump_ast(int indent) {
  auto myindent = indent;
  bool has_children = this->children.size() > 0;

  for (int i = 0; i < myindent; i++)
    cout << "    ";

  cout << this->to_str();

  if (has_children) {
    cout << "[Children: " << children.size() << "]  {" << endl;
    auto child_indent = indent + 1;
    for (auto child : children) {
      if (child != nullptr)
        child->dump_ast(child_indent);
    }
    for (int i = 0; i < myindent; i++)
      cout << "    ";
    cout << "}";
  }

  cout << endl;
}

void ASTNode::accept(Visitor *visitor){
  for(auto child: children)
    child->accept(visitor);
}

