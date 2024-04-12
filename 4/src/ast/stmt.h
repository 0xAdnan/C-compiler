//
// Created by satyam on 30/3/24.
//

#ifndef CCOMPILER_STMT_H
#define CCOMPILER_STMT_H

#include "base.h"
#include "decl.h"


class ASTStmt: public ASTNode{
public:
    ASTStmt(): ASTNode(){
      int x = 1;
    }
};


class ASTExprStmt: public ASTStmt{
public:
    ASTExpr* expr;

    ASTExprStmt(){
      expr = nullptr;
    }

    ASTExprStmt(ASTExpr* expr): ASTStmt() {
      this->expr = expr;
      children.push_back(expr);
    }

    [[nodiscard]] string to_str() const override {
      return "ExpressionStmt";
    }
};

class ASTLabeledStmt: public ASTStmt{
public:
    ASTStmt* stmt;

    explicit ASTLabeledStmt(ASTStmt* stmt): ASTStmt(){
      this->stmt = stmt;
      children.push_back(stmt);
    }
};

class ASTGotoLabeledStmt: public ASTLabeledStmt{
public:
    string label;

    ASTGotoLabeledStmt(string label, ASTStmt* stmt): ASTLabeledStmt(stmt){
      this->label = label;
    }

    [[nodiscard]] string to_str() const override {
      return "Label: " + label;
    }
};

class ASTCaseLabeledStmt: public ASTLabeledStmt{
public:
    ASTExpr* condition;

    ASTCaseLabeledStmt(ASTExpr* cond, ASTStmt* stmt): ASTLabeledStmt(stmt){
      this->condition = cond;
      children.push_back(stmt);
    }

    [[nodiscard]] string to_str() const override {
      return "Case" ;
    }
};

class ASTDefLabeledStmt: public ASTLabeledStmt{
public:
    ASTDefLabeledStmt(ASTStmt* stmt): ASTLabeledStmt(stmt){}

    [[nodiscard]] string to_str() const override {
      return "Default" ;
    }
};

class ASTSelectStmt: public ASTStmt{
public:
    ASTExpr* cond;

    ASTSelectStmt(ASTExpr* cond): ASTStmt(){
      this->cond = cond;

      children.push_back(cond);
    }
};

class ASTIfStmt: public ASTSelectStmt{
public:
    ASTStmt* stmt;

    ASTIfStmt(ASTExpr* cond, ASTStmt* stmt): ASTSelectStmt(cond){
      this->stmt = stmt;

      children.push_back(stmt);
    }

    [[nodiscard]] string to_str() const override {
      return "If Stmt" ;
    }

    llvm::Value *accept(Codegen *codegen) override;
};

class ASTIfElseStmt: public ASTSelectStmt{
public:
    ASTStmt* stmt;
    ASTStmt* elseStmt;

    ASTIfElseStmt(ASTExpr* cond, ASTStmt* stmt1, ASTStmt* stmt2): ASTSelectStmt(cond){
      this->stmt = stmt1;
      this->elseStmt = stmt2;

      children.push_back(stmt1);
      children.push_back(stmt2);
    }

    [[nodiscard]] string to_str() const override {
      return "IfElse Stmt" ;
    }

    llvm::Value *accept(Codegen *codegen) override;
};

class ASTSwitchStmt: public ASTSelectStmt{
public:
    ASTStmt* stmt;

    ASTSwitchStmt(ASTExpr* cond, ASTStmt* stmt): ASTSelectStmt(cond){
      this->stmt = stmt;

      children.push_back(stmt);
    }

    [[nodiscard]] string to_str() const override {
      return "Switch Stmt" ;
    }
};

class ASTIterStmt: public ASTStmt{};

class ASTWhileStmt: public ASTIterStmt{
public:
    ASTExpr* cond;
    ASTStmt* stmt;

    ASTWhileStmt(ASTExpr* cond, ASTStmt* stmt): ASTIterStmt(){
      this->cond = cond;
      this->stmt = stmt;

      children.push_back(cond);
      children.push_back(stmt);
    }

    [[nodiscard]] string to_str() const override {
      return "While Stmt" ;
    }

    llvm::Value *accept(Codegen *codegen) override;

};

class ASTDoWhileStmt: public ASTIterStmt{
public:
    ASTExpr* cond;
    ASTStmt* stmt;

    ASTDoWhileStmt(ASTExpr* cond, ASTStmt* stmt): ASTIterStmt(){
      this->cond = cond;
      this->stmt = stmt;

      children.push_back(cond);
      children.push_back(stmt);
    }

    [[nodiscard]] string to_str() const override {
      return "DoWhile Stmt" ;
    }
};

