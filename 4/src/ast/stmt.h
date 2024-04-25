//
// Created by satyam on 30/3/24.
//

#ifndef CCOMPILER_STMT_H
#define CCOMPILER_STMT_H

#include "base.h"
#include "decl.h"


class ASTStmt : public ASTNode {
public:
    ASTStmt() : ASTNode() {}

    llvm::Value *accept(Codegen *cg) override {
      return ASTNode::accept(cg);
    };

    ASTStmt *accept(AlgebraSimplificationOpt *aso) override;

    ASTStmt *accept(DeadCodeOpt *deadCodeOpt) override{
      return this;
    }

    string accept(Printer *printer, int indent) override;
};


class ASTExprStmt : public ASTStmt {
public:
    ASTExprList *exprs;

    ASTExprStmt() {
      exprs = nullptr;
    }

    ASTExprStmt(ASTExprList *exprs) : ASTStmt() {
      this->exprs = exprs;
    }

    [[nodiscard]] string to_str() const override {
      return "ExpressionStmt";
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTExprStmt *accept(AlgebraSimplificationOpt *) override;

    string accept(Printer *printer, int indent) override;

};

class ASTLabeledStmt : public ASTStmt {
public:
    ASTStmt *stmt;

    explicit ASTLabeledStmt(ASTStmt *stmt) : ASTStmt() {
      this->stmt = stmt;
    }
};

class ASTGotoLabeledStmt : public ASTLabeledStmt {
public:
    string label;

    ASTGotoLabeledStmt(string label, ASTStmt *stmt) : ASTLabeledStmt(stmt) {
      this->label = label;
    }

    [[nodiscard]] string to_str() const override {
      return "Label: " + label;
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTGotoLabeledStmt *accept(AlgebraSimplificationOpt *) override;

    string accept(Printer *printer, int indent) override;
};

class ASTCaseLabeledStmt : public ASTLabeledStmt {
public:
    ASTExpr *condition;

    ASTCaseLabeledStmt(ASTExpr *cond, ASTStmt *stmt) : ASTLabeledStmt(stmt) {
      this->condition = cond;
    }

    [[nodiscard]] string to_str() const override {
      return "Case";
    }

    string accept(Printer *printer, int indent) override;
};

class ASTDefLabeledStmt : public ASTLabeledStmt {
public:
    ASTDefLabeledStmt(ASTStmt *stmt) : ASTLabeledStmt(stmt) {}

    [[nodiscard]] string to_str() const override {
      return "Default";
    }

    string accept(Printer *printer, int indent) override;
};

class ASTSelectStmt : public ASTStmt {
public:
    ASTExpr *cond;

    explicit ASTSelectStmt(ASTExpr *cond) : ASTStmt() {
      this->cond = cond;
    }

    ASTSelectStmt *accept(AlgebraSimplificationOpt *) override;
};

class ASTIfStmt : public ASTSelectStmt {
public:
    ASTStmt *stmt;

    ASTIfStmt(ASTExpr *cond, ASTStmt *stmt) : ASTSelectStmt(cond) {
      this->stmt = stmt;
    }

    [[nodiscard]] string to_str() const override {
      return "If Stmt";
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTIfStmt *accept(AlgebraSimplificationOpt *) override;

    ASTStmt *accept(DeadCodeOpt *) override;

    string accept(Printer *printer, int indent) override;
};

class ASTIfElseStmt : public ASTSelectStmt {
public:
    ASTStmt *stmt;
    ASTStmt *elseStmt;

    ASTIfElseStmt(ASTExpr *cond, ASTStmt *stmt1, ASTStmt *stmt2) : ASTSelectStmt(cond) {
      this->stmt = stmt1;
      this->elseStmt = stmt2;
    }

    [[nodiscard]] string to_str() const override {
      return "IfElse Stmt";
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTIfElseStmt *accept(AlgebraSimplificationOpt *) override;

    ASTStmt *accept(DeadCodeOpt *) override;

    string accept(Printer *printer, int indent) override;

};

class ASTSwitchStmt : public ASTSelectStmt {
public:
    ASTStmt *stmt;

    ASTSwitchStmt(ASTExpr *cond, ASTStmt *stmt) : ASTSelectStmt(cond) {
      this->stmt = stmt;
    }

    [[nodiscard]] string to_str() const override {
      return "Switch Stmt";
    }

    string accept(Printer *printer, int indent) override;
};

class ASTIterStmt : public ASTStmt {
    ASTIterStmt *accept(AlgebraSimplificationOpt *) override;
};

class ASTWhileStmt : public ASTIterStmt {
public:
    ASTExpr *cond;
    ASTStmt *stmt;

    ASTWhileStmt(ASTExpr *cond, ASTStmt *stmt) : ASTIterStmt() {
      this->cond = cond;
      this->stmt = stmt;
    }

    [[nodiscard]] string to_str() const override {
      return "While Stmt";
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTWhileStmt *accept(AlgebraSimplificationOpt *) override;

    ASTWhileStmt *accept(DeadCodeOpt *) override;

    string accept(Printer *printer, int indent) override;

};

class ASTDoWhileStmt : public ASTIterStmt {
public:
    ASTExpr *cond;
    ASTStmt *stmt;

    ASTDoWhileStmt(ASTExpr *cond, ASTStmt *stmt) : ASTIterStmt() {
      this->cond = cond;
      this->stmt = stmt;
    }

