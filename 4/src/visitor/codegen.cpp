//
// Created by satyam on 29/3/24.
//

#include "codegen.h"
#include "expr.h"


llvm::Type* get_value_type(llvm::Value* value) {
  if (!value) return nullptr;

  if (auto* allocaInst = llvm::dyn_cast<llvm::AllocaInst>(value)) {
    return allocaInst->getAllocatedType();
  }
  else if (auto* constant = llvm::dyn_cast<llvm::Constant>(value)) {
    return constant->getType();
  }
  else {
    return value->getType();
  }
}

bool is_const_expr(ASTExpr* expr){
  auto const_ = dynamic_cast<ASTConst*>(expr);
  return const_ != nullptr;
}

llvm::Value *Codegen::visit(ASTProgram *program)
{
  int i = 0;
  for (; i < program->extDecls.size() - 1; i++)
    program->extDecls[i]->accept(this);

  return program->extDecls[i]->accept(this);
}

llvm::Value *Codegen::visit(ASTFnDef *fnDef)
{
  Function *fn = module->getFunction(fnDef->fnDecl->name);

  if (!fn)
  {
    vector<Type *> params;

    bool is_variadic = false;
    if (fnDef->fnDecl->params)
    {
      for (auto p : fnDef->fnDecl->params->paramList->params)
        params.push_back(ctype_2_llvmtype(p->type, p->num_ptr > 0));
      is_variadic = fnDef->fnDecl->params->is_variadic;
    }

    FunctionType *FT = FunctionType::get(
        ctype_2_llvmtype(fnDef->declSpec->type, fnDef->fnDecl->num_ptrs > 0),
        params,
        is_variadic);

    fn = Function::Create(FT, Function::ExternalLinkage, fnDef->fnDecl->name, *module);
  }

  // Create a new basic block to start insertion into.
  BasicBlock *BB = BasicBlock::Create(*context, "entry", fn);
  builder->SetInsertPoint(BB);

  enter_scope(fn->getFunctionType());

  // Alloca the parameters of function to support &x. Function parameters are in register in llvm.
  // So to support that we to copy it to memory(stack)
  int idx = 0;
  if (fnDef->fnDecl->params)
  {
    for (auto &arg : fn->args())
    {
      AllocaInst *paramAlloca = builder->CreateAlloca(
          arg.getType(), nullptr,
          fnDef->fnDecl->params->paramList->params[idx]->name);
      add_variable(std::string(fnDef->fnDecl->params->paramList->params[idx]->name), paramAlloca);
      idx++;
    }
  }

  fnDef->body->accept(this);
  verifyFunction(*fn);

  return fn;
}

llvm::Value *Codegen::visit(ASTBlockList *blockList)
{
  llvm::Value *v;
  enter_scope();
  for (auto block : blockList->blocks)
  {
    v = block->accept(this);
  }
  exit_scope();
  return v;
}

Value *Codegen::visit(ASTBlock *block)
{
  if (block->declaration)
    return block->declaration->accept(this);
  else
    return block->stmt->accept(this);
}

llvm::Value *Codegen::visit(ASTGlobalVar *globalVar)
{
  llvm::Value *val;

  for (auto &decl : globalVar->declaration->declarations)
  {
    vector<Type *> params;
    if (decl->fnDecl)
    {
      for (auto p : decl->fnDecl->params->paramList->params)
        params.push_back(ctype_2_llvmtype(p->type, p->num_ptr > 0));

      FunctionType *FT = FunctionType::get(
          ctype_2_llvmtype(decl->type, decl->num_ptr > 0),
          params,
          decl->fnDecl->params->is_variadic);
      val = Function::Create(FT, Function::ExternalLinkage, decl->name, *module);
    }
    else if (decl->value)
    {
      for (auto global = module->global_begin(); global != module->global_end(); ++global)
      {
        if (global->getName() == decl->name)
        {
          global->eraseFromParent();
          break;
        }
      }
      auto constant = (llvm::Constant *)(decl->value->accept(this));

      if (constant == nullptr)
      {
        string msg = "Global variable can only be initialized with constants";
        llvm::errs() << msg << "\n";
        assert(false);
      }

      val = new llvm::GlobalVariable(
          *module,
          ctype_2_llvmtype(decl->type, decl->num_ptr > 0),
          decl->is_const,
          llvm::GlobalValue::CommonLinkage,
          constant, decl->name);
    }
    else
    {
      for (auto global = module->global_begin(); global != module->global_end(); ++global)
      {
        if (global->getName() == decl->name)
        {
          global->eraseFromParent();
          break;
        }
      }
      val = new llvm::GlobalVariable(
          *module,
          ctype_2_llvmtype(decl->type, decl->num_ptr > 0),
          decl->is_const,
          llvm::GlobalValue::CommonLinkage,
          nullptr, decl->name);
      ((GlobalVariable *)val)->setDSOLocal(true);
    }
  }

  return val;
}

