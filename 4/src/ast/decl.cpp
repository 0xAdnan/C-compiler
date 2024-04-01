//
// Created by satyam on 29/3/24.
//

#include "decl.h"


ASTInitDecl::ASTInitDecl(ASTIDDecl * id): ASTNode() {
  this->name = id->name;
  this->num_ptr = id->num_ptrs;
}

ASTInitDecl::ASTInitDecl(ASTIDDecl * id, ASTExpr* expr): ASTNode(){
  this->name = id->name;
  this->value = expr;
  this->num_ptr = id->num_ptrs;

  if(this->value != nullptr)
    children.push_back(this->value);
}

ASTInitDecl::ASTInitDecl(ASTFnDecl * fnDecl) {
  this->name = fnDecl->name;
  this->value = nullptr;
  this->fnDecl = fnDecl;

  this->num_ptr = fnDecl->num_ptrs;
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
    decl->fnDecl = init->fnDecl;
    declarations.push_back(decl);
    children.push_back(decl);
  }
}

ASTParamDecl::ASTParamDecl(ASTDeclSpec * declSpec, ASTIDDecl * id) {
  this->type = declSpec->type;
  this->is_const = declSpec->is_const;
  this->name = id->name;
  this->num_ptr = id->num_ptrs;
}

ASTParamDecl::ASTParamDecl(ASTDeclSpec * declSpec) {
  this->type = declSpec->type;
  this->is_const = declSpec->is_const;

}


ASTParamList::ASTParamList(ASTParamList * paramList, ASTParamDecl * paramDecl) {
  for(auto x: paramList->params)
    params.push_back(x);
  params.push_back(paramDecl);
}

ASTParamList::ASTParamList(ASTParamDecl * x) {
  params.push_back(x);
}

