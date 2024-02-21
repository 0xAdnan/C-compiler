#include <iostream>
#include <vector>

using namespace std;

class ASTNode {
protected:
  vector<ASTNode *> children;

  ASTNode() { children = vector<ASTNode *>(); }

  void add_child(ASTNode *child) { this->children.push_back(child); }

  virtual string to_str() = 0;

public:
  string dump_ast(int indent) {
    string x = this->to_str();
    indent++;
    for (auto child : children) {
      x += child->dump_ast(indent);
    }
    return x;
  }
};

enum ttype {
  tvoid,
  tchar,
  tshort,
  tint,
  tlong,
  tfloat,
  tdouble,
  tsigned,
  tunsigned,
  tbool,
  tcomplex,
  timaginary
};

enum assignment_op {
  assign,
  mul_assign,
  div_assign,
  mod_assign,
  add_assign,
  sub_assign,
  left_assign,
  right_assign,
  and_assign,
  xor_assign,
  or_assign,

};

enum inc_op {
  plus_plus,
  minus_minus,
};

enum unary_op {
  u_op_and,
  u_op_star,
  u_op_plus,
  u_op_minus,
  u_op_tilde,
  u_op_not,
};

enum access_op {
  dot_op,
  ptr_op,
};

enum const_type {
  i_const,
  f_const,
};

enum equal_op {
  eq_op,
  neq_op,
};

enum rel_op {
  less_op,
  greater_op,
  less_eq,
  greater_eq,
};

enum shift_op {
  left_shift_op,
  right_shift_op,
};

enum arith_op {
  add_op,
  minus_op,
  mul_op,
  div_op,
  remainder_op,
};

class ASTInitDecl;
class ASTType;
class ASTDeclList;
class ASTExpr;
class ASTAssignmentExpr;
class ASTInitializerList;
class ASTCondExpr;
class ASTUnaryExpr;
class ASTAssignmentOp;

class ASTStmt : public ASTNode {
protected:
  ASTStmt() : ASTNode() {}
};

class ASTExpr : public ASTStmt {
public:
  ASTExpr(ASTAssignmentExpr *n);
  ASTExpr(ASTExpr *n1, ASTAssignmentExpr *n2);
};

class ASTAssignmentExpr : public ASTNode {
public:
  ASTAssignmentExpr(ASTCondExpr *n);
  ASTAssignmentExpr(ASTUnaryExpr *n1, ASTAssignmentOp *n2,
                    ASTAssignmentExpr *n3);
};

class ASTInitDeclList : public ASTNode {
public:
  ASTInitDeclList(ASTInitDecl *n);
  ASTInitDeclList(ASTInitDeclList *n1, ASTInitDecl *n2);
};

class ASTDeclSpec : public ASTNode {
public:
  ASTDeclSpec(ASTType *n);
  ASTDeclSpec(ASTType *n1, ASTDeclSpec *n2);
};

class ASTDecl : public ASTNode {
public:
  ASTDecl(ASTDeclSpec *n);
  ASTDecl(ASTDeclSpec *n1, ASTInitDeclList *n2);
};

class ASTInitializer : public ASTNode {
public:
  ASTInitializer(ASTInitializerList *n);
  ASTInitializer(ASTAssignmentExpr *n);
};

class ASTType : public ASTNode {
public:
  ASTType(ttype t);
};

class ASTAssignmentOp : public ASTNode {
public:
  ASTAssignmentOp(assignment_op ap);
};

class ASTIncOp : public ASTNode {
public:
  ASTIncOp(inc_op ip);
};

class ASTUnaryOp : public ASTNode {
public:
  ASTUnaryOp(unary_op up);
};

class ASTPtrOp : public ASTNode {
public:
  ASTPtrOp(access_op pp);
};

class ASTRelOp : public ASTNode {
public:
  ASTRelOp(rel_op rp);
};

class ASTEqOp : public ASTNode {
public:
  ASTEqOp(equal_op ep);
};

class ASTShiftOp : public ASTNode {
public:
  ASTShiftOp(shift_op sp);
};

class ASTArithOp : public ASTNode {
public:
  ASTArithOp(arith_op ap);
};

class ASTId : public ASTNode {
public:
  ASTId();
};

class ASTIdList : public ASTNode {
public:
  ASTIdList(ASTId *n) : ASTNode() { this->add_child(n); }
  ASTIdList(ASTIdList *n1, ASTId *n2);
};

class ASTConst : public ASTNode {
public:
  ASTConst(const_type t);
};

class ASTStrConst : public ASTNode {};

class ASTStrLiteralConst : public ASTStrConst {
  virtual string to_str() = 0;

public:
  ASTStrLiteralConst();
};

