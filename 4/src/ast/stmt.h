//
// Created by satyam on 30/3/24.
//

#ifndef CCOMPILER_STMT_H
#define CCOMPILER_STMT_H

#include "base.h"

class ASTStmt: public ASTNode{

};

class ASTCompoundStmt: public ASTStmt{
    vector<ASTStmt*> stmts;
};

#endif //CCOMPILER_STMT_H
