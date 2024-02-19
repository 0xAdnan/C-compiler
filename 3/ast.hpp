class ASTNode {};

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
  less,
  greater,
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

class ASTInitDeclList;
class ASTDeclSpec;
class ASTDecl;
class ASTDeclList;
class ASTExpr;
class ASTAssignmentExpr;

class ASTStmt : public ASTNode {};

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
  ASTIdList(ASTId *n);
  ASTIdList(ASTIdList *n1, ASTId *n2);
};

class ASTConst : public ASTNode {
public:
  ASTConst(const_type t);
};

class ASTStrConst : public ASTNode {
public:
  ASTStrConst();
};

class ASTFuncName : public ASTNode {
public:
  ASTFuncName();
};

class ASTArgExpList : public ASTNode {
public:
  ASTArgExpList(ASTAssignmentExpr *n);
  ASTArgExpList(ASTArgExpList *n1, ASTAssignmentExpr *n2);
};

class ASTPostExpr : public ASTNode {
public:
  ASTPostExpr(ASTId *n);
  ASTPostExpr(ASTConst *n);
  ASTPostExpr(ASTStrConst *n);
  ASTPostExpr(ASTFuncName *n);
  ASTPostExpr(ASTExpr *n);
  ASTPostExpr(ASTPostExpr *n1, ASTExpr *n2);
  ASTPostExpr(ASTPostExpr *n);
  ASTPostExpr(ASTPostExpr *n1, ASTArgExpList *n2);
  ASTPostExpr(ASTPostExpr *n1, ASTPtrOp *n2, ASTId *n3);
  ASTPostExpr(ASTPostExpr *n1, ASTIncOp *n2);
};

class ASTUnaryExpr : public ASTNode {
public:
  ASTUnaryExpr(ASTPostExpr *n);
  ASTUnaryExpr(ASTIncOp *n1, ASTUnaryExpr *n2);
  ASTUnaryExpr(ASTUnaryOp *n1, ASTUnaryExpr *n2);
};

class ASTMulExpr : public ASTNode {
public:
  ASTMulExpr(ASTMulExpr *n1, ASTArithOp *n2, ASTUnaryExpr *n3);
  ASTMulExpr(ASTUnaryExpr *n1, ASTArithOp *n2, ASTUnaryExpr *n3);
};

class ASTAddExpr : public ASTNode {
public:
  ASTAddExpr(ASTMulExpr *n);
  ASTAddExpr(ASTUnaryExpr *n);
  ASTAddExpr(ASTAddExpr *n1, ASTArithOp *n2, ASTMulExpr *n3);
  ASTAddExpr(ASTAddExpr *n1, ASTArithOp *n2, ASTUnaryExpr *n3);
};

class ASTShiftExpr : public ASTNode {
public:
  ASTShiftExpr(ASTAddExpr *n);
  ASTShiftExpr(ASTShiftExpr *n1, ASTShiftOp *n2, ASTAddExpr *n3);
};

class ASTRelExpr : public ASTNode {
public:
  ASTRelExpr(ASTShiftExpr *n);
  ASTRelExpr(ASTRelExpr *n1, ASTRelOp *n2, ASTShiftExpr *n3);
};

class ASTEqExpr : public ASTNode {
public:
  ASTEqExpr(ASTRelExpr *n);
  ASTEqExpr(ASTEqExpr *n1, ASTEqOp *n2, ASTRelExpr *n3);
};

class ASTAndExpr : public ASTNode {
public:
  ASTAndExpr(ASTEqExpr *n);
  ASTAndExpr(ASTAndExpr *n1, ASTEqExpr *n2);
};

class ASTExclusiveOrExpr : public ASTNode {
public:
  ASTExclusiveOrExpr(ASTAndExpr *n);
  ASTExclusiveOrExpr(ASTAndExpr *n1, ASTAndExpr *n2);
};

class ASTInclusiveOrExpr : public ASTNode {
public:
  ASTInclusiveOrExpr(ASTExclusiveOrExpr *n);
  ASTInclusiveOrExpr(ASTInclusiveOrExpr *n1, ASTExclusiveOrExpr *n2);
};

