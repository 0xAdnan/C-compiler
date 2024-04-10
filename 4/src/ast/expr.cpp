
#include "expr.h"
#include "Codegen.h"


llvm::Value *ASTExpr::accept(Codegen *codegen) {
  return codegen->visit(this);
}