llvm::Value *Codegen::visit(ASTConst *constant) const
{
  switch (constant->ct)
  {
  case i_const:
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), stoi(constant->value));
  case f_const:
    return llvm::ConstantFP::get(llvm::Type::getInt32Ty(*context), stof(constant->value));
  case s_const:
    auto string_const = ConstantDataArray::getString(module->getContext(), constant->value, true);

     // Create a global variable with the constant string
    GlobalVariable *strVar = new llvm::GlobalVariable(
        /*Module=*/    *module,
        /*Type=*/      string_const->getType(),
        /*isConstant=*/true,
        /*Linkage=*/   GlobalValue::PrivateLinkage,
        /*Initializer=*/string_const,
        /*Name=*/      ".str");

    strVar->setAlignment(Align(1));
    return strVar;

  }
}

llvm::Value *Codegen::visit(ASTDeclList *decls)
{
  llvm::Value *v;
  for (auto d : decls->declarations)
  {
    v = d->accept(this);
  }
  return v;
}

llvm::Value *Codegen::visit(ASTDecl *decl)
{
  if (decl->is_const)
    cout << "Not supporting Const Semantics" << endl;
  AllocaInst *allocaInst = create_alloca_of_type(decl->type, decl->name);

  if (decl->value)
  {
    llvm::Value *v = decl->value->accept(this);
    builder->CreateStore(v, allocaInst);
  }

  add_variable(decl->name, allocaInst);

  return allocaInst;
}




Value *Codegen::visit(ASTIdExpr *idExpr)
{
  return find_variable(idExpr->name);
}

