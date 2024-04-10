//
// Created by satyam on 29/3/24.
//

#include "Codegen.h"

llvm::Value *Codegen::visit(ASTProgram *program)
{
  int i = 0;
  for (; i < program->extDecls.size() - 1; i++)
    program->extDecls[i]->accept(this);
  return program->extDecls[i]->accept(this);
}

llvm::Value *Codegen::visit(ASTFnDef *fnDef)
{
  Function *fnDecl = module->getFunction(fnDef->idDecl->name);

  /*if (!fnDecl){
    fnDecl = new
  }*/

  return fnDecl;
}

llvm::Value *Codegen::visit(ASTGlobalVar *globalVar)
{
  vector<llvm::Value *> values;

  for (auto &decl : globalVar->declaration->declarations)
  {
    vector<Type *> params;
    if (decl->fnDecl)
    {
      for (auto p : decl->fnDecl->params->paramList->params)
      {
        params.push_back(ctype_2_llvmtype(p->type, p->num_ptr > 0));
      }

      FunctionType *FT = FunctionType::get(
          ctype_2_llvmtype(decl->type, decl->num_ptr > 0),
          params,
          decl->fnDecl->params->is_variadic);
      values.push_back(
          Function::Create(FT, Function::ExternalLinkage, decl->name, *module));
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
      assert(constant != nullptr);
      values.push_back(
          new llvm::GlobalVariable(
              *module,
              ctype_2_llvmtype(decl->type, decl->num_ptr > 0),
              decl->is_const,
              llvm::GlobalValue::ExternalLinkage,
              constant, decl->name));
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
      values.push_back(
          new llvm::GlobalVariable(
              *module,
              ctype_2_llvmtype(decl->type, decl->num_ptr > 0),
              decl->is_const,
              llvm::GlobalValue::ExternalLinkage,
              nullptr, decl->name));
    }
  }

  return values[0];
}

llvm::Value *Codegen::visit(ASTConst *constant) const
{
  switch (constant->ct)
  {
  case i_const:
    //      return llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), stoi(constant->value));
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 5);
  case f_const:
    return llvm::ConstantFP::get(llvm::Type::getInt32Ty(*context), stof(constant->value));
  case s_const:
    return ConstantDataArray::getString(module->getContext(), constant->value, true);
  }
}

llvm::Value *Codegen::visit(ASTExpr *expr)
{
  llvm::Value *L = expr->operands[0]->accept(this);
  llvm::Value *R = expr->operands[1]->accept(this);

  if (!L || !R)
    return nullptr;

  op_type ot = get_op_type(expr->operator_);

  switch (ot)
  {
  case unary:
    return visit_unary(expr);
  case binary:
    return visit_binary(expr);
  // case ternary:
  //   return visit_conditional(expr);
  // case assignment:
  //   return visit_assignment(expr);
  default:
    assert(false);
  }
}

llvm::Value *Codegen::visit_binary(ASTExpr *expr)
{
  assert(expr->operands.size() == 2);

  llvm::Value *L = expr->operands[0]->accept(this);
  llvm::Value *R = expr->operands[1]->accept(this);

  if (!L || !R)
    return nullptr;

  llvm::Type *typeL = L->getType();
  llvm::Type *typeR = R->getType();

  if (typeL != typeR)
    return nullptr;

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

// llvm::Value *Codegen::visit_assignment(ASTExpr *expr)
// {
//   assert(expr->operands.size() == 2);

//   llvm::Value *L = expr->operands[0]->accept(this);
//   llvm::Value *R = expr->operands[1]->accept(this);

//   if(!L || !R) return nullptr;

//   llvm::Type *typeL = L->getType();
//   llvm::Type *typeR = R->getType();

//   if(typeL != typeR) return nullptr;

//   llvm::Value *result = nullptr;

//   switch(expr->operator_){
//     case assign:
//       result = builder->CreateStore(R, L);
//     case mul_assign:
//       result = builder->CreateStore(builder->CreateMul(L,R), L);
//     case div_assign:
//       if(typeL->isIntegerTy())
//         result = builder->CreateStore(builder->CreateSDiv(L,R), L);
//     else if(typeL->isFloatingPointTy())
//           result = builder->CreateStore(builder->CreateFDiv(L,R), L);
//     case mod_assign:
//       if(typeL->isIntegerTy())
//         result = builder->CreateStore(builder->CreateSRem(L,R), L);
//     else if (typeL->isFloatingPointTy())
//           result = builder->CreateStore(builder->CreateFRem(L,R),L);
//     // case add_assign:
      
      
//   }

// }
