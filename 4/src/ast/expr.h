//
// Created by satyam on 29/3/24.
//

#ifndef CCOMPILER_EXPR_H
#define CCOMPILER_EXPR_H

#include "base.h"

#include <cassert>

class ASTExpr: public ASTNode{
public:
    operators operator_;
    op_type opType;
    vector<ASTExpr*> operands;

    ASTExpr(): ASTNode(){
      operator_ = noop;
      opType = get_op_type(operator_);
    }

    ASTExpr(operators op, ASTExpr* expr1): ASTNode(){
      assert((get_op_type(op) == unary || get_op_type(op) == assignment));

      this->operator_ = op;
      this->opType = get_op_type(op);

      operands.push_back(expr1);
      add_children();
    }

    ASTExpr(operators op, ASTExpr* expr1, ASTExpr* expr2): ASTNode(){
      assert(get_op_type(op) == binary);

      this->operator_ = op;
      this->opType = get_op_type(op);

      operands.push_back(expr1);
      operands.push_back(expr2);
      add_children();
    }

    ASTExpr(operators op, ASTExpr* expr1, ASTExpr* expr2, ASTExpr* expr3): ASTNode(){
      assert(get_op_type(op) == ternary);

      this->operator_ = op;
      this->opType = get_op_type(op);

      operands.push_back(expr1);
      operands.push_back(expr2);
      operands.push_back(expr3);
      add_children();
    }

    [[nodiscard]] string to_str() const override {
      return "Operator: " + op_to_str(operator_);
    }

    llvm::Value *accept(Codegen *codegen) override {
      return ASTNode::accept(codegen);
    }

private:
    void add_children(){
      children.clear();
      for(auto o: operands)
        children.push_back(o);
    }
};

class ASTIdExpr: public ASTExpr{
public:
    string name;
    ASTIdExpr(string name): ASTExpr(){
      this->name = name;
    }

    [[nodiscard]] string to_str() const override {
      return "IdentifierExpr: " + name;
    }

    llvm::Value *accept(Codegen *codegen) override;
};

class ASTConst: public ASTExpr{
public:
    const_type ct;
    string value;

    ASTConst(const_type ct, string value){
      this->ct = ct;
      this->value = value;
    }

    [[nodiscard]] string to_str() const override {
      return "Const: " + const_type_to_str(ct) + " " + value;
    }

    llvm::Value *accept(Codegen *codegen) override;

};

class ASTArrayAccess: public ASTExpr{
public:
    ASTExpr* array;
    ASTExpr* index;

    ASTArrayAccess(ASTExpr* array, ASTExpr* index){
      assert(array->operator_ == noop);
      this->array = array;
      this->index = index;

      children.push_back(array);
      children.push_back(index);
    }

    [[nodiscard]] string to_str() const override {
      return "ArrayAccess";
    }
};

class ASTExprList: public ASTExpr{
public:
    vector<ASTExpr*> exprs;

    ASTExprList(ASTExpr* expr): ASTExpr(){
      exprs.push_back(expr);
      children.push_back(expr);
    }

    ASTExprList(ASTExprList* exprL, ASTExpr* expr): ASTExpr(){
      for(auto e: exprL->exprs){
        exprs.push_back(e);
      }
      exprs.push_back(expr);

      delete exprL;

      children.clear();
      for(auto e: exprs)
        children.push_back(e);
    }

    [[nodiscard]] string to_str() const override{
      return "Expressions";
    }
};

class ASTFunctionCall: public ASTExpr{
public:
    ASTExpr* fn;
    ASTExprList* params= nullptr;

    ASTFunctionCall(ASTExpr* fn): ASTExpr(){
      this->fn = fn;

      children.push_back(fn);
    }

    ASTFunctionCall(ASTExpr* fn, ASTExprList* args){
      this->fn = fn;
      params = args;

      children.push_back(fn);
      children.push_back(args);
    }

    [[nodiscard]] string to_str() const override{
      return "FunctionCall";
    }
};

class ASTPostIncrement: public ASTExpr{
public:
    ASTExpr* expr;
    bool is_inc;

    ASTPostIncrement(ASTExpr* expr, bool is_inc): ASTExpr(){
      this->expr = expr;
      this->is_inc = is_inc;

      children.push_back(expr);
    }

    [[nodiscard]] string to_str() const override{
      if(is_inc)
        return "PostIncrement";
      return "PostDecrement";
    }
};


#endif //CCOMPILER_EXPR_H
