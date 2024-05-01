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

    ASTExpr *visit(ASTIdExpr *);
    ASTExpr *visit(ASTExpr *);
    ASTConst *visit(ASTConst *);
    ASTExpr *visit(ASTExprList *);
    ASTFunctionCall *visit(ASTFunctionCall*);
    ASTExpr *visit(ASTPostIncrement*);

    ASTStmt *visit(ASTStmt *);
    ASTExprStmt *visit(ASTExprStmt *);
    ASTIfStmt *visit(ASTIfStmt *);
    ASTIfElseStmt *visit(ASTIfElseStmt *);
    ASTWhileStmt *visit(ASTWhileStmt *);

void enterScope()
{
    unordered_map<string, ASTConst *> newScope;
    if (!constValues.empty()) {
        const auto& prevScope = constValues.back();
        newScope = prevScope;  
    }
    constValues.push_back(move(newScope));  
}


void exitScope()
{
    if (!constValues.empty()) {
        if (constValues.size() > 1) {
            auto& currScope = constValues.back();
            auto& prevScope = *(constValues.rbegin() + 1);

            for (const auto& [name, currConstPtr] : currScope) {
                auto it = prevScope.find(name);
                if (it != prevScope.end() && it->second != currConstPtr) {
                    prevScope.erase(it);
                }
            }
        }

        constValues.pop_back();
    }
}

};

#endif
