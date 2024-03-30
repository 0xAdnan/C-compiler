//
// Created by satyam on 29/3/24.
//

#ifndef CCOMPILER_EXPR_H
#define CCOMPILER_EXPR_H

#include "base.h"
#include "enums.h"

class ASTExpr: public ASTNode{

};



class ASTExprList: public ASTNode{
public:
    vector<ASTExpr*> exprs;

    ASTExprList(ASTExpr*);
    ASTExprList(ASTExprList*, ASTExpr*);
};



class ASTArgExprList: public ASTExpr{
public:
    vector<ASTExpr*> arguments;

    ASTArgExprList(ASTExpr*);
    ASTArgExprList(ASTArgExprList*, ASTExpr*);
};

class ASTPostExpr: public ASTExpr{};

class ASTUnaryExpr: public ASTPostExpr{
  ASTUnaryExpr* expr;
  unary_op op = noop;

  ASTUnaryExpr(ASTPostExpr* expr);
  ASTUnaryExpr(unary_op op, ASTPostExpr* expr);
};


class ASTBinaryExpr: public ASTUnaryExpr{
public:
    ASTUnaryExpr* lhs;
    binary_op op;
    ASTUnaryExpr* rhs;
};

class ASTTernaryExpr: public ASTBinaryExpr{
public:
    ASTBinaryExpr* cond;
    ASTExprList* lhs;
    ASTTernaryExpr* rhs;
};

class ASTAssignmentExpr: public ASTTernaryExpr{
public:
    ASTUnaryExpr* lhs;
    assignment_op op;
    ASTAssignmentExpr* rhs;

    ASTAssignmentExpr(ASTUnaryExpr*, assignment_op op, ASTAssignmentExpr*);
};

#endif //CCOMPILER_EXPR_H