class ASTLogicalAndExpr : public ASTNode {
public:
  ASTLogicalAndExpr(ASTInclusiveOrExpr *n);
  ASTLogicalAndExpr(ASTLogicalAndExpr *n1, ASTInclusiveOrExpr *n2);
};

class ASTLogicalOrExpr : public ASTNode {
public:
  ASTLogicalOrExpr(ASTLogicalAndExpr *n);
  ASTLogicalOrExpr(ASTLogicalOrExpr *n1, ASTExpr *n2, ASTLogicalAndExpr *n3);
};

class ASTCondExpr : public ASTNode {
public:
  ASTCondExpr(ASTLogicalOrExpr *n);
  ASTCondExpr(ASTLogicalOrExpr *n1, ASTExpr *n2, ASTCondExpr *n3);
};

class ASTAssignmentExpr : public ASTNode {
public:
  ASTAssignmentExpr(ASTCondExpr *n);
  ASTAssignmentExpr(ASTUnaryExpr *n1, ASTAssignmentOp *n2,
                    ASTAssignmentExpr *n3);
};

class ASTExpr : public ASTNode {
public:
  ASTExpr(ASTAssignmentExpr *n);
  ASTExpr(ASTExpr *n1, ASTAssignmentExpr *n2);
};

// ///////////////// STATEMENT /////////////////

/*  ITER Statements */
class ASTIterStmt : public ASTStmt {};

class ASTWhileStmt : public ASTIterStmt {
public:
  ASTWhileStmt(ASTExpr *n1, ASTStmt *n2);
};

class ASTDoWhileStmt : public ASTIterStmt {
public:
  ASTDoWhileStmt(ASTStmt *n1, ASTExpr *n2);
};

class ASTForStmt : public ASTIterStmt {
public:
  ASTForStmt(ASTExpr *n1, ASTExpr *n2, ASTStmt *n3);
  ASTForStmt(ASTExpr *n1, ASTExpr *n2, ASTExpr *n3, ASTStmt *n4);
  ASTForStmt(ASTDecl *n1, ASTExpr *n2, ASTStmt *n3);
  ASTForStmt(ASTDecl *n1, ASTExpr *n2, ASTExpr *n3, ASTStmt *n4);
};

/*  JUMP Statements */
class ASTJmpStmt : public ASTStmt {};

class ASTGotoJmptStmt : public ASTJmpStmt {
public:
  ASTGotoJmptStmt(ASTId *n);
};

class ASTContJmptStmt : public ASTJmpStmt {
public:
  ASTContJmptStmt();
};

class ASTBreakJmptStmt : public ASTJmpStmt {
public:
  ASTBreakJmptStmt();
};

class ASTRetJmptStmt : public ASTJmpStmt {
public:
  ASTRetJmptStmt();
  ASTRetJmptStmt(ASTExpr *n);
};

/*  SELECT Statements */
class ASTSelectStmt : public ASTStmt {};

class ASTIfElseSelectStmt : public ASTSelectStmt {
public:
  ASTIfElseSelectStmt(ASTExpr *n1, ASTStmt *n2, ASTStmt *n3);
};

class ASTIfSelectStmt : public ASTSelectStmt {
  ASTIfSelectStmt(ASTExpr *n1, ASTStmt *n2);
};

class ASTSwitchStmt : public ASTSelectStmt {
  ASTSwitchStmt(ASTExpr *n1, ASTStmt *n2);
};

/*  LABELED Statements */
class ASTLabeledStmt : public ASTStmt {};

class ASTGotoLabeledStmt : public ASTLabeledStmt {
public:
  ASTGotoLabeledStmt(ASTId *n1, ASTStmt *n2);
};

class ASTCaseLabeledStmt : public ASTLabeledStmt {
public:
  ASTCaseLabeledStmt(ASTCondExpr *n1, ASTStmt *n2);
};

class ASTDefLabeledStmt : public ASTLabeledStmt {
public:
  ASTDefLabeledStmt(ASTStmt *n);
};

// /////////////////////////////////////////////////

