//
// Created by satyam on 30/3/24.
//

#ifndef CCOMPILER_PROG_H
#define CCOMPILER_PROG_H

#include "base.h"
#include "decl.h"
#include "stmt.h"

class ASTExternDecl: public ASTNode{
public:
    ASTExternDecl(): ASTNode(){}

    llvm::Value *accept(Codegen *codegen) override {
      return ASTNode::accept(codegen);
    }
};

class ASTFnDef: public ASTExternDecl{
public:
    ASTDeclSpec* declSpec;
    ASTFnDecl* fnDecl;
    ASTBlockList* body;

    ASTFnDef(ASTDeclSpec* declSpec, ASTFnDecl* astFnDecl, ASTBlockList* body): ASTExternDecl(){
      this->declSpec = declSpec;
      this->fnDecl = astFnDecl;
      this->body = body;

      children.push_back(declSpec);
      children.push_back(fnDecl);
      children.push_back(body);
    }

    [[nodiscard]] string to_str() const override {
      return "FunctionDef";
    }

    llvm::Value *accept(Codegen *codegen) override;
};

class ASTGlobalVar: public ASTExternDecl{
public:
    ASTDeclList* declaration;

    explicit ASTGlobalVar(ASTDeclList* decl): ASTExternDecl(){
      declaration = decl;

      children.push_back(decl);
    }

    [[nodiscard]] string to_str() const override {
      return "GlobalVar";
    }

    llvm::Value *accept(Codegen *codegen) override;
};

class ASTProgram: public ASTNode{
public:
  vector<ASTExternDecl*> extDecls;

  explicit ASTProgram(ASTExternDecl* decl){
    extDecls.push_back(decl);

    children.push_back(decl);
  }

  ASTProgram(ASTProgram* program, ASTExternDecl* decl){
    for(auto p: program->extDecls){
      extDecls.push_back(p);
    }
    extDecls.push_back(decl);

    children.clear();
    for(auto c: extDecls){
      children.push_back(c);
    }
  }

  [[nodiscard]] string to_str() const override {
    return "Program";
  }

};

#endif //CCOMPILER_PROG_H
