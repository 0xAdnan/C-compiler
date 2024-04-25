//
// Created by satyam on 18/4/24.
//

#ifndef CCOMPILER_CONST_PROP_OPT_H
#define CCOMPILER_CONST_PROP_OPT_H

#include "visitor.h"
#include "expr.h"
#include "stmt.h"
#include "prog.h"
#include "vector"
#include "map"
#include "opt_utils.h"

class ConstPropagationOpt : public Visitor
{
private:
    // unordered_map<string, ASTConst*> constValues;
    vector<unordered_map<string, ASTConst *>> constValues;

public:
    ASTProgram *visit(ASTProgram *);
    ASTFnDef *visit(ASTFnDef *);
    ASTBlock *visit(ASTBlock *);
    ASTBlockList *visit(ASTBlockList *);
    ASTDecl *visit(ASTDecl *);
    ASTStmt *visit(ASTStmt *);
    ASTExprStmt *visit(ASTExprStmt *);
    ASTExpr *visit(ASTIdExpr *);
    ASTExpr *visit(ASTExpr *);
    ASTConst *visit(ASTConst *);
    ASTExpr *visit(ASTExprList *);
    ASTIfStmt *visit(ASTIfStmt *);
    ASTWhileStmt *visit(ASTWhileStmt *);

void enterScope()
{
    if (!constValues.empty()) {
        constValues.push_back(unordered_map<string, ASTConst *>());
        auto &previousScope = *(constValues.rbegin() - 1);
        for (auto &entry : previousScope) {
            constValues.back().insert(entry);
        }
    } else {
        constValues.push_back(unordered_map<string, ASTConst *>());
    }
}


void exitScope()
{
    if (!constValues.empty()) {
        auto &previousScope = *(constValues.rbegin() + 1);
        for (auto &entry : *(constValues.rbegin())) {
            if (entry.second) {
                previousScope.erase(entry.first);
            }
        }
        constValues.pop_back();
    }
}


};

#endif
