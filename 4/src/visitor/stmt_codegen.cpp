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
  if(llvm::isa<AllocaInst>(condV)){
    condV = builder->CreateLoad(get_value_type(condV), condV);
    condV = builder->CreateICmpNE(condV, ConstantInt::get(Type::getInt32Ty(*context), 0));
  }
  else{
    condV = builder->CreateICmpNE(condV, ConstantInt::get(*context, APInt(1, 0, false)));
  }
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
  if (!builder->GetInsertBlock()->getTerminator())
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
  if(llvm::isa<AllocaInst>(condV)){
    condV = builder->CreateLoad(get_value_type(condV), condV);
    condV = builder->CreateICmpNE(condV, ConstantInt::get(Type::getInt32Ty(*context), 0));
  }
  else{
    condV = builder->CreateICmpNE(condV, ConstantInt::get(*context, APInt(1, 0, false)));
  }
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
  if (!builder->GetInsertBlock()->getTerminator())
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
    if(llvm::isa<AllocaInst>(retVal)) {
      retVal = builder->CreateLoad(get_value_type(retVal), retVal);
    } else if(llvm::isa<GlobalVariable>(retVal)){
      retVal = builder->CreateLoad(get_value_type(retVal), retVal);
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
  if(llvm::isa<AllocaInst>(condV)){
    condV = builder->CreateLoad(get_value_type(condV), condV);
    condV = builder->CreateICmpNE(condV, ConstantInt::get(Type::getInt32Ty(*context), 0));
  }
  else{
    condV = builder->CreateICmpNE(condV, ConstantInt::get(*context, APInt(1, 0, false)));
  }
  builder->CreateCondBr(condV, loopBB, afterBB);

  builder->SetInsertPoint(loopBB);
  whileStmt->stmt->accept(this);
  builder->CreateBr(condBB);

  parentFunc->insert(parentFunc->end(), afterBB);
  builder->SetInsertPoint(afterBB);

  this->exit_loop();
  return nullptr;
}


Value *Codegen::visit(ASTForStmt *astForStmt) {
  Function *parentFunc = builder->GetInsertBlock()->getParent();

  this->enter_scope();
  astForStmt->expr1->accept(this);

  BasicBlock *condBB = BasicBlock::Create(*context, "cond", parentFunc);
  BasicBlock *loopBB = BasicBlock::Create(*context, "loop", parentFunc);
  BasicBlock *afterBB = BasicBlock::Create(*context, "afterloop");

  this->enter_loop(afterBB, condBB);

  builder->CreateBr(condBB);
  builder->SetInsertPoint(condBB);
  Value *condV = astForStmt->expr2->accept(this);
  condV = builder->CreateICmpNE(condV, ConstantInt::get(*context, APInt(1, 0, false)));
  builder->CreateCondBr(condV, loopBB, afterBB);

  builder->SetInsertPoint(loopBB);
  astForStmt->stmt->accept(this);
  if (astForStmt->expr3)
    astForStmt->expr3->accept(this);
  builder->CreateBr(condBB);

  parentFunc->insert(parentFunc->end(), afterBB);
  builder->SetInsertPoint(afterBB);

  this->exit_loop();
  this->exit_scope();

  return nullptr;
}

Value *Codegen::visit(ASTForStmt2 *astForStmt) {
  Function *parentFunc = builder->GetInsertBlock()->getParent();

  this->enter_scope();
  astForStmt->declList->accept(this);

  BasicBlock *condBB = BasicBlock::Create(*context, "cond", parentFunc);
  BasicBlock *loopBB = BasicBlock::Create(*context, "loop", parentFunc);
  BasicBlock *afterBB = BasicBlock::Create(*context, "afterloop");

  this->enter_loop(afterBB, condBB);

  builder->CreateBr(condBB);
  builder->SetInsertPoint(condBB);
  Value *condV = astForStmt->expr2->accept(this);
  condV = builder->CreateICmpNE(condV, ConstantInt::get(*context, APInt(1, 0, false)));
  builder->CreateCondBr(condV, loopBB, afterBB);

  builder->SetInsertPoint(loopBB);
  astForStmt->stmt->accept(this);
  if (astForStmt->expr3){
    builder->SetInsertPoint(loopBB);
    astForStmt->expr3->accept(this);
  }
  if(!builder->GetInsertBlock()->getTerminator())
    builder->CreateBr(condBB);

  parentFunc->insert(parentFunc->end(), afterBB);
  builder->SetInsertPoint(afterBB);

  this->exit_loop();
  this->exit_scope();

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

Value *Codegen::visit(ASTGotoLabeledStmt* astLabeledStmt){
  Function *parentFunc = builder->GetInsertBlock()->getParent();

  BasicBlock *label = nullptr;
  if(this->labelMap.find(astLabeledStmt->label) == this->labelMap.end()){
    label = BasicBlock::Create(*context, "goto-label", parentFunc);
    this->labelMap[astLabeledStmt->label] = label;
  }
  else{
    label = this->labelMap[astLabeledStmt->label];
  }
  this->completedLabels++;

  BasicBlock *mergeBB = BasicBlock::Create(*context, "goto-label-merge");

  builder->CreateBr(label); // Unconditional branch to the label block
  builder->SetInsertPoint(label);

  astLabeledStmt->stmt->accept(this);

  if (!builder->GetInsertBlock()->getTerminator())
    builder->CreateBr(mergeBB);

  parentFunc->insert(parentFunc->end(), mergeBB);
  builder->SetInsertPoint(mergeBB);

  return nullptr;
}

Value *Codegen::visit(ASTGotoJmpStmt * astGotoStmt) {
  Function *parentFunc = builder->GetInsertBlock()->getParent();

  BasicBlock *gotoBB = nullptr;
  if(this->labelMap.find(astGotoStmt->label) == this->labelMap.end()){
    gotoBB = BasicBlock::Create(*context, "goto-gotoBB", parentFunc);
    this->labelMap[astGotoStmt->label] = gotoBB;
  }
  else{
    gotoBB = this->labelMap[astGotoStmt->label];
  }
  BasicBlock *mergeBB = BasicBlock::Create(*context, "goto-merge");

  builder->CreateBr(gotoBB); // Unconditional branch to the goto block

  parentFunc->insert(parentFunc->end(), mergeBB);
  builder->SetInsertPoint(mergeBB);

  return nullptr;
}
