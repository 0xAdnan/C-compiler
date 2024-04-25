#include "expr.h"
#include "codegen.h"
#include "algebra_simplification_opt.h"
#include "const_prop_opt.h"
#include "printer.h"


// ////////////////////////////////////////////////////
// ////////////////// CODEGEN /////////////////////////
// ////////////////////////////////////////////////////

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

llvm::Value *ASTPostIncrement::accept(Codegen *codegen) {
  return codegen->visit(this);
}

// ////////////////////////////////////////////////////
// ///////////// ALGEBRA SIMPLIFICATION ///////////////
// ////////////////////////////////////////////////////

ASTExprList *ASTExprList::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}

ASTExpr *ASTExpr::accept(AlgebraSimplificationOpt *opt) {
  return opt->visit(this);
}

// ////////////////////////////////////////////////////
// ///////////////////// PRINTER //////////////////////
// ////////////////////////////////////////////////////

string ASTExpr::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTConst::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTIdExpr::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTFunctionCall::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTExprList::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTPostIncrement::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTArrayAccess::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

// /////////////////////////////////////////////////////////////////
// ////////////////// CONSTANT PROPAGATION /////////////////////////
// /////////////////////////////////////////////////////////////////

ASTExpr *ASTExpr::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}

ASTExpr *ASTIdExpr::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}

ASTExpr *ASTExprList::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}

ASTConst *ASTConst::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}

