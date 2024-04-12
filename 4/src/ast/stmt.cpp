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
