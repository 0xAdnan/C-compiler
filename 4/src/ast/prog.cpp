//
// Created by satyam on 31/3/24.
//
#include "prog.h"
#include "codegen.h"

//llvm::Value *ASTFnDef::accept(Codegen *codegen) {
//  return codegen->visit(this);
//}

llvm::Value *ASTGlobalVar::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTFnDef::accept(Codegen *codegen) {
  return codegen->visit(this);
}
