//
// Created by satyam on 29/3/24.
//

#ifndef CCOMPILER_EXPR_H
#define CCOMPILER_EXPR_H

#include "base.h"

#include <cassert>

class ASTExpr : public ASTNode {
public:
    operators operator_;
    op_type opType;
    vector<ASTExpr *> operands;
    bool is_LHS = false;

    ASTExpr() : ASTNode() {
      operator_ = noop;
      opType = get_op_type(operator_);
    }

    ASTExpr(operators op, ASTExpr *expr1) : ASTNode() {
      assert((get_op_type(op) == unary || get_op_type(op) == assignment));

      this->operator_ = op;
      this->opType = get_op_type(op);

      operands.push_back(expr1);
    }

    ASTExpr(operators op, ASTExpr *expr1, ASTExpr *expr2) : ASTNode() {
      // assert(get_op_type(op) == binary);

      this->operator_ = op;
      this->opType = get_op_type(op);

      if (this->opType == assignment) {
        expr1->is_LHS = true;
      }

      operands.push_back(expr1);
      operands.push_back(expr2);
    }

    ASTExpr(operators op, ASTExpr *expr1, ASTExpr *expr2, ASTExpr *expr3) : ASTNode() {
      assert(get_op_type(op) == ternary);

      this->operator_ = op;
      this->opType = get_op_type(op);

      if (this->opType == assignment) {
        expr1->is_LHS = true;
      }

      operands.push_back(expr1);
      operands.push_back(expr2);
      operands.push_back(expr3);
    }

    [[nodiscard]] string to_str() const override {
      return "Operator: " + op_to_str(operator_);
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTExpr *accept(AlgebraSimplificationOpt *opt) override;

    ASTExpr *accept(ConstPropagationOpt *opt)override;


    string accept(Printer *printer, int indent) override;

};

class ASTIdExpr : public ASTExpr {
public:
    string name;

    ASTIdExpr(string name) : ASTExpr() {
      this->name = name;
    }

    [[nodiscard]] string to_str() const override {
      return "IdentifierExpr: " + name;
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTExpr *accept(ConstPropagationOpt *opt) override;

    string accept(Printer *, int) override;
};

class ASTConst : public ASTExpr {
public:
    const_type ct;
    string value;

    ASTConst(const_type ct, string value) {
      this->ct = ct;
      this->value = value;
    }

    [[nodiscard]] string to_str() const override {
      return "Const: " + const_type_to_str(ct) + " " + value;
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTConst *accept(ConstPropagationOpt *opt) override;


    string accept(Printer *, int) override;
};

class ASTArrayAccess : public ASTExpr {
public:
    ASTExpr *array;
    ASTExpr *index;

    ASTArrayAccess(ASTExpr *array, ASTExpr *index) {
      assert(array->operator_ == noop);
      this->array = array;
      this->index = index;
    }

    [[nodiscard]] string to_str() const override {
      return "ArrayAccess";
    }

    string accept(Printer *, int) override;
};

class ASTExprList : public ASTExpr {
public:
    vector<ASTExpr *> exprs;

    ASTExprList(ASTExpr *expr) : ASTExpr() {
      exprs.push_back(expr);
    }

    ASTExprList(ASTExprList *exprL, ASTExpr *expr) : ASTExpr() {
      for (auto e: exprL->exprs) {
        exprs.push_back(e);
      }
      exprs.push_back(expr);

      delete exprL;
    }

    [[nodiscard]] string to_str() const override {
      return "Expressions";
    }

    llvm::Value *accept(Codegen *codegen) override;

    ASTExprList *accept(AlgebraSimplificationOpt *) override;

    ASTExpr *accept(ConstPropagationOpt *opt) override;


    string accept(Printer *, int) override;
};


class ASTFunctionCall : public ASTExpr {
public:
    ASTIdExpr *fn;
    ASTExprList *params = nullptr;

    ASTFunctionCall(ASTIdExpr *fn) : ASTExpr() {
      this->fn = fn;
    }

    ASTFunctionCall(ASTIdExpr *fn, ASTExprList *args) {
      this->fn = fn;
      params = args;
    }

    [[nodiscard]] string to_str() const override {
      return "FunctionCall: " + fn->name;
    }

    llvm::Value *accept(Codegen *codegen) override;

    string accept(Printer *, int) override;
};

class ASTPostIncrement : public ASTExpr {
public:
    ASTExpr *expr;
    bool is_inc;

    ASTPostIncrement(ASTExpr *expr, bool is_inc) : ASTExpr() {
      this->expr = expr;
      this->is_inc = is_inc;
    }

    [[nodiscard]] string to_str() const override {
      if (is_inc)
        return "PostIncrement";
      return "PostDecrement";
    }

    llvm::Value *accept(Codegen *codegen) override;

    string accept(Printer *, int) override;
};

#endif // CCOMPILER_EXPR_H
