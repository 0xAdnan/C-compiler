//
// Created by satyam on 30/3/24.
//

#ifndef CCOMPILER_PROG_H
#define CCOMPILER_PROG_H

#include "base.h"
#include "decl.h"
#include "stmt.h"

class ASTExternDecl: public ASTNode{

};

class ASTFnDef: public ASTExternDecl{
public:
    ASTFnDef(ASTDeclSpec*, ASTDeclarator*, ASTCompoundStmt*);
};

class ASTGlobalVar: public ASTExternDecl{
public:
    ASTDecl* declaration;

};

class ASTProgram: public ASTNode{
public:
  vector<ASTExternDecl*> extDecls;

  ASTProgram(ASTExternDecl*);
  ASTProgram(ASTExternDecl*, ASTProgram*);

};

#endif //CCOMPILER_PROG_H
