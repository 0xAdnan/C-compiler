//
// Created by satyam on 1/4/24.
//
#include "stmt.h"
#include "codegen.h"
#include "dead_code_opt.h"
#include "algebra_simplification_opt.h"
#include "const_prop_opt.h"
#include "printer.h"


// ////////////////////////////////////////////////////
// ////////////////// CODEGEN /////////////////////////
// ////////////////////////////////////////////////////

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

llvm::Value *ASTRetJmpStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTExprStmt::accept(Codegen *codegen) {
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

llvm::Value *ASTGotoLabeledStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTForStmt2::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTGotoJmpStmt::accept(Codegen *codegen) {
  return codegen->visit(this);
}

// ////////////////////////////////////////////////////
// ///////////// ALGEBRA SIMPLIFICATION ///////////////
// ////////////////////////////////////////////////////

ASTBlockList *ASTBlockList::accept(AlgebraSimplificationOpt *aso) {
  aso->visit(this);
}

ASTBlock *ASTBlock::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}


ASTIfElseStmt *ASTIfElseStmt::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}


ASTIfStmt *ASTIfStmt::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}

ASTWhileStmt *ASTWhileStmt::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}

ASTExprStmt *ASTExprStmt::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}

ASTRetJmpStmt *ASTRetJmpStmt::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}

ASTGotoLabeledStmt *ASTGotoLabeledStmt::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}

ASTStmt *ASTStmt::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}

ASTSelectStmt *ASTSelectStmt::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}

ASTIterStmt *ASTIterStmt::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}

// ////////////////////////////////////////////////////
// ///////////////////// PRINTER /////////////////////
// ////////////////////////////////////////////////////

string ASTBlock::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}


string ASTIfStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}


string ASTIfElseStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}


string ASTBlockList::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

ASTBlockList *ASTBlockList::accept(DeadCodeOpt *dco) {
  return dco->visit(this);
}

string ASTRetJmpStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTWhileStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}


string ASTExprStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTContJmpStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTBreakJmpStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTForStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTForStmt2::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTGotoJmpStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTGotoLabeledStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTCaseLabeledStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTDefLabeledStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTSwitchStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTDoWhileStmt::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

ASTBlock *ASTBlock::accept(DeadCodeOpt *dco) {
  return dco->visit(this);
}

ASTStmt *ASTIfStmt::accept(DeadCodeOpt *dco) {
  return dco->visit(this);
}
ASTStmt *ASTIfElseStmt::accept(DeadCodeOpt *dco) {
  return dco->visit(this);
}

ASTWhileStmt *ASTWhileStmt::accept(DeadCodeOpt *dco) {
  return dco->visit(this);
}


// /////////////////////////////////////////////////////////////////
// ////////////////// CONSTANT PROPAGATION /////////////////////////
// /////////////////////////////////////////////////////////////////

ASTStmt *ASTStmt::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}

ASTExprStmt *ASTExprStmt::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}

ASTIfStmt *ASTIfStmt::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}

ASTIfElseStmt *ASTIfElseStmt::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}

ASTWhileStmt *ASTWhileStmt::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}

ASTBlock *ASTBlock::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}

ASTBlockList *ASTBlockList::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}