
#include "expr.h"
#include "codegen.h"


llvm::Value *ASTExpr::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTConst::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTIdExpr::accept(Codegen *codegen) {
  return codegen->visit(this);
}


llvm::Value *ASTFunctionCall::accept(Codegen *codegen) {
  return codegen->visit(this);
}


llvm::Value *ASTExprList::accept(Codegen *codegen) {
  llvm::Value *value = nullptr;
  for (auto expr: exprs) {
    value = expr->accept(codegen);
  }
  return value;
}
