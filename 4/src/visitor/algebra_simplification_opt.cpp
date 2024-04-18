//
// Created by satyam on 18/4/24.
//

#include "algebra_simplification_opt.h"

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

bool AlgebraSimplificationOpt::is_const_node(ASTNode* node, const string& value){
  auto constNode = dynamic_cast<ASTConst*>(node);
  if(constNode == nullptr)
    return false;
  return constNode->value == value;
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

    case b_div:
      if(is_const_node(right, "0"))
        return new ASTConst(i_const, "0");
      if(is_const_node(right, "1"))
        return left;

    case b_remainder:
      if(is_const_node(right, "1"))
        return new ASTConst(i_const, "0");

    case b_minus:
    case b_add:
      if(is_const_node(left, "0"))
        return right;
      if(is_const_node(right, "0"))
        return left;

    case b_bitand:
      if(is_const_node(left, "0") || is_const_node(right, "0"))
        return new ASTConst(i_const, "0");
    case b_bitor:
      if(is_const_node(left, "1"))
        return right;
      if(is_const_node(right, "1"))
        return left;
    case b_and:
      if(is_const_node(left, "0") || is_const_node(right, "0"))
        return new ASTConst(i_const, "0");
    case b_or:
      if(is_const_node(left, "1"))
        return right;
      if(is_const_node(right, "1"))
        return left;
    default:
      return expr;
  }
}

ASTProgram *AlgebraSimplificationOpt::visit(ASTProgram * prog) {
  vector<ASTExternDecl*> newDecls;

  prog->children.clear();
  for(auto* decl: prog->extDecls){
    auto new_decl = decl->accept(this);
//    free(decl);
    newDecls.push_back(new_decl);
    prog->children.push_back(new_decl);
  }

  return prog;
}

ASTGlobalVar *AlgebraSimplificationOpt::visit(ASTGlobalVar * gv) {
  auto newGv = new ASTGlobalVar(this->visit(gv->declaration));
//  free(gv);
  return newGv;
}

ASTFnDef *AlgebraSimplificationOpt::visit(ASTFnDef * fnDef) {
  auto newBody = this->visit(fnDef->body);
//  free(fnDef->body);

  fnDef->body = newBody;

  fnDef->children.clear();
  fnDef->children.push_back(fnDef->declSpec);
  fnDef->children.push_back(fnDef->fnDecl);
  fnDef->children.push_back(newBody);

  return fnDef;
}

ASTDeclList* AlgebraSimplificationOpt::visit(ASTDeclList* declList){
  vector<ASTDecl*> newDeclList;

  declList->children.clear();
  for(auto* decl: declList->declarations){
    auto new_decl = this->visit(decl);
//    free(decl);
    newDeclList.push_back(new_decl);
    declList->children.push_back(new_decl);
  }

  return declList;
}

ASTDecl* AlgebraSimplificationOpt::visit(ASTDecl* decl){
  if(decl->value == nullptr)
    return decl;
  auto newExpr = this->visit(decl->value);
//  free(decl->value);

  decl->value = newExpr;
  return decl;
}

ASTBlockList* AlgebraSimplificationOpt::visit(ASTBlockList* bl){
  vector<ASTBlock*> newBlocks;

  bl->children.clear();
  for(auto block: bl->blocks){
    auto newBlock = this->visit(block);
//    free(block);
    newBlocks.push_back(newBlock);
    bl->children.push_back(newBlock);
  }

  return bl;
}

ASTBlock *AlgebraSimplificationOpt::visit(ASTBlock * block) {
  block->children.clear();

  if(block->stmt){
    auto newStmt = this->visit(block->stmt);
    block->children.push_back(newStmt);
  }
  if(block->declaration) {
    auto newDecl = this->visit(block->declaration);
    block->children.push_back(newDecl);
  }

  return block;
}

ASTExprStmt *AlgebraSimplificationOpt::visit(ASTExprStmt * exprStmt) {
  auto newExprs = this->visit(exprStmt->exprs);
//  free(exprStmt->exprs);
  exprStmt->children.clear();

  exprStmt->exprs = newExprs;
  exprStmt->children.push_back(newExprs);

  return exprStmt;
}

ASTExprList *AlgebraSimplificationOpt::visit(ASTExprList * exprList) {
  vector<ASTExpr*> newExprs;

  exprList->children.clear();
  for(auto expr: exprList->exprs){
    auto newexpr = this->visit(expr);
//    free(expr);
    newExprs.push_back(newexpr);
    exprList->children.push_back(newexpr);
  }

  return exprList;
}

ASTIfElseStmt *AlgebraSimplificationOpt::visit(ASTIfElseStmt *ifElseStmt) {
  ifElseStmt->children.clear();
  ifElseStmt->stmt = this->visit(ifElseStmt->stmt);
}

ASTIfStmt *AlgebraSimplificationOpt::visit(ASTIfStmt *ifStmt) {
  ifStmt->children.clear();

  auto newStmt = this->visit(ifStmt->stmt);
  auto newCond = this->visit(ifStmt->cond);

  ifStmt->stmt = newStmt;
  ifStmt->cond = newCond;

  ifStmt->children.push_back(newStmt);
  ifStmt->children.push_back(newCond);

  return ifStmt;
}

ASTWhileStmt *AlgebraSimplificationOpt::visit(ASTWhileStmt *whileStmt) {
  whileStmt->children.clear();

  auto newStmt = this->visit(whileStmt->stmt);
  auto newCond = this->visit(whileStmt->cond);

  whileStmt->stmt = newStmt;
  whileStmt->cond = newCond;

  whileStmt->children.push_back(newStmt);
  whileStmt->children.push_back(newCond);

  return whileStmt;
}

ASTRetJmpStmt *AlgebraSimplificationOpt::visit(ASTRetJmpStmt *retJmpStmt) {
  retJmpStmt->children.clear();
  auto expr = this->visit(retJmpStmt->expr);
  retJmpStmt->expr = expr;
  retJmpStmt->children.push_back(expr);

  return retJmpStmt;
}

ASTGotoLabeledStmt *AlgebraSimplificationOpt::visit(ASTGotoLabeledStmt *gotoLabeledStmt) {
  return gotoLabeledStmt;
}
