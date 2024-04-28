//
// Created by satyam on 18/4/24.
//

#include "algebra_simplification_opt.h"
#include "opt_utils.h"

bool AlgebraSimplificationOpt::is_simplifiable(operators ot){
  switch (ot) {
    case b_mul:
    case b_div:
    case b_remainder:
    case b_add:
    case b_minus:
    case b_and:
    case b_or:
      return true;

    case noop:
    case u_op_plus_plus:
    case u_op_minus_minus:
    case u_op_and:
    case u_op_star:
    case u_op_plus:
    case u_op_minus:
    case u_op_tilde:
    case u_op_not:
    case b_left_shift:
    case b_right_shift:
    case b_less:
    case b_greater:
    case b_less_eq:
    case b_greater_eq:
    case b_eq:
    case b_neq:
    case b_bitand:
    case b_bitxor:
    case b_bitor:
    case t_cond:
    case assign:
    case mul_assign:
    case div_assign:
    case mod_assign:
    case add_assign:
    case sub_assign:
    case left_assign:
    case right_assign:
    case and_assign:
    case xor_assign:
    case or_assign:
      return false;
  }
}



ASTExpr* AlgebraSimplificationOpt::visit(ASTExpr * expr) {
  ASTExpr* left;
  ASTExpr* right;

  if(is_simplifiable(expr->operator_)){
    assert(expr->operands.size() == 2);
    left = expr->operands[0];
    right = expr->operands[1];

    left = left->accept(this);
    right = right->accept(this);
  }
  else
    return expr;

  switch(expr->operator_){
    case b_mul:
      if(is_const_node(left, "0") || is_const_node(right, "0"))
        return new ASTConst(i_const,  "0");
      if(is_const_node(right, "1"))
        return right;
      if(is_const_node(right, "1"))
        return left;
      return expr;

    case b_div:
      if(is_const_node(right, "0"))
        return new ASTConst(i_const, "0");
      if(is_const_node(right, "1"))
        return left;
      return expr;
    case b_remainder:
      if(is_const_node(right, "1"))
        return new ASTConst(i_const, "0");
      return expr;
    case b_minus:
    case b_add:
      if(is_const_node(left, "0"))
        return right;
      if(is_const_node(right, "0"))
        return left;
      return expr;

    case b_bitand:
      if(is_const_node(left, "0") || is_const_node(right, "0"))
        return new ASTConst(i_const, "0");
      return expr;
    case b_bitor:
      if(is_const_node(left, "1"))
        return right;
      if(is_const_node(right, "1"))
        return left;
      return expr;
    case b_and:
      if(is_const_node(left, "0") || is_const_node(right, "0"))
        return new ASTConst(i_const, "0");
      return expr;
    case b_or:
      if(is_const_node(left, "1"))
        return right;
      if(is_const_node(right, "1"))
        return left;
      return expr;
    default:
      return expr;
  }
}

ASTProgram *AlgebraSimplificationOpt::visit(ASTProgram * prog) {
  vector<ASTExternDecl*> newDecls;

  for(auto* decl: prog->extDecls){
    auto new_decl = decl->accept(this);
    newDecls.push_back(new_decl);
  }
  prog->extDecls = newDecls;
  return prog;
}

ASTGlobalVar *AlgebraSimplificationOpt::visit(ASTGlobalVar * gv) {
  auto newGv = new ASTGlobalVar(this->visit(gv->declaration));
//  free(gv);
  return newGv;
}

ASTFnDef *AlgebraSimplificationOpt::visit(ASTFnDef * fnDef) {
  auto newBody = this->visit(fnDef->body);
  fnDef->body = newBody;
  return fnDef;
}

ASTDeclList* AlgebraSimplificationOpt::visit(ASTDeclList* declList){
  vector<ASTDecl*> newDeclList;

  for(auto* decl: declList->declarations){
    auto new_decl = this->visit(decl);
    newDeclList.push_back(new_decl);
  }
  declList->declarations = newDeclList;

  return declList;
}

ASTDecl* AlgebraSimplificationOpt::visit(ASTDecl* decl){
  if(decl->value == nullptr)
    return decl;
  auto newExpr = this->visit(decl->value);

  decl->value = newExpr;
  return decl;
}

ASTBlockList* AlgebraSimplificationOpt::visit(ASTBlockList* bl){
  vector<ASTBlock*> newBlocks;

  for(auto block: bl->blocks){
    auto newBlock = this->visit(block);
    newBlocks.push_back(newBlock);
  }

  bl->blocks = newBlocks;
  return bl;
}

ASTBlock *AlgebraSimplificationOpt::visit(ASTBlock * block) {
  if(block->stmt){
    auto newStmt = this->visit(block->stmt);
    block->stmt = newStmt;
  }
  if(block->declaration) {
    auto newDecl = this->visit(block->declaration);
    block->declaration = newDecl;
  }

  return block;
}

ASTExprStmt *AlgebraSimplificationOpt::visit(ASTExprStmt * exprStmt) {
  auto newExprs = this->visit(exprStmt->exprs);
//  free(exprStmt->exprs);

  exprStmt->exprs = newExprs;

  return exprStmt;
}

ASTExprList *AlgebraSimplificationOpt::visit(ASTExprList * exprList) {
  vector<ASTExpr*> newExprs;

  for(auto expr: exprList->exprs){
    auto newexpr = this->visit(expr);
    newExprs.push_back(newexpr);
  }

  return exprList;
}

ASTIfElseStmt *AlgebraSimplificationOpt::visit(ASTIfElseStmt *ifElseStmt) {
  ifElseStmt->stmt = this->visit(ifElseStmt->stmt);
}

ASTIfStmt *AlgebraSimplificationOpt::visit(ASTIfStmt *ifStmt) {
  auto newStmt = this->visit(ifStmt->stmt);
  auto newCond = this->visit(ifStmt->cond);

  ifStmt->stmt = newStmt;
  ifStmt->cond = newCond;

  return ifStmt;
}

ASTWhileStmt *AlgebraSimplificationOpt::visit(ASTWhileStmt *whileStmt) {
  auto newStmt = this->visit(whileStmt->stmt);
  auto newCond = this->visit(whileStmt->cond);

  whileStmt->stmt = newStmt;
  whileStmt->cond = newCond;

  return whileStmt;
}

ASTRetJmpStmt *AlgebraSimplificationOpt::visit(ASTRetJmpStmt *retJmpStmt) {
  auto expr = this->visit(retJmpStmt->expr);
  retJmpStmt->expr = expr;

  return retJmpStmt;
}

ASTGotoLabeledStmt *AlgebraSimplificationOpt::visit(ASTGotoLabeledStmt *gotoLabeledStmt) {
  return gotoLabeledStmt;
}
