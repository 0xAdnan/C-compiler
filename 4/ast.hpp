#ifndef AST_HPP_INCLUDED
#define AST_HPP_INCLUDED

#include "magic_enum.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class SemanticAnalyzer;

class ASTNode {
protected:
  ASTNode() { children = vector<ASTNode *>(); }

  void add_child(ASTNode *child, bool allow_single = false) {
    if (child == NULL)
      return;
    if (!allow_single && child->children.size() == 1)
      this->children.push_back(child->children[0]);
    else
      this->children.push_back(child);
  }

public:
  vector<ASTNode *> children;
  virtual string to_str() const = 0;

  void dump_ast(int indent) {
    auto myindent = indent;
    bool has_children = this->children.size() > 0;

    for (int i = 0; i < myindent; i++)
      cout << "    ";

    cout << this->to_str();

    if (has_children) {
      cout << "[Children: " << children.size() << "]  {" << endl;
      auto child_indent = indent + 1;
      for (auto child : children) {
        if (child != NULL)
          child->dump_ast(child_indent);
      }

      if (has_children) {
        for (int i = 0; i < myindent; i++)
          cout << "    ";
        cout << "}";
      }
    }

    cout << endl;
  }

  virtual bool semantic_action_start(SemanticAnalyzer *sa) const;

  virtual bool semantic_action_end(SemanticAnalyzer *sa) const;
};

enum ttype {
  t_void,
  t_char,
  t_short,
  t_int,
  t_long,
  t_float,
  t_double,
  t_signed,
  t_unsigned,
  t_bool,
  t_complex,
  t_imaginary
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

class ASTDeclList;
class ASTDirectDeclarator;
class ASTInitializer;
class ASTInitializerList;
class ASTCondExpr;
class ASTUnaryExpr;
class ASTAssignmentOp;
class ASTBlockItemList;
class ASTInitDeclList;
class ASTAssignmentExpr;

class ASTStmt : public ASTNode {
public:
  ASTStmt();
};

class ASTExpr : public ASTStmt {
public:
  ASTExpr();
  ASTExpr(ASTAssignmentExpr *n);
  ASTExpr(ASTExpr *n1, ASTAssignmentExpr *n2);
  string to_str() const override { return "Expression"; }
  bool semantic_action_start(SemanticAnalyzer *sa) const override;
  vector<string> get_referred_vars() const;
};

class ASTAssignmentExpr : public ASTExpr {
public:
  ASTAssignmentExpr(ASTCondExpr *n);
  ASTAssignmentExpr(ASTUnaryExpr *n1, ASTAssignmentOp *n2,
                    ASTAssignmentExpr *n3);
  string to_str() const override { return "AssignmentExpression"; }
};

class ASTInitDecl : public ASTNode {
public:
  ASTInitDecl(ASTDirectDeclarator *n1, ASTInitializer *n2);
  ASTInitDecl(ASTDirectDeclarator *n);
  string to_str() const override { return "InitDeclaration"; }
};

class ASTInitDeclList : public ASTNode {
public:
  ASTInitDeclList(ASTInitDecl *n);
  ASTInitDeclList(ASTInitDeclList *n1, ASTInitDecl *n2);
  string to_str() const override { return "InitDeclaratorList"; }
};

class ASTInitializer : public ASTNode {
public:
  ASTInitializer(ASTInitializerList *n);
  ASTInitializer(ASTAssignmentExpr *n);
  string to_str() const override { return "Initializer"; }
};

class ASTType : public ASTNode {
public:
  ttype t;

public:
  ASTType(ttype t);
  string to_str() const override {
    return "Type: " + string(magic_enum::enum_name(t).data());
  };
};

class ASTDeclSpec : public ASTNode {
public:
  ASTDeclSpec(ASTType *n);
  ASTDeclSpec(ASTType *n1, ASTDeclSpec *n2);
  string to_str() const override { return "DeclarationSpecifier"; }

