#include "ast.hpp"

ASTStmt::ASTStmt() : ASTNode() {}

ASTAssignmentExpr::ASTAssignmentExpr(ASTCondExpr *n) : ASTNode() {
  this->add_child(n);
}
ASTAssignmentExpr::ASTAssignmentExpr(ASTUnaryExpr *n1, ASTAssignmentOp *n2,
                                     ASTAssignmentExpr *n3)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3);
}

ASTExpr::ASTExpr(ASTAssignmentExpr *n) : ASTStmt() {
  if (this->children.size() == 1)
    this->add_child(n->children[0]);
  else
    this->add_child(n);
}

ASTExpr::ASTExpr(ASTExpr *n1, ASTAssignmentExpr *n2) : ASTStmt() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTInitDecl::ASTInitDecl(ASTDirectDeclarator *n1, ASTInitializer *n2)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTInitDecl::ASTInitDecl(ASTDirectDeclarator *n) : ASTNode() {
  this->add_child(n);
}

ASTInitDeclList::ASTInitDeclList(ASTInitDecl *n) : ASTNode() {
  this->add_child(n);
}

ASTInitDeclList::ASTInitDeclList(ASTInitDeclList *n1, ASTInitDecl *n2)
    : ASTNode() {
  for (auto child : n1->children) {
    this->add_child(child);
  }
  this->add_child(n2);
  delete n1;
}

ASTInitializer::ASTInitializer(ASTInitializerList *n) : ASTNode() {
  this->add_child(n);
}
ASTInitializer::ASTInitializer(ASTAssignmentExpr *n) : ASTNode() {
  this->add_child(n);
}

ASTType::ASTType(ttype t) : ASTNode(), t(t) {}

ASTDeclSpec::ASTDeclSpec(ASTType *n) : ASTNode() { this->add_child(n); }

ASTDeclSpec::ASTDeclSpec(ASTType *n1, ASTDeclSpec *n2) : ASTNode() {
  for (auto child : n2->children) {
    this->add_child(child);
  }
  this->add_child(n1);
  delete n2;
}

ASTFnDef::ASTFnDef(ASTDeclSpec *n1, ASTDirectDeclarator *n2, ASTDeclList *n3,
                   ASTBlockItemList *n4)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2, true);
  this->add_child(n3, true);
  this->add_child(n4, true);
}

ASTFnDef::ASTFnDef(ASTDeclSpec *n1, ASTDirectDeclarator *n2,
                   ASTBlockItemList *n3)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2, true);
  this->add_child(n3, true);
}

ASTId::ASTId(string name) : ASTNode(), name(name) {}

ASTDesignator::ASTDesignator(ASTCondExpr *n) : ASTNode() { this->add_child(n); }

ASTDesignator::ASTDesignator(ASTId *n) : ASTNode() { this->add_child(n); }
ASTDesignatorList::ASTDesignatorList(ASTDesignator *n) : ASTNode() {
  this->add_child(n);
}

ASTDesignatorList::ASTDesignatorList(ASTDesignatorList *n1, ASTDesignator *n2)
    : ASTNode() {
  for (auto child : n1->children) {
    this->add_child(child);
  }
  this->add_child(n2);
  delete n1;
}

ASTInitializerList::ASTInitializerList(ASTDesignatorList *n1,
                                       ASTInitializer *n2)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTInitializerList::ASTInitializerList(ASTInitializer *n) : ASTNode() {
  this->add_child(n);
}

ASTInitializerList::ASTInitializerList(ASTInitializerList *n1,
                                       ASTDesignatorList *n2,
                                       ASTInitializer *n3)
    : ASTNode() {
  for (auto child : n1->children) {
    this->add_child(child);
  }
  this->add_child(n2);
  this->add_child(n3);
  delete n1;
}

ASTInitializerList::ASTInitializerList(ASTInitializerList *n1,
                                       ASTInitializer *n2)
    : ASTNode() {
  for (auto child : n1->children) {
    this->add_child(child);
  }
  this->add_child(n2);
  delete n1;
}

ASTDecl::ASTDecl(ASTDeclSpec *n) : ASTNode() { this->add_child(n); }

ASTDecl::ASTDecl(ASTDeclSpec *n1, ASTInitDeclList *n2) : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTDeclList::ASTDeclList() : ASTNode() {}

