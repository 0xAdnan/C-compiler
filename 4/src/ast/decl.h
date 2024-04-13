//
// Created by satyam on 29/3/24.
//

#ifndef CCOMPILER_DECL_H
#define CCOMPILER_DECL_H

#include <llvm/Support/raw_ostream.h>
#include "string"

#include "base.h"
#include "expr.h"
#include "SemanticException.h"

using namespace std;


/* Type and const part of the declaration "__const int__ x = 1" */
class ASTDeclSpec: public ASTNode{
public:
    ctype_ type;
    bool is_const = false;

    ASTDeclSpec(){}

    ASTDeclSpec(ctype_ t){
       type = t;
    }

    ASTDeclSpec(ctype_ t, ASTDeclSpec* declSpec){
      if(!(declSpec->type == t_long && t == t_long)){
        string msg = "Only supporting 'long' and 'long long'";
        llvm::errs() << msg << "\n";
        assert(false);
      }
      type = t_long_long;
    }

    [[nodiscard]] string to_str() const override{
      return "DeclarationSpecifier";
    }
};


/* Identifier part of the declaration "int __*x__ = " */
class ASTDeclarator: public ASTNode{
public:
    int num_ptrs = 0;
    ASTDeclarator():ASTNode(){}

    [[nodiscard]] string to_str() const override{
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

    [[nodiscard]] string to_str() const override{
      return "IdDeclarator: " + this->name ;
    }
};

class ASTParamDecl: public ASTNode{
public:
    ctype_ type;
    string name;
    bool is_const = false;
    int num_ptr = 0;

    ASTParamDecl(ASTDeclSpec*, ASTIDDecl*);
    explicit ASTParamDecl(ASTDeclSpec*);

    [[nodiscard]] string to_str() const override {
      if(is_const)
        return to_string(type) + " " + name + " const " + to_string(num_ptr);
      return to_string(type) + " " + name + " " + to_string(num_ptr);
    }
};

class ASTParamList: public ASTNode{
public:
    vector<ASTParamDecl*> params;

    explicit ASTParamList(ASTParamDecl*);
    ASTParamList(ASTParamList*, ASTParamDecl*);


    [[nodiscard]] string to_str() const {
      return "Parameters";
    }
};

class ASTParamTypeList: public ASTNode{
public:
    ASTParamList* paramList;
    bool is_variadic = false;

    explicit ASTParamTypeList(ASTParamList* params): ASTNode(){
      this->paramList = params;
      children.push_back(paramList);
    }

    [[nodiscard]] string to_str() const override {
      return "ParameterDecls";
    }
};
/* Function Identifier "int __f(int, int, bool)__" */

class ASTFnDecl: public ASTDeclarator {
public:
    string name;
    ASTParamTypeList* params = nullptr;

    explicit ASTFnDecl(ASTIDDecl* id): ASTDeclarator(){
      this->name = id->name;
    }

    ASTFnDecl(ASTIDDecl* id, ASTParamTypeList* params): ASTDeclarator(){
      this->name = id->name;
      this->params = params;
      children.push_back(params);
    }

    [[nodiscard]] string to_str() const override{
      return "FnDecl: " + this->name ;
    }
};

/* Rhs of the initialization "int x = __1__;" */
class ASTInitDecl: public ASTNode{
public:
    string name;
    ASTExpr* value = nullptr;
    int num_ptr = 0;
    ASTFnDecl* fnDecl = nullptr;

    explicit ASTInitDecl(ASTIDDecl*);
    explicit ASTInitDecl(ASTFnDecl*);
    ASTInitDecl(ASTIDDecl*, ASTExpr*);

    [[nodiscard]] string to_str() const override{
      return "InitDecl: num_ptrs=" + to_string(num_ptr);
    }
};

class ASTInitDeclList: public ASTNode{
public:
    ASTInitDeclList(ASTInitDecl*);
    ASTInitDeclList(ASTInitDeclList*, ASTInitDecl*);
    vector<ASTInitDecl*> initializations;

    [[nodiscard]] string to_str() const override{
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
    ASTFnDecl* fnDecl = nullptr;

    ASTDecl(string name, ctype_ type): ASTNode(){
      this->name = name;
      this->type = type;
    }

    [[nodiscard]] string to_str() const override{
      if(fnDecl)
        return "Declaration";
      if(is_const)
        return "Declaration: " + name + ", type: " + to_string(type) + ", is_const: True, num_ptr: " + to_string(num_ptr);
      return "Declaration: " + name + ", type: " + to_string(type) + ", is_const: False, num_ptr: " + to_string(num_ptr);
    }

    llvm::Value *accept(Codegen *codegen) override;
};

class ASTDeclList: public ASTNode{
public:
    ASTDeclList(ASTDeclSpec* n1, ASTInitDeclList* n2);
    vector<ASTDecl*> declarations;

    [[nodiscard]] string to_str() const override{
      return "DeclarationList";
    }

    llvm::Value *accept(Codegen *codegen) override;
};



#endif //CCOMPILER_DECL_H
