
#include "expr.h"
#include "Codegen.h"

llvm::Value *ASTConst::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTExpr::accept(Codegen *codegen) {
  return codegen->visit(this);
}