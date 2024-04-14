//
// Created by satyam on 14/4/24.
//
#include "codegen.h"

Value *Codegen::visit(ASTIfStmt *ifStmt) {
  Function *parentFunc = builder->GetInsertBlock()->getParent();
  // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
  BasicBlock *thenBB = BasicBlock::Create(*context, "then", parentFunc);
  BasicBlock *elseBB = BasicBlock::Create(*context, "else");
  BasicBlock *mergeBB = BasicBlock::Create(*context, "ifcont");

  Value *condV = ifStmt->cond->accept(this);
  condV = builder->CreateICmpNE(condV, ConstantInt::get(*context, APInt(1, 0, false)));

  builder->CreateCondBr(condV, thenBB, elseBB);

  // Emit then value.
  builder->SetInsertPoint(thenBB);
  Value *thenV = ifStmt->stmt->accept(this);
  if (!builder->GetInsertBlock()->getTerminator())
    builder->CreateBr(mergeBB);

  // Emit else block.
  parentFunc->insert(parentFunc->end(), elseBB);
  builder->SetInsertPoint(elseBB);
  builder->CreateBr(mergeBB);

  // Emit merge block.
  parentFunc->insert(parentFunc->end(), mergeBB);
  builder->SetInsertPoint(mergeBB);

  return nullptr;
}

Value *Codegen::visit(ASTIfElseStmt *ifStmt) {
  Function *parentFunc = builder->GetInsertBlock()->getParent();
  // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
  BasicBlock *thenBB = BasicBlock::Create(*context, "then", parentFunc);
  BasicBlock *elseBB = BasicBlock::Create(*context, "else");
  BasicBlock *mergeBB = BasicBlock::Create(*context, "ifcont");

  Value *condV = ifStmt->cond->accept(this);
  condV = builder->CreateICmpNE(condV, ConstantInt::get(*context, APInt(1, 0, false)));
  builder->CreateCondBr(condV, thenBB, elseBB);

  // Emit then value.
  builder->SetInsertPoint(thenBB);
  ifStmt->stmt->accept(this);
  if (!builder->GetInsertBlock()->getTerminator())
    builder->CreateBr(mergeBB);

  // Emit else block.
  parentFunc->insert(parentFunc->end(), elseBB);
  builder->SetInsertPoint(elseBB);
  ifStmt->elseStmt->accept(this);
  builder->CreateBr(mergeBB);

  // Emit merge block.
  parentFunc->insert(parentFunc->end(), mergeBB);
  builder->SetInsertPoint(mergeBB);

  return nullptr;
}

llvm::Value *Codegen::visit(ASTRetJmpStmt *retStmt) {
  if (retStmt->expr) {
    llvm::Value *retVal = retStmt->expr->accept(this);
    if (!retVal) {
      llvm::errs() << "Error generating code for return statement expression.\n";
      return nullptr;
    }
    return builder->CreateRet(retVal);
  } else {
    return builder->CreateRetVoid();
  }
}

Value *Codegen::visit(ASTWhileStmt *whileStmt) {

  Function *parentFunc = builder->GetInsertBlock()->getParent();

  BasicBlock *condBB = BasicBlock::Create(*context, "cond", parentFunc);
  BasicBlock *loopBB = BasicBlock::Create(*context, "loop", parentFunc);
  BasicBlock *afterBB = BasicBlock::Create(*context, "afterloop");

  this->enter_loop(afterBB, condBB);

  builder->CreateBr(condBB);
  builder->SetInsertPoint(condBB);
  Value *condV = whileStmt->cond->accept(this);
  condV = builder->CreateICmpNE(condV, ConstantInt::get(*context, APInt(1, 0, false)));
  builder->CreateCondBr(condV, loopBB, afterBB);

  builder->SetInsertPoint(loopBB);
  whileStmt->stmt->accept(this);
  builder->CreateBr(condBB);

  parentFunc->insert(parentFunc->end(), afterBB);
  builder->SetInsertPoint(afterBB);

  this->exit_loop();
  return nullptr;
}

Value *Codegen::visit(ASTBreakJmpStmt *) {
  if (!this->breakBlock) {
    llvm::errs() << "Break statement outside loop\n";
    assert(false);
  }
  return builder->CreateBr(this->breakBlock);
}

Value *Codegen::visit(ASTContJmpStmt *) {
  if (!this->contBlock) {
    llvm::errs() << "Break statement outside loop\n";
    assert(false);
  }
  return builder->CreateBr(this->contBlock);
}