ASTDeclList::ASTDeclList(ASTDeclList *n1, ASTDecl *n2) : ASTNode() {
  for (auto child : n1->children) {
    this->add_child(child);
  }
  this->add_child(n2);
  delete n1;
}

ASTAssignmentOp::ASTAssignmentOp(assignment_op ap) : ASTNode(), ap(ap) {}

ASTIncOp::ASTIncOp(inc_op ip) : ASTNode(), ip(ip) {}

ASTUnaryOp::ASTUnaryOp(unary_op up) : ASTNode(), up(up) {}

ASTPtrOp::ASTPtrOp(access_op ap) : ASTNode(), ap(ap) {}

ASTRelOp::ASTRelOp(rel_op rp) : ASTNode(), rp(rp) {}

ASTEqOp::ASTEqOp(equal_op ep) : ASTNode(), ep(ep) {}

ASTShiftOp::ASTShiftOp(shift_op sp) : ASTNode(), sp(sp) {}

ASTArithOp::ASTArithOp(arith_op ap) : ASTNode(), ap(ap) {}

ASTConst::ASTConst(const_type t, string value)
    : ASTNode(), ct(t), value(value) {}

ASTIdList::ASTIdList(ASTId *n) : ASTNode() { this->add_child(n); }

ASTIdList::ASTIdList(ASTIdList *n1, ASTId *n2) : ASTNode() {
  for (auto child : n1->children) {
    this->add_child(child);
  }
  this->add_child(n2);
  delete n1;
}

// ASTStrConst::ASTStrConst() : ASTNode() {}

ASTStrLiteralConst::ASTStrLiteralConst() : ASTStrConst() {}

ASTFuncNameConst::ASTFuncNameConst() : ASTStrConst() {}

ASTArgExpList::ASTArgExpList(ASTAssignmentExpr *n) : ASTNode() {
  this->add_child(n);
}

ASTArgExpList::ASTArgExpList(ASTArgExpList *n1, ASTAssignmentExpr *n2)
    : ASTNode() {
  for (auto child : n1->children) {
    this->add_child(child);
  }
  this->add_child(n2);
  delete n1;
}

ASTPrimaryExpr::ASTPrimaryExpr(ASTId *n) : ASTNode() { this->add_child(n); }

ASTPrimaryExpr::ASTPrimaryExpr(ASTConst *n) : ASTNode() { this->add_child(n); }

ASTPrimaryExpr::ASTPrimaryExpr(ASTStrConst *n) : ASTNode() {
  this->add_child(n);
}

ASTPrimaryExpr::ASTPrimaryExpr(ASTExpr *n) : ASTNode() { this->add_child(n); }

ASTPostExpr::ASTPostExpr(ASTPrimaryExpr *n) : ASTNode() { this->add_child(n); }

ASTPostExpr::ASTPostExpr(ASTPostExpr *n1, ASTExpr *n2) : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTPostExpr::ASTPostExpr(ASTPostExpr *n) : ASTNode() { this->add_child(n); }

ASTPostExpr::ASTPostExpr(ASTPostExpr *n1, ASTArgExpList *n2) : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTPostExpr::ASTPostExpr(ASTPostExpr *n1, ASTPtrOp *n2, ASTId *n3) : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3);
}

ASTPostExpr::ASTPostExpr(ASTPostExpr *n1, ASTIncOp *n2) : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTUnaryExpr::ASTUnaryExpr(ASTPostExpr *n) : ASTNode() { this->add_child(n); }

ASTUnaryExpr::ASTUnaryExpr(ASTIncOp *n1, ASTUnaryExpr *n2) : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTUnaryExpr::ASTUnaryExpr(ASTUnaryOp *n1, ASTUnaryExpr *n2) : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}
ASTMulExpr::ASTMulExpr(ASTUnaryExpr *n) : ASTNode() { this->add_child(n); }

ASTMulExpr::ASTMulExpr(ASTMulExpr *n1, ASTArithOp *n2, ASTUnaryExpr *n3)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3);
}

ASTAddExpr::ASTAddExpr(ASTMulExpr *n) : ASTNode() { this->add_child(n); }

ASTAddExpr::ASTAddExpr(ASTAddExpr *n1, ASTArithOp *n2, ASTMulExpr *n3)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3);
}

ASTShiftExpr::ASTShiftExpr(ASTAddExpr *n) : ASTNode() { this->add_child(n); }

