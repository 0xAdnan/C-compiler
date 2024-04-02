//
// Created by satyam on 1/4/24.
//
#include "stmt.h"
#include "Codegen.h"

llvm::Value *ASTBlockList::accept(Codegen *codegen) {
  return codegen->visit(this);
}


llvm::Value *ASTBlock::accept(Codegen *codegen) {
  return codegen->visit(this);
}