class ASTForStmt: public ASTIterStmt{
public:
    ASTExprStmt* expr1;
    ASTExprStmt* expr2;
    ASTExpr* expr3;
    ASTStmt* stmt;

    ASTForStmt(ASTExprStmt* expr1, ASTExprStmt* expr2, ASTExpr* expr3, ASTStmt* stmt): ASTIterStmt(){
      this->expr1 = expr1;
      this->expr2 = expr2;
      this->expr3 = expr3;
      this->stmt = stmt;

      children.push_back(expr1);
      children.push_back(expr2);
      children.push_back(expr3);
      children.push_back(stmt);
    }

    ASTForStmt(ASTExprStmt* exprStmt, ASTExprStmt* expr2, ASTStmt* stmt): ASTIterStmt(){
      this->expr1 = exprStmt;
      this->expr2 = expr2;
      this->expr3 = nullptr;
      this->stmt = stmt;

      children.push_back(expr1);
      children.push_back(expr2);
      children.push_back(stmt);
    }


    [[nodiscard]] string to_str() const override {
      return "For Stmt" ;
    }
};

class ASTForStmt2: public ASTIterStmt{
public:
    ASTDeclList* declList;
    ASTExprStmt* expr2;
    ASTExpr* expr3;
    ASTStmt* stmt;

    ASTForStmt2(ASTDeclList* declList, ASTExprStmt* expr2, ASTExpr* expr3, ASTStmt* stmt): ASTIterStmt(){
      this->declList = declList;
      this->expr2 = expr2;
      this->expr3 = expr3;
      this->stmt = stmt;

      children.push_back(declList);
      children.push_back(expr2);
      children.push_back(expr3);
      children.push_back(stmt);
    }

    ASTForStmt2(ASTDeclList* declList, ASTExprStmt* expr2, ASTStmt* stmt): ASTIterStmt(){
      this->declList = declList;
      this->expr2 = expr2;
      this->expr3 = nullptr;
      this->stmt = stmt;

      children.push_back(expr2);
      children.push_back(expr3);
      children.push_back(stmt);
    }


    [[nodiscard]] string to_str() const override {
      return "For Stmt" ;
    }
};

class ASTJmpStmt: public ASTStmt{
public:
    ASTJmpStmt(): ASTStmt(){}
};

class ASTGotoJmpStmt: public ASTJmpStmt{
public:
    string label;

    ASTGotoJmpStmt(string label): ASTJmpStmt(){
      this->label = label;
    }

    [[nodiscard]] string to_str() const override {
      return "Goto label: " + label;
    }
};

class ASTContJmpStmt: public ASTJmpStmt{
public:
    ASTContJmpStmt(): ASTJmpStmt(){}

    [[nodiscard]] string to_str() const override {
      return "Continue";
    }
};

class ASTBreakJmpStmt: public ASTJmpStmt{
public:
    ASTBreakJmpStmt(): ASTJmpStmt(){}

    [[nodiscard]] string to_str() const override {
      return "Break";
    }
};

class ASTRetJmpStmt: public ASTJmpStmt{
public:
    ASTExpr* expr;

    ASTRetJmpStmt(): ASTJmpStmt(){ expr = nullptr; }

    explicit ASTRetJmpStmt(ASTExpr* expr): ASTJmpStmt(){
      this->expr = expr;

      children.push_back(expr);
    }


    [[nodiscard]] string to_str() const override {
      return "Return";
    }
};

class ASTBlock: public ASTNode{
public:
    ASTDeclList* declaration = nullptr;
    ASTStmt* stmt = nullptr;

    explicit ASTBlock(ASTDeclList* declaration): ASTNode() {
      this->declaration = declaration;

      children.push_back(declaration);
    }

    explicit ASTBlock(ASTStmt* stmt): ASTNode() {
      this->stmt = stmt;

      children.push_back(stmt);
    }

    [[nodiscard]] string to_str() const override {
      return "Block";
    }

    llvm::Value *accept(Codegen *codegen) override;
};

class ASTBlockList: public ASTStmt{
public:
    vector<ASTBlock*> blocks;

    ASTBlockList(): ASTStmt(){}

    explicit ASTBlockList(ASTBlock* block): ASTStmt(){
      blocks.push_back(block);
      children.push_back(block->children[0]);
    }

    ASTBlockList(ASTBlockList* blocks, ASTBlock* block): ASTStmt(){
      for(auto b: blocks->blocks)
        this->blocks.push_back(b);

      this->blocks.push_back(block);

      delete blocks;

      children.clear();
      for(auto b: this->blocks)
        children.push_back(b->children[0]);
    }

    [[nodiscard]] string to_str() const override {
      return "BlockList";
    }

    llvm::Value *accept(Codegen *codegen) override;
};

#endif //CCOMPILER_STMT_H