  ttype get_type() const {
    if (children.size() > 1) {
      cout << "Not supporting long long yet;" << endl;
      exit(1);
    }
    ASTType *t = dynamic_cast<ASTType *>(children[0]);
    return t->t;
  }
};

class ASTFnDef : public ASTNode {
public:
  ASTFnDef(ASTDeclSpec *n1, ASTDirectDeclarator *n2, ASTDeclList *n3,
           ASTBlockItemList *n4);
  ASTFnDef(ASTDeclSpec *n1, ASTDirectDeclarator *n2, ASTBlockItemList *n3);
  string to_str() const override { return "ASTFnDef"; }
};

class ASTId : public ASTNode {
public:
  string name;

public:
  ASTId(string name);
  string to_str() const override { return "Identifier: " + name; }
};

class ASTDesignator : public ASTExpr {
public:
  ASTDesignator(ASTCondExpr *n);
  ASTDesignator(ASTId *n);
  string to_str() const override { return "Designator"; }
};

class ASTDesignatorList : public ASTNode {
public:
  ASTDesignatorList(ASTDesignator *n);
  ASTDesignatorList(ASTDesignatorList *n1, ASTDesignator *n2);
  string to_str() const override { return "DesignatorList"; }
};

class ASTInitializerList : public ASTNode {
public:
  ASTInitializerList(ASTDesignatorList *n1, ASTInitializer *n2);
  ASTInitializerList(ASTInitializer *n);
  ASTInitializerList(ASTInitializerList *n1, ASTDesignatorList *n2,
                     ASTInitializer *n3);
  ASTInitializerList(ASTInitializerList *n1, ASTInitializer *n2);
  string to_str() const override { return "InitializerList"; }
};

class ASTDecl : public ASTNode {
public:
  ASTDecl(ASTDeclSpec *n);
  ASTDecl(ASTDeclSpec *n1, ASTInitDeclList *n2);
  string to_str() const override { return "Declaration"; }
  unordered_map<string, ttype> get_variables() const;

  bool semantic_action_start(SemanticAnalyzer *sa) const override;
};

class ASTDeclList : public ASTNode {
public:
  ASTDeclList();
  ASTDeclList(ASTDeclList *n1, ASTDecl *n2);

