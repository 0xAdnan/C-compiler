//
// Created by satyam on 30/3/24.
//

#ifndef CCOMPILER_PROG_H
#define CCOMPILER_PROG_H

#include "base.h"
#include "decl.h"
#include "stmt.h"

class ASTExternDecl : public ASTNode {
public:
    ASTExternDecl() : ASTNode() {}

    llvm::Value *accept(Codegen *codegen) override {
      return ASTNode::accept(codegen);
    }

    ASTExternDecl *accept(AlgebraSimplificationOpt *aso) override = 0;

    string accept(Printer *printer, int indent) override {
      return ASTNode::accept(printer, indent);
    }
};

class ASTFnDef : public ASTExternDecl {
public:
    ASTDeclSpec *declSpec;
    ASTFnDecl *fnDecl;
    ASTBlockList *body;

    ASTFnDef(ASTDeclSpec *declSpec, ASTFnDecl *astFnDecl, ASTBlockList *body) : ASTExternDecl() {
      this->declSpec = declSpec;
      this->fnDecl = astFnDecl;
      this->body = body;
    }

    [[nodiscard]] string to_str() const override {
      return "FunctionDef";
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTFnDef *accept(AlgebraSimplificationOpt *aso) override;

    ASTFnDef *accept(DeadCodeOpt *dco) override;

    string accept(Printer *, int indent) override;
};

class ASTGlobalVar : public ASTExternDecl {
public:
    ASTDeclList *declaration;

    explicit ASTGlobalVar(ASTDeclList *decl) : ASTExternDecl() {
      declaration = decl;
    }

    [[nodiscard]] string to_str() const override {
      return "GlobalVar";
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTGlobalVar *accept(AlgebraSimplificationOpt *aso) override;

    string accept(Printer *, int indent) override;
};

class ASTProgram : public ASTNode {
public:
    vector<ASTExternDecl *> extDecls;

    explicit ASTProgram(ASTExternDecl *decl) {
      extDecls.push_back(decl);
    }

    ASTProgram(ASTProgram *program, ASTExternDecl *decl) {
      for (auto p: program->extDecls) {
        extDecls.push_back(p);
      }
      extDecls.push_back(decl);
    }

    [[nodiscard]] string to_str() const override {
      return "Program";
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTProgram *accept(AlgebraSimplificationOpt *) override;

    ASTProgram *accept(DeadCodeOpt *) override;

    string accept(Printer *printer, int indent) override;

};

#endif //CCOMPILER_PROG_H
