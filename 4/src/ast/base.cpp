//
// Created by satyam on 29/3/24.
//

#include <llvm/Support/raw_ostream.h>
#include "base.h"

llvm::Value *ASTNode::accept(Codegen *codegen) {
  string msg = "Codegen for '" + to_str() + "' not supported yet.";
  llvm::errs() << msg << "\n";
  assert(false);
}

ASTNode *ASTNode::accept(AlgebraSimplificationOpt *node) {
  string msg = "Algebraic Simplification is not implemented for '" + to_str() + "' not supported yet.";
  llvm::errs() << msg << "\n";
  assert(false);
}

string ASTNode::accept(Printer *, int) {
  return {};
}

ASTNode *ASTNode::accept(ConstPropagationOpt *) {
  string msg = "Constant Propagation is not implemented for '" + to_str() + "' not supported yet.";
  llvm::errs() << msg << "\n";
  assert(false);
}

ASTNode *ASTNode::accept(DeadCodeOpt *) {
  string msg = "Dead Code is not implemented for '" + to_str() + "' not supported yet.";
  llvm::errs() << msg << "\n";
  assert(false);
}
