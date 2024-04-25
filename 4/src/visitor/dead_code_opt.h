//
// Created by satyam on 18/4/24.
//

#ifndef CCOMPILER_DEAD_CODE_OPT_H
#define CCOMPILER_DEAD_CODE_OPT_H

#include "visitor.h"
#include "stmt.h"
#include "prog.h"

class DeadCodeOpt: public Visitor {
public:
    ASTNode* visit(ASTNode*);
    ASTStmt* visit(ASTStmt*);
    ASTIfStmt* visit(ASTIfStmt*);
    ASTStmt* visit(ASTIfElseStmt*);
    ASTWhileStmt* visit(ASTWhileStmt*);

    ASTProgram* visit(ASTProgram*);
    ASTFnDef* visit(ASTFnDef*);
    ASTBlockList* visit(ASTBlockList*);
    ASTBlock* visit(ASTBlock*);

    ASTLabeledStmt *visit(ASTLabeledStmt*);
};

#endif //CCOMPILER_DEAD_CODE_OPT_H
