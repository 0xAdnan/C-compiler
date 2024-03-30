//
// Created by satyam on 29/3/24.
//

#ifndef CCOMPILER_DECL_H
#define CCOMPILER_DECL_H

#include "string"
#include "enums.h"
#include "base.h"
#include "expr.h"
#include "../../magic_enum.hpp"

using namespace std;


/* Type and const part of the declaration "__const int__ x = 1" */
class ASTDeclSpec: public ASTNode{
public:
    ctype_ type;
    bool is_const;
    ASTDeclSpec(ctype_, bool);

    string to_str() const override{
      return "DeclarationSpecifier";
    }
};


/* Identifier part of the declaration "int __*x__ = " */
class ASTDeclarator: public ASTNode{
public:
    int num_ptrs = 0;
    void add_ptr(){num_ptrs++;}
    ASTDeclarator():ASTNode(){}

    string to_str() const override{
      return "Declarator: num_ptrs= " + to_string(num_ptrs);
    }
};

/* Variable Identifier*/
class ASTIDDecl: public ASTDeclarator {
public:
    string name;
    ASTIDDecl(string name): ASTDeclarator(){
      this->name = name;
    }

    string to_str() const override{
      return "IdDeclarator: " + this->name ;
    }
};

/* Function Identifier "int __f(int, int, bool)__" */
class ASTParamTypeList;

class ASTFnDecl: public ASTDeclarator {
public:
    string name;
    ASTParamTypeList* params = nullptr;

    ASTFnDecl(ASTIDDecl* id): ASTDeclarator(){
      this->name = id->name;
    }

    ASTFnDecl(ASTIDDecl* id, ASTParamTypeList* params): ASTDeclarator(){
      this->name = id->name;
      this->params = params;
    }

    string to_str() const override{
      return "IdDeclarator: " + this->name ;
    }
};

/* Rhs of the initialization "int x = _1_;" */
class ASTInitializer: public ASTNode{
public:
    ASTExpr* expr;
    ASTInitializer(ASTExpr* expr){
      this->expr = expr; children.push_back(expr);
    }

    string to_str() const override{
      return "Initializer";
    }
};

/* Rhs of the initialization "int x = __1__;" */
class ASTInitDecl: public ASTNode{
public:
    string name;
    ASTExpr* value = nullptr;
    int num_ptr = 0;
    bool is_fn = false;

    explicit ASTInitDecl(ASTIDDecl*);
    explicit ASTInitDecl(ASTFnDecl*);
    ASTInitDecl(ASTIDDecl*, ASTInitializer*);

    string to_str() const override{
      return "InitDecl";
    }
};

class ASTInitDeclList: public ASTNode{
public:
    ASTInitDeclList(ASTInitDecl*);
    ASTInitDeclList(ASTInitDeclList*, ASTInitDecl*);
    vector<ASTInitDecl*> initializations;

    string to_str() const override{
      return "InitDeclList";
    }
};

// CODEGEN VISIT
class ASTDecl: public ASTNode{
public:
    string name;
    ctype_ type;
    ASTExpr* value = nullptr;
    bool is_const = false;
    int num_ptr = 0;
    bool is_fn = false;

    ASTDecl(string name, ctype_ type): ASTNode(){
      this->name = name;
      this->type = type;
    }

    string to_str() const override{
      if(is_const)
        return "Declaration: " + name + ", type: " + to_string(type) + ", is_const: True, num_ptr: " + to_string(num_ptr);
      return "Declaration: " + name + ", type: " + to_string(type) + ", is_const: False, num_ptr: " + to_string(num_ptr);
    }
};

class ASTDeclList: public ASTNode{
public:
    ASTDeclList(ASTDeclSpec* n1, ASTInitDeclList* n2);
    vector<ASTDecl*> declarations;

    string to_str() const override{
      return "DeclarationList";
    }
};

class ASTParam: ASTNode{

};

class ASTParamList: ASTNode{
public:
    vector<ASTParam*> params;
};

class ASTParamTypeList: ASTNode{
public:
    ASTParamList* paramList;
    bool is_variadic = false;

    ASTParamTypeList(ASTParamList* params): ASTNode(){
      this->paramList = params;
    }
};

#endif //CCOMPILER_DECL_H
