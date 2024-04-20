//
// Created by satyam on 18/4/24.
//

#ifndef CCOMPILER_ALGEBRA_SIMPLIFICATION_OPT_H
#define CCOMPILER_ALGEBRA_SIMPLIFICATION_OPT_H


#include "visitor.h"
#include "expr.h"
#include "prog.h"

class AlgebraSimplificationOpt: public Visitor {
public:
    ASTExpr* visit(ASTExpr*);
    ASTExprList* visit(ASTExprList*);
    ASTProgram* visit(ASTProgram*);
    ASTGlobalVar* visit(ASTGlobalVar*);
    ASTFnDef* visit(ASTFnDef*);
    ASTDeclList* visit(ASTDeclList*);
    ASTDecl* visit(ASTDecl*);
    ASTBlockList* visit(ASTBlockList*);
    ASTBlock* visit(ASTBlock*);
    ASTIfStmt* visit(ASTIfStmt*);
    ASTIfElseStmt* visit(ASTIfElseStmt*);
    ASTWhileStmt* visit(ASTWhileStmt*);
    ASTRetJmpStmt* visit(ASTRetJmpStmt*);
    ASTGotoLabeledStmt* visit(ASTGotoLabeledStmt*);
    ASTExprStmt* visit(ASTExprStmt*);

    ASTSelectStmt* visit(ASTSelectStmt* stmt){
      return stmt;
    }

    ASTIterStmt* visit(ASTIterStmt* stmt){
      return stmt;
    }

    ASTStmt* visit(ASTStmt* stmt){
      return stmt;
    }

private:
    static bool is_simplifiable(operators ot);
};


#endif //CCOMPILER_ALGEBRA_SIMPLIFICATION_OPT_H
