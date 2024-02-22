#ifndef AST_HPP_INCLUDED
#define AST_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "magic_enum.hpp"
using namespace std;

class ASTNode
{
protected:
  vector<ASTNode *> children;

  ASTNode() { children = vector<ASTNode *>(); }

  void add_child(ASTNode *child) { this->children.push_back(child); }

  virtual string to_str() = 0;

public:
  void dump_ast(int indent)
  {
    for (int i = 0; i < indent; i++)
      cout << "    ";

    cout << this->to_str() << endl;

    indent++;
    for (auto child : children)
    {
      child->dump_ast(indent);
    }
  }
};

enum ttype
{
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

enum assignment_op
{
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

enum inc_op
{
  plus_plus,
  minus_minus,
};

enum unary_op
{
  u_op_and,
  u_op_star,
  u_op_plus,
  u_op_minus,
  u_op_tilde,
  u_op_not,
};

enum access_op
{
  dot_op,
  ptr_op,
};

enum const_type
{
  i_const,
  f_const,
};

enum equal_op
{
  eq_op,
  neq_op,
};

enum rel_op
{
  less_op,
  greater_op,
  less_eq,
  greater_eq,
};

enum shift_op
{
  left_shift_op,
  right_shift_op,
};

enum arith_op
{
  add_op,
  minus_op,
  mul_op,
  div_op,
  remainder_op,
};

class ASTDeclList;
class ASTDirectDeclarator;
class ASTInitializer;
class ASTInitializerList;
class ASTCondExpr;
class ASTUnaryExpr;
class ASTAssignmentOp;

class ASTStmt : public ASTNode
{
protected:
  ASTStmt() : ASTNode() {}
};

class ASTAssignmentExpr : public ASTNode
{
public:
  ASTAssignmentExpr(ASTCondExpr *n);
  ASTAssignmentExpr(ASTUnaryExpr *n1, ASTAssignmentOp *n2, ASTAssignmentExpr *n3);
  string to_str() override;
};

class ASTExpr : public ASTStmt
{
public:
  ASTExpr(ASTAssignmentExpr *n);
  ASTExpr(ASTExpr *n1, ASTAssignmentExpr *n2);
  string to_str() override;
};

class ASTInitDecl : public ASTNode
{
public:
  ASTInitDecl(ASTDirectDeclarator *n1, ASTInitializer *n2);
  ASTInitDecl(ASTDirectDeclarator *n);
  string to_str() override;
};

class ASTInitializer : public ASTNode
{
public:
  ASTInitializer(ASTInitializerList *n);
  ASTInitializer(ASTAssignmentExpr *n);
  string to_str() override;
};

class ASTAssignmentOp : public ASTNode
{
protected:
  assignment_op ap;

public:
  ASTAssignmentOp(assignment_op ap) : ap(ap) {}
  string to_str() override { return magic_enum::enum_name(ap).data(); }
};

class ASTIncOp : public ASTNode
{
protected:
  inc_op ip;

public:
  ASTIncOp(inc_op ip) : ip(ip) {}
  string to_str() override { return magic_enum::enum_name(ip).data(); }
};

class ASTUnaryOp : public ASTNode
{
protected:
  unary_op up;

public:
  ASTUnaryOp(unary_op up) : up(up) {}
  string to_str() override { return magic_enum::enum_name(up).data(); }
};

class ASTPtrOp : public ASTNode
{
protected:
  access_op ap;

public:
  ASTPtrOp(access_op ap) : ap(ap) {}
  string to_str() override { return magic_enum::enum_name(ap).data(); }
};

class ASTRelOp : public ASTNode
{
protected:
  rel_op rp;

public:
  ASTRelOp(rel_op rp) : rp(rp) {}
  string to_str() override { return magic_enum::enum_name(rp).data(); }
};

class ASTEqOp : public ASTNode
{
protected:
  equal_op ep;

public:
  ASTEqOp(equal_op ep) : ep(ep) {}
  string to_str() override { return magic_enum::enum_name(ep).data(); }
};

class ASTShiftOp : public ASTNode
{
protected:
  shift_op sp;

public:
  ASTShiftOp(shift_op sp) : sp(sp) {}
  string to_str() override { return magic_enum::enum_name(sp).data(); }
};

class ASTArithOp : public ASTNode
{
protected:
  arith_op ap;

public:
  ASTArithOp(arith_op ap) : ap(ap) {}
  string to_str() override { return magic_enum::enum_name(ap).data(); }
};

class ASTConst : public ASTNode
{
protected:
  const_type ct;

public:
  ASTConst(const_type t) : ct(t) {}
  string to_str() override { return magic_enum::enum_name(ct).data(); }
};

class ASTId : public ASTNode
{
public:
  ASTId() {}
  string to_str() override { return "Identifier"; }
};

class ASTIdList : public ASTNode
{
public:
  ASTIdList(ASTId *n) : ASTNode() { this->add_child(n); }
  ASTIdList(ASTIdList *n1, ASTId *n2)
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "IdentifierList"; }
};

class ASTStrLiteralConst : public ASTStrConst
{
public:
  ASTStrLiteralConst() {}
  string to_str() override { return "StringLiteral"; }
};

class ASTFuncNameConst : public ASTStrConst
{
public:
  ASTFuncNameConst() {}
  string to_str() override { return "FunctionName"; }
};

class ASTArgExpList : public ASTNode
{
public:
  ASTArgExpList(ASTAssignmentExpr *n) : ASTNode() { this->add_child(n); }
  ASTArgExpList(ASTArgExpList *n1, ASTAssignmentExpr *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "ArgumentList"; }
};

class ASTPrimaryExpr : public ASTNode
{
public:
  ASTPrimaryExpr(ASTId *n) : ASTNode() { this->add_child(n); }
  ASTPrimaryExpr(ASTConst *n) : ASTNode() { this->add_child(n); }
  ASTPrimaryExpr(ASTStrConst *n) : ASTNode() { this->add_child(n); }
  ASTPrimaryExpr(ASTExpr *n) : ASTNode() { this->add_child(n); }
  string to_str() override { return "PrimaryExpression"; }
};

class ASTPostExpr : public ASTNode
{
public:
  ASTPostExpr(ASTPrimaryExpr *n) : ASTNode() { this->add_child(n); }
  ASTPostExpr(ASTPostExpr *n1, ASTExpr *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  ASTPostExpr(ASTPostExpr *n) : ASTNode() { this->add_child(n); }
  ASTPostExpr(ASTPostExpr *n1, ASTArgExpList *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  ASTPostExpr(ASTPostExpr *n1, ASTPtrOp *n2, ASTId *n3) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  ASTPostExpr(ASTPostExpr *n1, ASTIncOp *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "PostFixExpression"; }
};

class ASTUnaryExpr : public ASTNode
{
public:
  ASTUnaryExpr(ASTPostExpr *n) : ASTNode() { this->add_child(n); }
  ASTUnaryExpr(ASTIncOp *n1, ASTUnaryExpr *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  ASTUnaryExpr(ASTUnaryOp *n1, ASTUnaryExpr *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "UnaryExpression"; }
};

class ASTMulExpr : public ASTNode
{
public:
  ASTMulExpr(ASTUnaryExpr *n) : ASTNode() { this->add_child(n); }
  ASTMulExpr(ASTMulExpr *n1, ASTArithOp *n2, ASTUnaryExpr *n3) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  string to_str() override { return "MultiplicationExpression"; }
};

class ASTAddExpr : public ASTNode
{
public:
  ASTAddExpr(ASTMulExpr *n) : ASTNode() { this->add_child(n); }
  ASTAddExpr(ASTAddExpr *n1, ASTArithOp *n2, ASTMulExpr *n3) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  string to_str() override { return "AddExpression"; }
};

class ASTShiftExpr : public ASTNode
{
public:
  ASTShiftExpr(ASTAddExpr *n) : ASTNode() { this->add_child(n); }
  ASTShiftExpr(ASTShiftExpr *n1, ASTShiftOp *n2, ASTAddExpr *n3) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  string to_str() override { return "ShiftExpression"; }
};

class ASTRelExpr : public ASTNode
{
public:
  ASTRelExpr(ASTShiftExpr *n) : ASTNode() { this->add_child(n); }
  ASTRelExpr(ASTRelExpr *n1, ASTRelOp *n2, ASTShiftExpr *n3) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  string to_str() override { return "RelationalExpression"; }
};

class ASTEqExpr : public ASTNode
{
public:
  ASTEqExpr(ASTRelExpr *n) : ASTNode() { this->add_child(n); }
  ASTEqExpr(ASTEqExpr *n1, ASTEqOp *n2, ASTRelExpr *n3) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  string to_str() override { return "EqualExpression"; }
};

class ASTAndExpr : public ASTNode
{
public:
  ASTAndExpr(ASTEqExpr *n) : ASTNode() { this->add_child(n); }
  ASTAndExpr(ASTAndExpr *n1, ASTEqExpr *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "AndExpression"; }
};

class ASTExclusiveOrExpr : public ASTNode
{
public:
  ASTExclusiveOrExpr(ASTAndExpr *n) : ASTNode() { this->add_child(n); }
  ASTExclusiveOrExpr(ASTExclusiveOrExpr *n1, ASTAndExpr *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "ExclusiveOrExpression"; }
};

class ASTInclusiveOrExpr : public ASTNode
{
public:
  ASTInclusiveOrExpr(ASTExclusiveOrExpr *n) : ASTNode() { this->add_child(n); }
  ASTInclusiveOrExpr(ASTInclusiveOrExpr *n1, ASTExclusiveOrExpr *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "InclusiveOrExpression"; }
};

class ASTLogicalAndExpr : public ASTNode
{
public:
  ASTLogicalAndExpr(ASTInclusiveOrExpr *n) : ASTNode() { this->add_child(n); }
  ASTLogicalAndExpr(ASTLogicalAndExpr *n1, ASTInclusiveOrExpr *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "LogicalAndExpression"; }
};

class ASTLogicalOrExpr : public ASTNode
{
public:
  ASTLogicalOrExpr(ASTLogicalAndExpr *n) : ASTNode() { this->add_child(n); }
  ASTLogicalOrExpr(ASTLogicalOrExpr *n1, ASTLogicalAndExpr *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "LogicalOrExpression"; }
};

class ASTCondExpr : public ASTNode
{
public:
  ASTCondExpr(ASTLogicalOrExpr *n) : ASTNode() { this->add_child(n); }
  ASTCondExpr(ASTLogicalOrExpr *n1, ASTExpr *n2, ASTCondExpr *n3) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  string to_str() override { return "ConditionalExpression"; }
};

class ASTIterStmt : public ASTStmt
{
};

class ASTWhileStmt : public ASTIterStmt
{
public:
  ASTWhileStmt(ASTExpr *n1, ASTStmt *n2) : ASTIterStmt()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "WhileStatement"; }
};

class ASTDoWhileStmt : public ASTIterStmt
{
public:
  ASTDoWhileStmt(ASTStmt *n1, ASTExpr *n2) : ASTIterStmt()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "DoWhileStatement"; }
};

class ASTForStmt : public ASTIterStmt
{
public:
  ASTForStmt(ASTExpr *n1, ASTExpr *n2, ASTStmt *n3) : ASTIterStmt()
  {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  ASTForStmt(ASTExpr *n1, ASTExpr *n2, ASTExpr *n3, ASTStmt *n4)
      : ASTIterStmt()
  {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
    this->add_child(n4);
  }
  ASTForStmt(ASTDecl *n1, ASTExpr *n2, ASTStmt *n3) : ASTIterStmt()
  {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
  }
  ASTForStmt(ASTDecl *n1, ASTExpr *n2, ASTExpr *n3, ASTStmt *n4)
      : ASTIterStmt()
  {
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
    this->add_child(n4);
  }
  string to_str() override { return "ForStatement"; }
};

/*  JUMP Statements */
class ASTJmpStmt : public ASTStmt
{
protected:
  ASTJmpStmt() : ASTStmt() {}
};

class ASTGotoJmpStmt : public ASTJmpStmt
{
public:
  ASTGotoJmpStmt(ASTId *n) : ASTJmpStmt() { this->add_child(n); }
  string to_str() override { return "GotoStatement"; }
};

class ASTContJmpStmt : public ASTJmpStmt
{
public:
  ASTContJmpStmt() {}
  string to_str() override { return "Continue"; }
};

class ASTBreakJmpStmt : public ASTJmpStmt
{
public:
  ASTBreakJmpStmt() {}
  string to_str() override { return "Break"; }
};

class ASTRetJmpStmt : public ASTJmpStmt
{
public:
  ASTRetJmpStmt() {}
  ASTRetJmpStmt(ASTExpr *n) : ASTJmpStmt() { this->add_child(n); }
  string to_str() override { return "ReturnStatement"; }
};

class ASTSelectStmt : public ASTStmt
{
};

class ASTGotoLabeledStmt : public ASTLabeledStmt
{
public:
  ASTGotoLabeledStmt(ASTId *n1, ASTStmt *n2) : ASTLabeledStmt()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "GotoLabel"; }
};

class ASTCaseLabeledStmt : public ASTLabeledStmt
{
public:
  ASTCaseLabeledStmt(ASTCondExpr *n1, ASTStmt *n2) : ASTLabeledStmt()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "CaseLabel"; }
};

class ASTDefLabeledStmt : public ASTLabeledStmt
{
public:
  ASTDefLabeledStmt(ASTStmt *n) : ASTLabeledStmt() { this->add_child(n); }
  string to_str() override { return "DefaultCaseLabel"; }
};

class ASTBlockItem : public ASTNode
{
public:
  ASTBlockItem(ASTDecl *n) : ASTNode() { this->add_child(n); }
  ASTBlockItem(ASTStmt *n) : ASTNode() { this->add_child(n); }
  string to_str() override { return "Block"; }
};

class ASTBlockItemList : public ASTStmt
{
public:
  ASTBlockItemList(ASTBlockItem *n) : ASTStmt() { this->add_child(n); }
  ASTBlockItemList(ASTBlockItemList *n1, ASTBlockItem *n2) : ASTStmt()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() override { return "BlockList"; }
};

class ASTProgram : public ASTNode
{
public:
  ASTProgram(ASTExternDecl *n1) : ASTNode() { this->add_child(n1); }
  ASTProgram(ASTProgram *n1, ASTExternDecl *n2) : ASTNode()
  {
    this->add_child(n1);
    this->add_child(n2);
  }
  string to_str() { return "Program"; }
};

#endif /* AST_HPP_INCLUDED */