    [[nodiscard]] string to_str() const override {
      return "DoWhile Stmt";
    }

    string accept(Printer *printer, int indent) override;
};

class ASTForStmt : public ASTIterStmt {
public:
    ASTExprStmt *expr1;
    ASTExprStmt *expr2;
    ASTExpr *expr3;
    ASTStmt *stmt;

    ASTForStmt(ASTExprStmt *expr1, ASTExprStmt *expr2, ASTExpr *expr3, ASTStmt *stmt) : ASTIterStmt() {
      this->expr1 = expr1;
      this->expr2 = expr2;
      this->expr3 = expr3;
      this->stmt = stmt;
    }

    ASTForStmt(ASTExprStmt *exprStmt, ASTExprStmt *expr2, ASTStmt *stmt) : ASTIterStmt() {
      this->expr1 = exprStmt;
      this->expr2 = expr2;
      this->expr3 = nullptr;
      this->stmt = stmt;
    }

    [[nodiscard]] string to_str() const override {
      return "For Stmt";
    }

    llvm::Value *accept(Codegen *codegen) override;

    string accept(Printer *printer, int indent) override;
};

class ASTForStmt2 : public ASTIterStmt {
public:
    ASTDeclList *declList;
    ASTExprStmt *expr2;
    ASTExpr *expr3;
    ASTStmt *stmt;

    ASTForStmt2(ASTDeclList *declList, ASTExprStmt *expr2, ASTExpr *expr3, ASTStmt *stmt) : ASTIterStmt() {
      this->declList = declList;
      this->expr2 = expr2;
      this->expr3 = expr3;
      this->stmt = stmt;
    }

    ASTForStmt2(ASTDeclList *declList, ASTExprStmt *expr2, ASTStmt *stmt) : ASTIterStmt() {
      this->declList = declList;
      this->expr2 = expr2;
      this->expr3 = nullptr;
      this->stmt = stmt;
    }

    [[nodiscard]] string to_str() const override {
      return "For Stmt2";
    }

    llvm::Value *accept(Codegen *codegen) override;

    string accept(Printer *printer, int indent) override;
};

class ASTJmpStmt : public ASTStmt {
public:
    ASTJmpStmt() : ASTStmt() {}

    ASTJmpStmt *accept(AlgebraSimplificationOpt *) override {
      return this;
    }
};

class ASTGotoJmpStmt : public ASTJmpStmt {
public:
    string label;

    ASTGotoJmpStmt(string label) : ASTJmpStmt() {
      this->label = label;
    }

    [[nodiscard]] string to_str() const override {
      return "Goto label: " + label;
    }

    llvm::Value *accept(Codegen *codegen) override;

    string accept(Printer *printer, int indent) override;
};

class ASTContJmpStmt : public ASTJmpStmt {
public:
    ASTContJmpStmt() : ASTJmpStmt() {}

    [[nodiscard]] string to_str() const override {
      return "Continue";
    }

    llvm::Value *accept(Codegen *codegen) override;

    string accept(Printer *printer, int indent) override;
};

class ASTBreakJmpStmt : public ASTJmpStmt {
public:
    ASTBreakJmpStmt() : ASTJmpStmt() {}

    [[nodiscard]] string to_str() const override {
      return "Break";
    }

    llvm::Value *accept(Codegen *codegen) override;

    string accept(Printer *printer, int indent) override;
};

class ASTRetJmpStmt : public ASTJmpStmt {
public:
    ASTExpr *expr;

    ASTRetJmpStmt() : ASTJmpStmt() { expr = nullptr; }

    explicit ASTRetJmpStmt(ASTExpr *expr) : ASTJmpStmt() {
      this->expr = expr;
    }


    [[nodiscard]] string to_str() const override {
      return "Return";
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTRetJmpStmt *accept(AlgebraSimplificationOpt *) override;

    string accept(Printer *printer, int indent) override;

};

class ASTBlock : public ASTNode {
public:
    ASTDeclList *declaration = nullptr;
    ASTStmt *stmt = nullptr;

    explicit ASTBlock(ASTDeclList *declaration) : ASTNode() {
      this->declaration = declaration;
    }

    explicit ASTBlock(ASTStmt *stmt) : ASTNode() {
      this->stmt = stmt;
    }

    [[nodiscard]] string to_str() const override {
      return "Block";
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTBlock *accept(AlgebraSimplificationOpt *) override;

    ASTBlock *accept(DeadCodeOpt *) override;

    string accept(Printer *printer, int indent) override;
};

class ASTBlockList : public ASTStmt {
public:
    vector<ASTBlock *> blocks;

    ASTBlockList() : ASTStmt() {}

    explicit ASTBlockList(ASTBlock *block) : ASTStmt() {
      blocks.push_back(block);
    }

    ASTBlockList(ASTBlockList *blocks, ASTBlock *block) : ASTStmt() {
      for (auto b: blocks->blocks)
        this->blocks.push_back(b);

      this->blocks.push_back(block);

      delete blocks;
    }

    [[nodiscard]] string to_str() const override {
      return "BlockList";
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTBlockList *accept(AlgebraSimplificationOpt *) override;

    ASTBlockList *accept(DeadCodeOpt *) override;

    string accept(Printer *printer, int indent) override;
};

#endif //CCOMPILER_STMT_H
