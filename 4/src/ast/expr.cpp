
#include "expr.h"
#include "Codegen.h"

llvm::Value *ASTConst::accept(Codegen *codegen) {
  return codegen->visit(this);
}
