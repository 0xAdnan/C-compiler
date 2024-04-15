//
// Created by satyam on 1/4/24.
//
#include "stmt.h"
#include "codegen.h"

llvm::Value *ASTBlockList::accept(Codegen *codegen) {
  return codegen->visit(this);
}


llvm::Value *ASTBlock::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTIfElseStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTIfStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTWhileStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTExprStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTRetJmpStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTContJmpStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTBreakJmpStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTForStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTForStmt2::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTGotoJmpStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTGotoLabeledStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}