ASTShiftExpr::ASTShiftExpr(ASTShiftExpr *n1, ASTShiftOp *n2, ASTAddExpr *n3)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3);
}

ASTRelExpr::ASTRelExpr(ASTShiftExpr *n) : ASTNode() { this->add_child(n); }

ASTRelExpr::ASTRelExpr(ASTRelExpr *n1, ASTRelOp *n2, ASTShiftExpr *n3)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3);
}

ASTEqExpr::ASTEqExpr(ASTRelExpr *n) : ASTNode() { this->add_child(n); }

ASTEqExpr::ASTEqExpr(ASTEqExpr *n1, ASTEqOp *n2, ASTRelExpr *n3) : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3);
}

ASTAndExpr::ASTAndExpr(ASTEqExpr *n) : ASTNode() { this->add_child(n); }

ASTAndExpr::ASTAndExpr(ASTAndExpr *n1, ASTEqExpr *n2) : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTExclusiveOrExpr::ASTExclusiveOrExpr(ASTAndExpr *n) : ASTNode() {
  this->add_child(n);
}

ASTExclusiveOrExpr::ASTExclusiveOrExpr(ASTExclusiveOrExpr *n1, ASTAndExpr *n2)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTInclusiveOrExpr::ASTInclusiveOrExpr(ASTExclusiveOrExpr *n) : ASTNode() {
  this->add_child(n);
}

ASTInclusiveOrExpr::ASTInclusiveOrExpr(ASTInclusiveOrExpr *n1,
                                       ASTExclusiveOrExpr *n2)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTLogicalAndExpr::ASTLogicalAndExpr(ASTInclusiveOrExpr *n) : ASTNode() {
  this->add_child(n);
}

ASTLogicalAndExpr::ASTLogicalAndExpr(ASTLogicalAndExpr *n1,
                                     ASTInclusiveOrExpr *n2)
    : ASTNode() {

  this->add_child(n1);
  this->add_child(n2);
}

ASTLogicalOrExpr::ASTLogicalOrExpr(ASTLogicalAndExpr *n) : ASTNode() {
  this->add_child(n);
}

ASTLogicalOrExpr::ASTLogicalOrExpr(ASTLogicalOrExpr *n1, ASTLogicalAndExpr *n2)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTCondExpr::ASTCondExpr(ASTLogicalOrExpr *n) : ASTNode() {
  this->add_child(n);
}

ASTCondExpr::ASTCondExpr(ASTLogicalOrExpr *n1, ASTExpr *n2, ASTCondExpr *n3)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3);
}

// ASTIterStmt::ASTIterStmt() : ASTStmt() {}

ASTWhileStmt::ASTWhileStmt(ASTExpr *n1, ASTStmt *n2) : ASTIterStmt() {
  this->add_child(n1);
  this->add_child(n2, true);
}

ASTDoWhileStmt::ASTDoWhileStmt(ASTStmt *n1, ASTExpr *n2) : ASTIterStmt() {
  this->add_child(n1, true);
  this->add_child(n2);
}

ASTForStmt::ASTForStmt(ASTExpr *n1, ASTExpr *n2, ASTStmt *n3) : ASTIterStmt() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3, true);
}

ASTForStmt::ASTForStmt(ASTExpr *n1, ASTExpr *n2, ASTExpr *n3, ASTStmt *n4)
    : ASTIterStmt() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3);
  this->add_child(n4, true);
}

ASTForStmt::ASTForStmt(ASTDecl *n1, ASTExpr *n2, ASTStmt *n3) : ASTIterStmt() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3, true);
}

ASTForStmt::ASTForStmt(ASTDecl *n1, ASTExpr *n2, ASTExpr *n3, ASTStmt *n4)
    : ASTIterStmt() {
  this->add_child(n1);
  this->add_child(n2);
  this->add_child(n3);
  this->add_child(n4, true);
}

ASTGotoJmpStmt::ASTGotoJmpStmt(ASTId *n) : ASTJmpStmt() { this->add_child(n); }

ASTContJmpStmt::ASTContJmpStmt() : ASTJmpStmt() {}

ASTBreakJmpStmt::ASTBreakJmpStmt() : ASTJmpStmt() {}

ASTRetJmpStmt::ASTRetJmpStmt() : ASTJmpStmt() {}