  string to_str() const override { return "ASTDeclList"; }
};

class ASTAssignmentOp : public ASTNode {
protected:
  assignment_op ap;

public:
  ASTAssignmentOp(assignment_op ap);
  string to_str() const override { return magic_enum::enum_name(ap).data(); }
};

class ASTIncOp : public ASTNode {
protected:
  inc_op ip;

public:
  ASTIncOp(inc_op ip);
  string to_str() const override { return magic_enum::enum_name(ip).data(); }
};

class ASTUnaryOp : public ASTNode {
protected:
  unary_op up;

public:
  ASTUnaryOp(unary_op up);
  string to_str() const override { return magic_enum::enum_name(up).data(); }
};

class ASTPtrOp : public ASTNode {
protected:
  access_op ap;

public:
  ASTPtrOp(access_op ap);
  string to_str() const override { return magic_enum::enum_name(ap).data(); }
};

class ASTRelOp : public ASTNode {
protected:
  rel_op rp;

public:
  ASTRelOp(rel_op rp);
  string to_str() const override { return magic_enum::enum_name(rp).data(); }
};

class ASTEqOp : public ASTNode {
protected:
  equal_op ep;

public:
  ASTEqOp(equal_op ep);
  string to_str() const override { return magic_enum::enum_name(ep).data(); }
};

class ASTShiftOp : public ASTNode {
protected:
  shift_op sp;

public:
  ASTShiftOp(shift_op sp);
  string to_str() const override { return magic_enum::enum_name(sp).data(); }
};

class ASTArithOp : public ASTNode {
protected:
  arith_op ap;

public:
  ASTArithOp(arith_op ap);
  string to_str() const override { return magic_enum::enum_name(ap).data(); }
};

class ASTConst : public ASTNode {
public:
  const_type ct;
  string value;

public:
  ASTConst(const_type t, string value);
  string to_str() const override {
    if (ct == const_type::i_const)
      return "IntConst: " + value;
    else if (ct == const_type::f_const)
      return "FloatConst: " + value;
    return "UnknownConst: " + value;
  }
};

class ASTIdList : public ASTNode {
public:
  ASTIdList(ASTId *n);
  ASTIdList(ASTIdList *n1, ASTId *n2);
  string to_str() const override { return "IdentifierList"; }
};

class ASTStrConst : public ASTNode {};

class ASTStrLiteralConst : public ASTStrConst {
public:
  ASTStrLiteralConst();
  string to_str() const override { return "StringLiteral"; }
};

class ASTFuncNameConst : public ASTStrConst {
public:
  ASTFuncNameConst();
  string to_str() const override { return "FunctionName"; }
};

class ASTArgExpList : public ASTNode {
public:
  ASTArgExpList(ASTAssignmentExpr *n);
  ASTArgExpList(ASTArgExpList *n1, ASTAssignmentExpr *n2);
  string to_str() const override { return "ArgumentList"; }
};

class ASTPrimaryExpr : public ASTExpr {
public:
  ASTPrimaryExpr(ASTId *n);
  ASTPrimaryExpr(ASTConst *n);
  ASTPrimaryExpr(ASTStrConst *n);
  ASTPrimaryExpr(ASTExpr *n);
  string to_str() const override { return "PrimaryExpression"; }
};

class ASTPostExpr : public ASTExpr {
public:
  ASTPostExpr(ASTPrimaryExpr *n);
  ASTPostExpr(ASTPostExpr *n1, ASTExpr *n2);
  ASTPostExpr(ASTPostExpr *n);
  ASTPostExpr(ASTPostExpr *n1, ASTArgExpList *n2);
  ASTPostExpr(ASTPostExpr *n1, ASTPtrOp *n2, ASTId *n3);
  ASTPostExpr(ASTPostExpr *n1, ASTIncOp *n2);
  string to_str() const override { return "PostFixExpression"; }
};

class ASTUnaryExpr : public ASTExpr {
public:
  ASTUnaryExpr(ASTPostExpr *n);
  ASTUnaryExpr(ASTIncOp *n1, ASTUnaryExpr *n2);
  ASTUnaryExpr(ASTUnaryOp *n1, ASTUnaryExpr *n2);
  string to_str() const override { return "UnaryExpression"; }
};

class ASTMulExpr : public ASTExpr {
public:
  ASTMulExpr(ASTUnaryExpr *n);
  ASTMulExpr(ASTMulExpr *n1, ASTArithOp *n2, ASTUnaryExpr *n3);
  string to_str() const override { return "MultiplicationExpression"; }
};

class ASTAddExpr : public ASTExpr {
public:
  ASTAddExpr(ASTMulExpr *n);
  ASTAddExpr(ASTAddExpr *n1, ASTArithOp *n2, ASTMulExpr *n3);
  string to_str() const override { return "AddExpression"; }
};

class ASTShiftExpr : public ASTExpr {
public:
  ASTShiftExpr(ASTAddExpr *n);
  ASTShiftExpr(ASTShiftExpr *n1, ASTShiftOp *n2, ASTAddExpr *n3);
  string to_str() const override { return "ShiftExpression"; }
};

class ASTRelExpr : public ASTExpr {
public:
  ASTRelExpr(ASTShiftExpr *n);
  ASTRelExpr(ASTRelExpr *n1, ASTRelOp *n2, ASTShiftExpr *n3);
  string to_str() const override { return "RelationalExpression"; }
};

class ASTEqExpr : public ASTExpr {
public:
  ASTEqExpr(ASTRelExpr *n);
  ASTEqExpr(ASTEqExpr *n1, ASTEqOp *n2, ASTRelExpr *n3);
  string to_str() const override { return "EqualExpression"; }
};

class ASTAndExpr : public ASTExpr {
public:
  ASTAndExpr(ASTEqExpr *n);
  ASTAndExpr(ASTAndExpr *n1, ASTEqExpr *n2);
  string to_str() const override { return "AndExpression"; }
};

class ASTExclusiveOrExpr : public ASTExpr {
public:
  ASTExclusiveOrExpr(ASTAndExpr *n);
  ASTExclusiveOrExpr(ASTExclusiveOrExpr *n1, ASTAndExpr *n2);
  string to_str() const override { return "ExclusiveOrExpression"; }
};

class ASTInclusiveOrExpr : public ASTExpr {
public:
  ASTInclusiveOrExpr(ASTExclusiveOrExpr *n);
  ASTInclusiveOrExpr(ASTInclusiveOrExpr *n1, ASTExclusiveOrExpr *n2);
  string to_str() const override { return "InclusiveOrExpression"; }
};

class ASTLogicalAndExpr : public ASTExpr {
public:
  ASTLogicalAndExpr(ASTInclusiveOrExpr *n);
  ASTLogicalAndExpr(ASTLogicalAndExpr *n1, ASTInclusiveOrExpr *n2);
  string to_str() const override { return "LogicalAndExpression"; }
};

class ASTLogicalOrExpr : public ASTExpr {
public:
  ASTLogicalOrExpr(ASTLogicalAndExpr *n);
  ASTLogicalOrExpr(ASTLogicalOrExpr *n1, ASTLogicalAndExpr *n2);
  string to_str() const override { return "LogicalOrExpression"; }
};

class ASTCondExpr : public ASTExpr {
public:
  ASTCondExpr(ASTLogicalOrExpr *n);
  ASTCondExpr(ASTLogicalOrExpr *n1, ASTExpr *n2, ASTCondExpr *n3);
  string to_str() const override { return "ConditionalExpression"; }
};

class ASTIterStmt : public ASTStmt {};

class ASTWhileStmt : public ASTIterStmt {
public:
  ASTWhileStmt(ASTExpr *n1, ASTStmt *n2);
  string to_str() const override { return "WhileStatement"; }
};

class ASTDoWhileStmt : public ASTIterStmt {
public:
  ASTDoWhileStmt(ASTStmt *n1, ASTExpr *n2);
  string to_str() const override { return "DoWhileStatement"; }
};

class ASTForStmt : public ASTIterStmt {
public:
  ASTForStmt(ASTExpr *n1, ASTExpr *n2, ASTStmt *n3);
  ASTForStmt(ASTExpr *n1, ASTExpr *n2, ASTExpr *n3, ASTStmt *n4);
  ASTForStmt(ASTDecl *n1, ASTExpr *n2, ASTStmt *n3);
  ASTForStmt(ASTDecl *n1, ASTExpr *n2, ASTExpr *n3, ASTStmt *n4);
  string to_str() const override { return "ForStatement"; }
};

/*  JUMP Statements */
class ASTJmpStmt : public ASTStmt {};

class ASTGotoJmpStmt : public ASTJmpStmt {
public:
  ASTGotoJmpStmt(ASTId *n);
  string to_str() const override { return "GotoStatement"; }
};

class ASTContJmpStmt : public ASTJmpStmt {
public:
  ASTContJmpStmt();
  string to_str() const override { return "Continue"; }
};

class ASTBreakJmpStmt : public ASTJmpStmt {
public:
  ASTBreakJmpStmt();
  string to_str() const override { return "Break"; }
};

class ASTRetJmpStmt : public ASTJmpStmt {
public:
  ASTRetJmpStmt();
  ASTRetJmpStmt(ASTExpr *n);
  string to_str() const override { return "ReturnStatement"; }
};

class ASTSelectStmt : public ASTStmt {};

class ASTIfSelectStmt : public ASTSelectStmt {
public:
  ASTIfSelectStmt(ASTExpr *n1, ASTStmt *n2);
  string to_str() const override { return "IfStatement"; }
};

class ASTIfElseSelectStmt : public ASTSelectStmt {
public:
  ASTIfElseSelectStmt(ASTExpr *n1, ASTStmt *n2, ASTStmt *n3);
  string to_str() const override { return "IfElseStatement"; }
};

class ASTSwitchStmt : public ASTSelectStmt {
public:
  ASTSwitchStmt(ASTExpr *n1, ASTStmt *n2);
  string to_str() const override { return "SwitchStatement"; }
};

/*  LABELED Statements */
class ASTLabeledStmt : public ASTStmt {};

class ASTGotoLabeledStmt : public ASTLabeledStmt {
public:
  ASTGotoLabeledStmt(ASTId *n1, ASTStmt *n2);
  string to_str() const override { return "GotoLabel"; }
};

class ASTCaseLabeledStmt : public ASTLabeledStmt {
public:
  ASTCaseLabeledStmt(ASTCondExpr *n1, ASTStmt *n2);
  string to_str() const override { return "CaseLabel"; }
};

class ASTDefLabeledStmt : public ASTLabeledStmt {
public:
  ASTDefLabeledStmt(ASTStmt *n);
  string to_str() const override { return "DefaultCaseLabel"; }
};

class ASTBlockItem : public ASTNode {
public:
  ASTBlockItem(ASTDecl *n);
  ASTBlockItem(ASTStmt *n);
  string to_str() const override { return "Block"; }
};

class ASTBlockItemList : public ASTStmt {
public:
  ASTBlockItemList();
  ASTBlockItemList(ASTBlockItem *n);
  ASTBlockItemList(ASTBlockItemList *n1, ASTBlockItem *n2);
  string to_str() const override {
    if (children.size() == 0)
      return "EmptyBlockList";
    return "BlockList";
  }
  bool semantic_action_start(SemanticAnalyzer *sa) const override;
  bool semantic_action_end(SemanticAnalyzer *sa) const override;
};

class ASTPtr : public ASTNode {
public:
  ASTPtr();
  ASTPtr(ASTPtr *n);
  string to_str() const override { return "*Pointer"; }
};

class ASTDirectDeclarator : public ASTNode {
public:
  ASTDirectDeclarator() : ASTNode() {}
  void add_ptr(ASTPtr *ptr) { children.insert(children.begin(), ptr); }
};

class ASTIdDeclarator : public ASTDirectDeclarator {
public:
  ASTIdDeclarator(ASTId *n);
  string to_str() const override { return "IdDeclarator"; }
};

class ASTParamDecl : public ASTNode {
public:
  ASTParamDecl(ASTDeclSpec *n1, ASTDirectDeclarator *n2);
  ASTParamDecl(ASTDeclSpec *n);
  string to_str() const override { return "ParameterDeclaration"; }

