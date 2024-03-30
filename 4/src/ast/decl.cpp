//
// Created by satyam on 29/3/24.
//

#include "decl.h"

ASTDeclSpec::ASTDeclSpec(ctype_ type, bool is_const) : ASTNode() {
  this->type = type;
  this->is_const = is_const;
}


ASTInitDecl::ASTInitDecl(ASTIDDecl * id): ASTNode() {
  this->name = id->name;
}

ASTInitDecl::ASTInitDecl(ASTIDDecl * id, ASTInitializer* init): ASTNode(){
  this->name = id->name;
  this->value = init->expr;

  if(this->value != nullptr)
    children.push_back(this->value);
}

ASTInitDecl::ASTInitDecl(ASTFnDecl * fnDecl) {
  this->name = fnDecl->name;
  this->value = nullptr;
  this->is_fn = true;
}


ASTInitDeclList::ASTInitDeclList(ASTInitDecl * n): ASTNode(){
  initializations.push_back(n);
}

ASTInitDeclList::ASTInitDeclList(ASTInitDeclList* n1, ASTInitDecl * n2): ASTNode(){
  for(auto x: n1->initializations)
    initializations.push_back(x);
  initializations.push_back(n2);
}

ASTDeclList::ASTDeclList(ASTDeclSpec *n1, ASTInitDeclList *n2): ASTNode(){
  for(auto init: n2->initializations){
    auto decl = new ASTDecl(init->name, n1->type);
    decl->value = init->value;
    decl->is_const = n1->is_const;
    decl->num_ptr = init->num_ptr;
    decl->is_fn = init->is_fn;
    declarations.push_back(decl);
    children.push_back(decl);
  }
}