ASTRetJmpStmt::ASTRetJmpStmt(ASTExpr *n) : ASTJmpStmt() { this->add_child(n); }
ASTIfSelectStmt::ASTIfSelectStmt(ASTExpr *n1, ASTStmt *n2) : ASTSelectStmt() {
  this->add_child(n1);
  this->add_child(n2, true);
}

ASTIfElseSelectStmt::ASTIfElseSelectStmt(ASTExpr *n1, ASTStmt *n2, ASTStmt *n3)
    : ASTSelectStmt() {
  this->add_child(n1);
  this->add_child(n2, true);
  this->add_child(n3, true);
}

ASTSwitchStmt::ASTSwitchStmt(ASTExpr *n1, ASTStmt *n2) : ASTSelectStmt() {
  this->add_child(n1);
  this->add_child(n2, true);
}

// ASTLabeledStmt::ASTLabeledStmt() : ASTStmt() {}

ASTGotoLabeledStmt::ASTGotoLabeledStmt(ASTId *n1, ASTStmt *n2)
    : ASTLabeledStmt() {
  this->add_child(n1);
  this->add_child(n2, true);
}

ASTCaseLabeledStmt::ASTCaseLabeledStmt(ASTCondExpr *n1, ASTStmt *n2)
    : ASTLabeledStmt() {
  this->add_child(n1);
  this->add_child(n2, true);
}

ASTDefLabeledStmt::ASTDefLabeledStmt(ASTStmt *n) : ASTLabeledStmt() {
  this->add_child(n, true);
}

ASTBlockItem::ASTBlockItem(ASTDecl *n) : ASTNode() { this->add_child(n); }

ASTBlockItem::ASTBlockItem(ASTStmt *n) : ASTNode() { this->add_child(n, true); }

ASTBlockItemList::ASTBlockItemList() : ASTStmt() {}

ASTBlockItemList::ASTBlockItemList(ASTBlockItem *n) : ASTStmt() {
  this->add_child(n);
}

ASTBlockItemList::ASTBlockItemList(ASTBlockItemList *n1, ASTBlockItem *n2)
    : ASTStmt() {
  for (auto child : n1->children) {
    this->add_child(child);
  }
  this->add_child(n2);
  delete n1;
}

ASTPtr::ASTPtr() : ASTNode() {}
// // ASTPtr::ASTPtr(ASTPtr *n) : ASTNode()   {if (n->children.size() == 1) {
//     this->add_child(n->children[0]);
//   } else {
//     this->add_child(n);
//   }

ASTPtr::ASTPtr(ASTPtr *n) : ASTNode() {
  for (auto child : n->children) {
    this->add_child(child);
  }
  delete n;
}

// ASTDirectDeclarator::ASTDirectDeclarator() : ASTNode() {}

ASTIdDeclarator::ASTIdDeclarator(ASTId *n) : ASTDirectDeclarator() {
  this->add_child(n);
}

ASTParamDecl::ASTParamDecl(ASTDeclSpec *n1, ASTDirectDeclarator *n2)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTParamDecl::ASTParamDecl(ASTDeclSpec *n) : ASTNode() { this->add_child(n); }

ASTParamList::ASTParamList(ASTParamDecl *n) : ASTNode() { this->add_child(n); }

ASTParamList::ASTParamList(ASTParamList *n1, ASTParamDecl *n2) : ASTNode() {
  for (auto child : n1->children) {
    this->add_child(child);
  }
  this->add_child(n2);
  delete n1;
}

ASTFnDeclarator::ASTFnDeclarator(ASTDirectDeclarator *n1, ASTParamList *n2)
    : ASTDirectDeclarator() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTFnDeclarator::ASTFnDeclarator(ASTDirectDeclarator *n)
    : ASTDirectDeclarator() {
  this->add_child(n);
}

ASTFnCallDeclarator::ASTFnCallDeclarator(ASTDirectDeclarator *n1, ASTIdList *n2)
    : ASTDirectDeclarator() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTExternDecl::ASTExternDecl(ASTFnDef *n) : ASTNode() { this->add_child(n); }

ASTExternDecl::ASTExternDecl(ASTDecl *n) : ASTNode() { this->add_child(n); }

ASTProgram::ASTProgram(ASTExternDecl *n) : ASTNode() { this->add_child(n); }

ASTProgram::ASTProgram(ASTProgram *n1, ASTExternDecl *n2) : ASTNode() {
  for (auto child : n1->children) {
    this->add_child(child);
  }
  this->add_child(n2->children[0]);
  delete n1;
}