class ASTFuncNameConst : public ASTStrConst {
public:
  ASTFuncNameConst();
};

class ASTArgExpList : public ASTNode {
public:
  ASTArgExpList(ASTAssignmentExpr *n) : ASTNode() { this->add_child(n); }
  ASTArgExpList(ASTArgExpList *n1, ASTAssignmentExpr *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTPrimaryExpr : public ASTNode {
public:
  ASTPrimaryExpr(ASTId *n) : ASTNode() { this->add_child(n); }
  ASTPrimaryExpr(ASTConst *n) : ASTNode() { this->add_child(n); }
  ASTPrimaryExpr(ASTStrConst *n) : ASTNode() { this->add_child(n); }
  ASTPrimaryExpr(ASTExpr *n) : ASTNode() { this->add_child(n); }
};

class ASTPostExpr : public ASTNode {
public:
  ASTPostExpr(ASTPrimaryExpr *n) : ASTNode() { this->add_child(n); }
  ASTPostExpr(ASTPostExpr *n1, ASTExpr *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
  ASTPostExpr(ASTPostExpr *n) : ASTNode() { this->add_child(n); }
  ASTPostExpr(ASTPostExpr *n1, ASTArgExpList *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
  ASTPostExpr(ASTPostExpr *n1, ASTPtrOp *n2, ASTId *n3) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  ASTPostExpr(ASTPostExpr *n1, ASTIncOp *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTUnaryExpr : public ASTNode {
public:
  ASTUnaryExpr(ASTPostExpr *n) : ASTNode() { this->add_child(n); }
  ASTUnaryExpr(ASTIncOp *n1, ASTUnaryExpr *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
  ASTUnaryExpr(ASTUnaryOp *n1, ASTUnaryExpr *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTMulExpr : public ASTNode {
public:
  ASTMulExpr(ASTUnaryExpr *n) : ASTNode() { this->add_child(n); }
  ASTMulExpr(ASTMulExpr *n1, ASTArithOp *n2, ASTUnaryExpr *n3) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  ASTMulExpr(ASTUnaryExpr *n1, ASTArithOp *n2, ASTUnaryExpr *n3) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
};

class ASTAddExpr : public ASTNode {
public:
  ASTAddExpr(ASTMulExpr *n) : ASTNode() { this->add_child(n); }
  ASTAddExpr(ASTUnaryExpr *n) : ASTNode() { this->add_child(n); }
  ASTAddExpr(ASTAddExpr *n1, ASTArithOp *n2, ASTMulExpr *n3) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  ASTAddExpr(ASTAddExpr *n1, ASTArithOp *n2, ASTUnaryExpr *n3) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
};

class ASTShiftExpr : public ASTNode {
public:
  ASTShiftExpr(ASTAddExpr *n) : ASTNode() { this->add_child(n); }
  ASTShiftExpr(ASTShiftExpr *n1, ASTShiftOp *n2, ASTAddExpr *n3) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
};

class ASTRelExpr : public ASTNode {
public:
  ASTRelExpr(ASTShiftExpr *n) : ASTNode() { this->add_child(n); }
  ASTRelExpr(ASTRelExpr *n1, ASTRelOp *n2, ASTShiftExpr *n3) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
};

class ASTEqExpr : public ASTNode {
public:
  ASTEqExpr(ASTRelExpr *n) : ASTNode() { this->add_child(n); }
  ASTEqExpr(ASTEqExpr *n1, ASTEqOp *n2, ASTRelExpr *n3) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
};

class ASTAndExpr : public ASTNode {
public:
  ASTAndExpr(ASTEqExpr *n) : ASTNode() { this->add_child(n); }
  ASTAndExpr(ASTAndExpr *n1, ASTEqExpr *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTExclusiveOrExpr : public ASTNode {
public:
  ASTExclusiveOrExpr(ASTAndExpr *n) : ASTNode() { this->add_child(n); }
  ASTExclusiveOrExpr(ASTExclusiveOrExpr *n1, ASTAndExpr *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTInclusiveOrExpr : public ASTNode {
public:
  ASTInclusiveOrExpr(ASTExclusiveOrExpr *n) : ASTNode() { this->add_child(n); }
  ASTInclusiveOrExpr(ASTInclusiveOrExpr *n1, ASTExclusiveOrExpr *n2)
      : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTLogicalAndExpr : public ASTNode {
public:
  ASTLogicalAndExpr(ASTInclusiveOrExpr *n) : ASTNode() { this->add_child(n); }
  ASTLogicalAndExpr(ASTLogicalAndExpr *n1, ASTInclusiveOrExpr *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTLogicalOrExpr : public ASTNode {
public:
  ASTLogicalOrExpr(ASTLogicalAndExpr *n) : ASTNode() { this->add_child(n); }
  ASTLogicalOrExpr(ASTLogicalOrExpr *n1, ASTLogicalAndExpr *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTCondExpr : public ASTNode {
public:
  ASTCondExpr(ASTLogicalOrExpr *n) : ASTNode() { this->add_child(n); }
  ASTCondExpr(ASTLogicalOrExpr *n1, ASTExpr *n2, ASTCondExpr *n3) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
};

ASTExpr::ASTExpr(ASTAssignmentExpr *n) : ASTStmt() { this->add_child(n); }
ASTExpr::ASTExpr(ASTExpr *n1, ASTAssignmentExpr *n2) : ASTStmt() {
  this->add_child(n1);
  this->add_child(n2);
}

// ///////////////// STATEMENT /////////////////

/*  ITER Statements */
class ASTIterStmt : public ASTStmt {};

class ASTWhileStmt : public ASTIterStmt {
public:
  ASTWhileStmt(ASTExpr *n1, ASTStmt *n2) : ASTIterStmt() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTDoWhileStmt : public ASTIterStmt {
public:
  ASTDoWhileStmt(ASTStmt *n1, ASTExpr *n2) : ASTIterStmt() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTForStmt : public ASTIterStmt {
public:
  ASTForStmt(ASTExpr *n1, ASTExpr *n2, ASTStmt *n3) : ASTIterStmt() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  ASTForStmt(ASTExpr *n1, ASTExpr *n2, ASTExpr *n3, ASTStmt *n4)
      : ASTIterStmt() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
    this->add_child(n4);
  }
  ASTForStmt(ASTDecl *n1, ASTExpr *n2, ASTStmt *n3) : ASTIterStmt() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  ASTForStmt(ASTDecl *n1, ASTExpr *n2, ASTExpr *n3, ASTStmt *n4)
      : ASTIterStmt() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
    this->add_child(n4);
  }
};

/*  JUMP Statements */
class ASTJmpStmt : public ASTStmt {
protected:
  ASTJmpStmt() : ASTStmt() {}
};

class ASTGotoJmpStmt : public ASTJmpStmt {
public:
  ASTGotoJmpStmt(ASTId *n) : ASTJmpStmt() { this->add_child(n); }
};

class ASTContJmpStmt : public ASTJmpStmt {
public:
  ASTContJmpStmt();
};

class ASTBreakJmpStmt : public ASTJmpStmt {
public:
  ASTBreakJmpStmt();
};

class ASTRetJmpStmt : public ASTJmpStmt {
public:
  ASTRetJmpStmt();
  ASTRetJmpStmt(ASTExpr *n) : ASTJmpStmt() { this->add_child(n); }
};

/*  SELECT Statements */
class ASTSelectStmt : public ASTStmt {};

class ASTIfElseSelectStmt : public ASTSelectStmt {
public:
  ASTIfElseSelectStmt(ASTExpr *n1, ASTStmt *n2, ASTStmt *n3) : ASTSelectStmt() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
};

class ASTIfSelectStmt : public ASTSelectStmt {
public:
  ASTIfSelectStmt(ASTExpr *n1, ASTStmt *n2) : ASTSelectStmt() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTSwitchStmt : public ASTSelectStmt {
public:
  ASTSwitchStmt(ASTExpr *n1, ASTStmt *n2) : ASTSelectStmt() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

/*  LABELED Statements */
class ASTLabeledStmt : public ASTStmt {};

class ASTGotoLabeledStmt : public ASTLabeledStmt {
public:
  ASTGotoLabeledStmt(ASTId *n1, ASTStmt *n2) : ASTLabeledStmt() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTCaseLabeledStmt : public ASTLabeledStmt {
public:
  ASTCaseLabeledStmt(ASTCondExpr *n1, ASTStmt *n2) : ASTLabeledStmt() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTDefLabeledStmt : public ASTLabeledStmt {
public:
  ASTDefLabeledStmt(ASTStmt *n) : ASTLabeledStmt() { this->add_child(n); }
};

// /////////////////////////////////////////////////

class ASTBlockItem : public ASTNode {
public:
  ASTBlockItem(ASTDecl *n) : ASTNode() { this->add_child(n); }
  ASTBlockItem(ASTStmt *n) : ASTNode() { this->add_child(n); }
};

class ASTBlockItemList : public ASTStmt {
public:
  ASTBlockItemList(ASTBlockItem *n) : ASTStmt() { this->add_child(n); }
  ASTBlockItemList(ASTBlockItemList *n1, ASTBlockItem *n2) : ASTStmt() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTPtr : public ASTNode {
public:
  ASTPtr();
  ASTPtr(ASTPtr *n) : ASTNode() { this->add_child(n); }
};

class ASTDirectDeclarator : public ASTNode {};

class ASTIdDeclarator : public ASTDirectDeclarator {
public:
  ASTIdDeclarator(ASTId *n) : ASTDirectDeclarator() { this->add_child(n); }
};

class ASTParamDecl : public ASTNode {
public:
  ASTParamDecl(ASTDeclSpec *n1, ASTDirectDeclarator *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
  ASTParamDecl(ASTDeclSpec *n) : ASTNode() { this->add_child(n); }
};

class ASTParamList : public ASTNode {
public:
  ASTParamList(ASTParamDecl *n) : ASTNode() { this->add_child(n); }
  ASTParamList(ASTParamList *n1, ASTParamDecl *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTFnDeclarator : public ASTDirectDeclarator {
public:
  ASTFnDeclarator(ASTDirectDeclarator *n1, ASTParamList *n2)
      : ASTDirectDeclarator() {
    this->add_child(n1);
    this->add_child(n2);
  }
  ASTFnDeclarator(ASTDirectDeclarator *n) : ASTDirectDeclarator() {
    this->add_child(n);
  }
};

class ASTFnCallDeclarator : public ASTDirectDeclarator {
public:
  ASTFnCallDeclarator(ASTDirectDeclarator *n1, ASTIdList *n2)
      : ASTDirectDeclarator() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTDeclList : public ASTNode {
public:
  ASTDeclList() : ASTNode() {}
  ASTDeclList(ASTDeclList *n1, ASTDecl *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTFnDef : public ASTNode {
public:
  ASTFnDef(ASTDeclSpec *n1, ASTDirectDeclarator *n2, ASTDeclList *n3,
           ASTBlockItemList *n4)
      : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
    this->add_child(n4);
  }
  ASTFnDef(ASTDeclSpec *n1, ASTDirectDeclarator *n2, ASTBlockItemList *n3)
      : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
};

ASTDeclSpec::ASTDeclSpec(ASTType *n) : ASTNode() { this->add_child(n); }
ASTDeclSpec::ASTDeclSpec(ASTType *n1, ASTDeclSpec *n2) : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

ASTDecl::ASTDecl(ASTDeclSpec *n) : ASTNode() {}
ASTDecl::ASTDecl(ASTDeclSpec *n1, ASTInitDeclList *n2) : ASTNode() {}

class ASTDesignator : public ASTNode {
public:
  ASTDesignator(ASTCondExpr *n) : ASTNode() { this->add_child(n); }
  ASTDesignator(ASTId *n) : ASTNode() { this->add_child(n); }
};

class ASTDesignatorList : public ASTNode {
public:
  ASTDesignatorList(ASTDesignator *n) : ASTNode() { this->add_child(n); }
  ASTDesignatorList(ASTDesignatorList *n1, ASTDesignator *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};

class ASTInitializerList : public ASTNode {
public:
  ASTInitializerList(ASTDesignatorList *n1, ASTInitializer *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
  ASTInitializerList(ASTInitializer *n) : ASTNode() { this->add_child(n); }
  ASTInitializerList(ASTInitializerList *n1, ASTDesignatorList *n2,
                     ASTInitializer *n3)
      : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  ASTInitializerList(ASTInitializerList *n1, ASTInitializer *n2);
};

ASTInitializer::ASTInitializer(ASTInitializerList *n) : ASTNode() {
  this->add_child(n);
}
ASTInitializer::ASTInitializer(ASTAssignmentExpr *n) : ASTNode() {
  this->add_child(n);
}

class ASTInitDecl : public ASTNode {
public:
  ASTInitDecl(ASTDirectDeclarator *n1, ASTInitializer *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
  ASTInitDecl(ASTDirectDeclarator *n) : ASTNode() { this->add_child(n); }
};

ASTInitDeclList::ASTInitDeclList(ASTInitDecl *n) : ASTNode() {
  this->add_child(n);
}
ASTInitDeclList::ASTInitDeclList(ASTInitDeclList *n1, ASTInitDecl *n2)
    : ASTNode() {
  this->add_child(n1);
  this->add_child(n2);
}

class ASTExternDecl : public ASTNode {
public:
  ASTExternDecl(ASTFnDef *n) : ASTNode() { this->add_child(n); }
  ASTExternDecl(ASTDecl *n) : ASTNode() { this->add_child(n); }
};

class ASTProgram : public ASTNode {
public:
  ASTProgram(ASTExternDecl *n1) : ASTNode() { this->add_child(n1); }
  ASTProgram(ASTProgram *n1, ASTExternDecl *n2) : ASTNode() {
    this->add_child(n1);
    this->add_child(n2);
  }
};