  string get_var_name() const;
  ttype get_type() const;
};

class ASTParamList : public ASTNode {
public:
  ASTParamList(ASTParamDecl *n);
  ASTParamList(ASTParamList *n1, ASTParamDecl *n2);
  string to_str() const override { return "ParameterList"; }

  pair<bool, unordered_map<string, ttype>> get_variables() const;
};

class ASTFnDeclarator : public ASTDirectDeclarator {
public:
  ASTFnDeclarator(ASTDirectDeclarator *n1, ASTParamList *n2);
  ASTFnDeclarator(ASTDirectDeclarator *n);
  string to_str() const override { return "FunctionDeclarator"; }

  bool semantic_action_start(SemanticAnalyzer *sa) const override;

  pair<bool, unordered_map<string, ttype>> get_variables() const;
};

class ASTFnCallDeclarator : public ASTDirectDeclarator {
public:
  ASTFnCallDeclarator(ASTDirectDeclarator *n1, ASTIdList *n2);
  string to_str() const override { return "FunctionCallDeclarator"; }
};

class ASTExternDecl : public ASTNode {
public:
  ASTExternDecl(ASTFnDef *n);
  ASTExternDecl(ASTDecl *n);
  string to_str() const override { return "ASTExternDecl"; }
};

class ASTProgram : public ASTNode {
public:
  ASTProgram(ASTExternDecl *n1);
  ASTProgram(ASTProgram *n1, ASTExternDecl *n2);
  string to_str() const override { return "Program"; }
};

struct SymbolTable {
  string context;
  unordered_map<string, pair<ttype, int>> table;
};

class SemanticAnalyzer {
private:
  vector<SymbolTable> symbol_table;

public:
  SemanticAnalyzer() { symbol_table = vector<SymbolTable>(); }
  bool analyze(ASTProgram *p);
  bool analyze_node(ASTNode *node);

  bool find(string variable);
  bool find_all(string variable);
  void enter_scope(string context);
  void exit_scope();
  bool add_variable(string variable, ttype type);

  SymbolTable *peek();
};

#endif /* AST_HPP_INCLUDED */