Value *Codegen::visit(ASTIfStmt *ifStmt)
{
  Function *parentFunc = builder->GetInsertBlock()->getParent();
  // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
  BasicBlock *thenBB = BasicBlock::Create(*context, "then", parentFunc);
  BasicBlock *elseBB = BasicBlock::Create(*context, "else");
  BasicBlock *mergeBB = BasicBlock::Create(*context, "ifcont");

  Value *condV = ifStmt->cond->accept(this);
  builder->CreateCondBr(condV, thenBB, elseBB);

  // Emit then value.
  builder->SetInsertPoint(thenBB);

  Value *thenV = ifStmt->stmt->accept(this);

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

Value *Codegen::visit(ASTIfElseStmt *ifStmt)
{
  Function *parentFunc = builder->GetInsertBlock()->getParent();
  // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
  BasicBlock *thenBB = BasicBlock::Create(*context, "then", parentFunc);
  BasicBlock *elseBB = BasicBlock::Create(*context, "else");
  BasicBlock *mergeBB = BasicBlock::Create(*context, "ifcont");

  Value *condV = ifStmt->cond->accept(this);
  builder->CreateCondBr(condV, thenBB, elseBB);

  // Emit then value.
  builder->SetInsertPoint(thenBB);
  ifStmt->stmt->accept(this);
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

llvm::Value *Codegen::visit(ASTFunctionCall *fncall)
{
    string fnName = fncall->fn->name;

    llvm::Function *calleeF = module->getFunction(fnName);
    if (!calleeF) {
        llvm::errs() << "Unknown function referenced: " << fnName << "\n";
        return nullptr;
    }

    vector<llvm::Value *> argsV;
    if (fncall->params) {
        for (auto &arg : fncall->params->exprs) {
          llvm::Value *argVal = arg->accept(this);
          if (!argVal) {
            return nullptr; 
          }
          if(llvm::isa<llvm::AllocaInst>(argVal))
            argsV.push_back(builder->CreateLoad(get_value_type(argVal), argVal));
          else
            argsV.push_back(argVal);
        }
    }

// Check for variadic fucntions and handle args accordingly
    if (!calleeF->getFunctionType()->isVarArg() && (calleeF->arg_size() != argsV.size())) {
    llvm::errs() << "Incorrect number of arguments for function " << fnName << "\n";
    return nullptr;
}

return builder->CreateCall(calleeF, argsV);
}

llvm::Value *Codegen::visit(ASTRetJmpStmt* retStmt) {
  if(retStmt->expr){
    llvm::Value* retVal = retStmt->expr->accept(this);
    if(!retVal){
      llvm::errs() << "Error generating code for return statement expression.\n";
      return nullptr;
    }
    return builder->CreateRet(retVal);
  } else {
    return builder->CreateRetVoid();
  }
}

llvm::Value *Codegen::visit(ASTExprStmt *expStmt){
  if(expStmt->exprs != nullptr)
    return expStmt->exprs->accept(this);

  return nullptr;
}


llvm::Value *Codegen::visit(ASTExpr *expr)
{
  op_type ot = get_op_type(expr->operator_);

  switch (ot)
  {
  case nop:
    llvm::errs() << "Invalid operator type in expression\n";
    assert(false);
  case unary:
    return visit_unary(expr);
  case binary:
    return visit_binary(expr);
  // case ternary:
  //   return visit_conditional(expr);
  case assignment:
    return visit_assignment(expr);
  default:
    assert(false);
  }
}

llvm::Value *Codegen::visit_binary(ASTExpr *expr)
{
  assert(expr->operands.size() == 2);

  llvm::Value *L = expr->operands[0]->accept(this);
  llvm::Value *R = expr->operands[1]->accept(this);

  assert(L && R);

  llvm::Type *typeL = get_value_type(L);
  llvm::Type *typeR = get_value_type(R);

  assert(typeL == typeR);

 if (L->getType()->isPointerTy()) {
    L = builder->CreateLoad(typeL, L);
  }
  if (R->getType()->isPointerTy()) {
    R = builder->CreateLoad(typeR, R);
  }

// codegen.dumpCode();

      if (typeL->isIntegerTy())
      {
        switch (expr->operator_)
        {
        case b_mul:
          return builder->CreateMul(L, R);
        case b_div:
          return builder->CreateSDiv(L, R);
        case b_remainder:
          return builder->CreateSRem(L, R);
        case b_add:
          return builder->CreateAdd(L, R);
        case b_minus:
          return builder->CreateSub(L, R);
        case b_left_shift:
          return builder->CreateShl(L, R);
        case b_right_shift:
          return builder->CreateLShr(L, R);
        case b_less:
          return builder->CreateICmpSLT(L, R);
        case b_greater:
          return builder->CreateICmpSGT(L, R);
        case b_less_eq:
          return builder->CreateICmpSLE(L, R);
        case b_greater_eq:
          return builder->CreateICmpSGE(L, R);
        case b_eq:
          return builder->CreateICmpEQ(L, R);
        case b_neq:
          return builder->CreateICmpNE(L, R);
        case b_bitand:
          return builder->CreateAnd(L, R);
        case b_bitxor:
          return builder->CreateXor(L, R);
        case b_bitor:
          return builder->CreateOr(L, R);
        case b_and:
          return builder->CreateLogicalAnd(L, R);
        case b_or:
          return builder->CreateLogicalOr(L, R);
        case t_cond:
          break;
        default:
          return nullptr;
        }
      }
      else if (typeL->isFloatingPointTy())
      {
        switch (expr->operator_)
        {
        case b_mul:
          return builder->CreateFMul(L, R);
        case b_div:
          return builder->CreateFDiv(L, R);
        case b_remainder:
          return builder->CreateFRem(L, R);
        case b_add:
          return builder->CreateFAdd(L, R);
        case b_minus:
          return builder->CreateFSub(L, R);
        case b_less:
          return builder->CreateFCmpOLT(L, R);
        case b_greater:
          return builder->CreateFCmpOGT(L, R);
        case b_less_eq:
          return builder->CreateFCmpOLE(L, R);
        case b_greater_eq:
          return builder->CreateFCmpOGE(L, R);
        case b_eq:
          return builder->CreateFCmpOEQ(L, R);
        case b_neq:
          return builder->CreateFCmpONE(L, R);
        case b_and:
          return builder->CreateLogicalAnd(L, R);
        case b_or:
          return builder->CreateLogicalOr(L, R);
        case t_cond:
          break;
        default:
          return nullptr;
        }
      }
     
  else
  {
    return nullptr;
  }
}


llvm::Value *Codegen::visit_unary(ASTExpr *unaryExp)
{
  assert(unaryExp->operands.size() == 1);

  llvm::Value *L = unaryExp->operands[0]->accept(this);

  if (!L)
    return nullptr;

  llvm::Type *typeL = L->getType();

  switch (unaryExp->operator_)
  {
  case u_op_plus_plus:
    if (typeL->isIntegerTy())
    {
      return builder->CreateAdd(L, llvm::ConstantInt::get(typeL, 1, true));
    }
    else if (typeL->isFloatingPointTy())
    {
      return builder->CreateFAdd(L, llvm::ConstantFP::get(typeL, 1.0));
    }

  case u_op_minus_minus:
    if (typeL->isIntegerTy())
    {
      return builder->CreateSub(L, llvm::ConstantInt::get(typeL, 1, true));
    }
    else if (typeL->isFloatingPointTy())
    {
      return builder->CreateFSub(L, llvm::ConstantFP::get(typeL, 1.0));
    }

  case u_op_and:
    return L;

    // case u_op_star:
    //   if (L->getType()->isPointerTy())
    //   {
    //     auto *pointerType = llvm::dyn_cast<llvm::PointerType>(L->getType());
    //     return builder->CreateLoad(pointerType->getPtrTy(), L);
    //     }
    //     else
    //     {
    //       return nullptr;
    //     }

  case u_op_plus:
    return L;

  case u_op_minus:
    if (typeL->isIntegerTy())
    {
      return builder->CreateNeg(L);
    }
    else if (typeL->isFloatingPointTy())
    {
      return builder->CreateFNeg(L);
    }

  case u_op_tilde:
    if (typeL->isIntegerTy())
    {
      return builder->CreateNot(L);
    }

  case u_op_not:
    auto size_in_bits = L->getType()->getPrimitiveSizeInBits();
    if (L->getType()->isFloatingPointTy())
    {
      return builder->CreateFCmpOEQ(L, llvm::ConstantFP::get(L->getType(), 0.0));
    }
    else if (L->getType()->isIntegerTy())
    {
      return builder->CreateICmpEQ(L, llvm::ConstantInt::get(L->getType(), 0, false));
    }
  }
}

Value *Codegen::visit(ASTWhileStmt * whileStmt) {
  Function *parentFunc = builder->GetInsertBlock()->getParent();

  BasicBlock *condBB = BasicBlock::Create(*context, "cond", parentFunc);
  BasicBlock *loopBB = BasicBlock::Create(*context, "loop", parentFunc);
  BasicBlock *afterBB = BasicBlock::Create(*context, "afterloop");

  builder->CreateBr(condBB);
  builder->SetInsertPoint(condBB);
  Value *condV = whileStmt->cond->accept(this);
  builder->CreateCondBr(condV, loopBB, afterBB);

  builder->SetInsertPoint(loopBB);
  whileStmt->stmt->accept(this);
  builder->CreateBr(condBB);

  parentFunc->insert(parentFunc->end(), afterBB);
  builder->SetInsertPoint(afterBB);

  return nullptr;
}

llvm::Value *Codegen::visit_assignment(ASTExpr *expr)
{
  assert(expr->operands.size() == 2);

  llvm::Value *L = expr->operands[0]->accept(this);
  llvm::Value *R = expr->operands[1]->accept(this);

  if(!L || !R) return nullptr;

  llvm::Type *typeL = L->getType();
  llvm::Type *typeR = R->getType();

  if(typeL != typeR) return nullptr;

  llvm::Value *result = nullptr;


  return builder->CreateStore(R, builder->CreateLoad(typeL, L));
}

// }
