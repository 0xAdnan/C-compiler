//
// Created by satyam on 18/4/24.
//

#include "dead_code_opt.h"
#include "opt_utils.h"


ASTNode *DeadCodeOpt::visit(ASTNode *node) {
  return node;
}


ASTStmt *DeadCodeOpt::visit(ASTStmt *stmt) {
  return stmt;
}

ASTIfStmt *DeadCodeOpt::visit(ASTIfStmt *ifStmt) {
  if(is_const_node(ifStmt->cond, "0")) {
      return nullptr;
  }
  return ifStmt;

}

ASTStmt *DeadCodeOpt::visit(ASTIfElseStmt *ifElseStmt) {
  if(is_const_node(ifElseStmt->cond, "0")) {
    return ifElseStmt->elseStmt->accept(this);
  } else if(is_const_node(ifElseStmt->cond, "1")){
    return ifElseStmt->stmt->accept(this);
  }
  return ifElseStmt;
}

ASTWhileStmt *DeadCodeOpt::visit(ASTWhileStmt *whileStmt) {
  if(is_const_node(whileStmt->cond, "0")) {
    return nullptr;
  }
  return whileStmt;
}

ASTLabeledStmt* DeadCodeOpt::visit(ASTLabeledStmt* labeledStmt) {
  labeledStmt->stmt = labeledStmt->stmt->accept(this);
  return labeledStmt;
}


ASTFnDef *DeadCodeOpt::visit(ASTFnDef *fnDef) {
  fnDef->body = fnDef->body->accept(this);
  return fnDef;
}

ASTBlockList *DeadCodeOpt::visit(ASTBlockList *bl) {
  vector<ASTBlock*> newBlockList;
  for(auto block: bl->blocks) {
    auto newBlock = block->accept(this);
    if(newBlock != nullptr) {
      newBlockList.push_back(newBlock);
    }
  }
  bl->blocks = newBlockList;
  return bl;
}

ASTBlock* DeadCodeOpt::visit(ASTBlock *block) {
  if(block->stmt != nullptr) {
    block->stmt = block->stmt->accept(this);
    if(block->stmt == nullptr) {
      return nullptr;
    }
  }
  return block;
}

ASTProgram *DeadCodeOpt::visit(ASTProgram *program) {
  vector<ASTExternDecl*> newExtDecls;

  for(auto extDecl: program->extDecls) {
    auto fnDef = dynamic_cast<ASTFnDef*>(extDecl);
    if(fnDef != nullptr) {
      auto newFnDef = fnDef->accept(this);
      if(newFnDef)
        newExtDecls.push_back(newFnDef);
    } else {
      newExtDecls.push_back(extDecl);
    }
  }

  program->extDecls = newExtDecls;
  return program;
}
