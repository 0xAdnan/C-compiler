//
// Created by satyam on 31/3/24.
//
#include "prog.h"
#include "codegen.h"
#include "algebra_simplification_opt.h"
#include "dead_code_opt.h"
#include "printer.h"
#include "const_prop_opt.h"


// ////////////////////////////////////////////////////
// ////////////////// CODEGEN /////////////////////////
// ////////////////////////////////////////////////////

llvm::Value *ASTGlobalVar::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTFnDef::accept(Codegen *codegen) {
  return codegen->visit(this);
}

llvm::Value *ASTProgram::accept(Codegen *codegen) {
  return codegen->visit(this);
}


// ////////////////////////////////////////////////////
// ///////////// ALGEBRA SIMPLIFICATION ///////////////
// ////////////////////////////////////////////////////

ASTFnDef *ASTFnDef::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}

ASTGlobalVar *ASTGlobalVar::accept(AlgebraSimplificationOpt *aso) {
  return aso->visit(this);
}

ASTProgram *ASTProgram::accept(AlgebraSimplificationOpt *opt) {
  return opt->visit(this);
}


// ////////////////////////////////////////////////////
// ///////////////////// PRINTER //////////////////////
// ////////////////////////////////////////////////////

string ASTFnDef::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

ASTFnDef *ASTFnDef::accept(DeadCodeOpt *dco) {
  return dco->visit(this);
}

string ASTGlobalVar::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

string ASTProgram::accept(Printer *printer, int indent) {
  return printer->visit(this, indent);
}

ASTProgram *ASTProgram::accept(DeadCodeOpt *deadCodeOpt) {
  return deadCodeOpt->visit(this);
}


// /////////////////////////////////////////////////////////////////
// ////////////////// CONSTANT PROPAGATION /////////////////////////
// /////////////////////////////////////////////////////////////////

ASTProgram *ASTProgram::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}

ASTFnDef *ASTFnDef::accept(ConstPropagationOpt *cpo) {
  return cpo->visit(this);
}