class ASTBlockItemList : public ASTNode {
public:
  ASTBlockItemList(ASTDecl *n);
  ASTBlockItemList(ASTStmt *n);
  ASTBlockItemList(ASTBlockItemList *n1, ASTDecl *n2);
  ASTBlockItemList(ASTBlockItemList *n1, ASTStmt *n2);
};

class ASTPtr : public ASTNode {
public:
  ASTPtr();
  ASTPtr(ASTPtr *n);
};

class ASTDeclarator : public ASTNode {
public:
  ASTDeclarator(ASTPtr *n1, ASTDeclarator *n2);
};

class ASTIdDeclarator : public ASTDeclarator {
public:
  ASTIdDeclarator(ASTId *n);
};

class ASTParamDecl : public ASTNode {
public:
  ASTParamDecl(ASTDeclSpec *n1, ASTDeclarator *n2);
  ASTParamDecl(ASTDeclSpec *n);
};

class ASTParamList : public ASTNode {
public:
  ASTParamList(ASTParamDecl *n);
  ASTParamList(ASTParamList *n1, ASTParamDecl *n2);
};

class ASTFnDeclarator : public ASTDeclarator {
public:
  ASTFnDeclarator(ASTDeclarator *n1, ASTParamList *n2);
  ASTFnDeclarator(ASTDeclarator *n1);
};

class ASTFnCallDeclarator : public ASTDeclarator {
public:
  ASTFnCallDeclarator(ASTDeclarator *n1, ASTIdList *n2);
};

class ASTFnDef : public ASTNode {
public:
  ASTFnDef(ASTDeclSpec *n1, ASTDeclarator *n2, ASTDeclList *n3,
           ASTBlockItemList *n4);
  ASTFnDef(ASTDeclSpec *n1, ASTDeclarator *n2, ASTBlockItemList *n3);
};

class ASTDeclSpec : public ASTNode {
public:
  ASTDeclSpec(ASTType *n1, ASTDeclSpec *n2);
  ASTDeclSpec(ASTType *n);
};

class ASTDecl : public ASTNode {
public:
  ASTDecl(ASTDeclSpec *n);
  ASTDecl(ASTDeclSpec *n1, ASTInitDeclList *n2);
};

class ASTDesignatorList : public ASTNode {
public:
  ASTDesignatorList(ASTCondExpr *n);
  ASTDesignatorList(ASTId *n);
  ASTDesignatorList(ASTDesignatorList *n1, ASTCondExpr *n2);
  ASTDesignatorList(ASTDesignatorList *n1, ASTId *n2);
};

class ASTInitializerList : public ASTNode {
public:
  ASTInitializerList(ASTDesignatorList *n1, ASTInitializerList *n2);
  ASTInitializerList(ASTDesignatorList *n1, ASTAssignmentExpr *n2);
  ASTInitializerList(ASTInitializerList *n);
  ASTInitializerList(ASTAssignmentExpr *n);
  ASTInitializerList(ASTInitializerList *n1, ASTDesignatorList *n2,
                     ASTInitializerList *n3);
  ASTInitializerList(ASTInitializerList *n1, ASTDesignatorList *n2,
                     ASTAssignmentExpr *n3);
  ASTInitializerList(ASTInitializerList *n1, ASTInitializerList *n2);
  ASTInitializerList(ASTInitializerList *n1, ASTAssignmentExpr *n2);
};

class ASTInitDecl : public ASTNode {
public:
  ASTInitDecl(ASTDecl *n1, ASTInitializerList *n2);
  ASTInitDecl(ASTDecl *n1, ASTAssignmentExpr *n2);
  ASTInitDecl(ASTDecl *n);
};

class ASTInitDeclList : public ASTNode {
public:
  ASTInitDeclList(ASTInitDecl *n2);
  ASTInitDeclList(ASTInitDeclList *n1, ASTInitDecl *n2);
};

class ASTExternDecl : public ASTNode {
public:
  ASTExternDecl(ASTFnDef *n);
  ASTExternDecl(ASTDecl *n);
};

class ASTProgram : public ASTNode {
public:
  ASTProgram();
  ASTProgram(ASTExternDecl *n1);
  ASTProgram(ASTProgram *n1, ASTExternDecl *n2);
};
