//
// Created by satyam on 14/4/24.
//
#include "codegen.h"

llvm::Value *Codegen::visit(ASTExprStmt *expStmt) {
  if (expStmt->exprs != nullptr)
    return expStmt->exprs->accept(this);

  return nullptr;
}

llvm::Value *Codegen::visit(ASTConst *constant) {
  switch (constant->ct) {
    case i_const:
      return llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), stoi(constant->value));
    case f_const:
      return llvm::ConstantFP::get(llvm::Type::getDoubleTy(*context), stof(constant->value));
    case s_const:
      auto string_const = ConstantDataArray::getString(module->getContext(), constant->value, true);

      // Create a global variable with the constant string
      auto *strVar = new llvm::GlobalVariable(
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

Value *Codegen::visit(ASTIdExpr *idExpr) {
  return find_variable(idExpr->name);
}

llvm::Value *Codegen::visit(ASTExpr *expr) {
  op_type ot = get_op_type(expr->operator_);

  switch (ot) {
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

llvm::Value *Codegen::visit_binary(ASTExpr *expr) {
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

  if (typeL->isIntegerTy()) {
    switch (expr->operator_) {
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
  } else if (typeL->isFloatingPointTy()) {
    switch (expr->operator_) {
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
  } else {
    return nullptr;
  }
}

llvm::Value *Codegen::visit_unary(ASTExpr *unaryExp) {
  assert(unaryExp->operands.size() == 1);

  llvm::Value *L = unaryExp->operands[0]->accept(this);

  if (!L)
    return nullptr;

  llvm::Type *typeL = L->getType();

  switch (unaryExp->operator_) {
    case u_op_plus_plus:
      if (typeL->isIntegerTy()) {
        return builder->CreateAdd(L, llvm::ConstantInt::get(typeL, 1, true));
      } else if (typeL->isFloatingPointTy()) {
        return builder->CreateFAdd(L, llvm::ConstantFP::get(typeL, 1.0));
      }

    case u_op_minus_minus:
      if (typeL->isIntegerTy()) {
        return builder->CreateSub(L, llvm::ConstantInt::get(typeL, 1, true));
      } else if (typeL->isFloatingPointTy()) {
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
      if (typeL->isIntegerTy()) {
        return builder->CreateNeg(L);
      } else if (typeL->isFloatingPointTy()) {
        return builder->CreateFNeg(L);
      }

    case u_op_tilde:
      if (typeL->isIntegerTy()) {
        return builder->CreateNot(L);
      }

    case u_op_not:
      auto size_in_bits = L->getType()->getPrimitiveSizeInBits();
      if (L->getType()->isFloatingPointTy()) {
        return builder->CreateFCmpOEQ(L, llvm::ConstantFP::get(L->getType(), 0.0));
      } else if (L->getType()->isIntegerTy()) {
        return builder->CreateICmpEQ(L, llvm::ConstantInt::get(L->getType(), 0, false));
      }
  }
}

llvm::Value *Codegen::visit_assignment(ASTExpr *expr) {
  assert(expr->operands.size() == 2);

  llvm::Value *L = expr->operands[0]->accept(this);
  llvm::Value *R = expr->operands[1]->accept(this);

  if (!L || !R) {
    llvm::errs() << "Error generating code for assignment\n";
    assert(false);
  }

  llvm::Type *typeL = get_value_type(L);
  llvm::Type *typeR = get_value_type(R);

  if (typeL != typeR) {
    llvm::errs() << "Type mismatch in assignment\n";
    assert(false);
  }

  if (!llvm::isa<llvm::AllocaInst>(R)) {
    switch (expr->operator_) {
      case mul_assign:
        R = builder->CreateMul(builder->CreateLoad(typeL, L), R);
        break;
      case div_assign:
        R = builder->CreateSDiv(builder->CreateLoad(typeL, L), R);
        break;
      case mod_assign:
        R = builder->CreateSRem(builder->CreateLoad(typeL, L), R);
        break;
      case add_assign:
        R = builder->CreateAdd(builder->CreateLoad(typeL, L), R);
        break;
      case sub_assign:
        R = builder->CreateSub(builder->CreateLoad(typeL, L), R);
        break;
      case left_assign:
        R = builder->CreateShl(builder->CreateLoad(typeL, L), R);
        break;
      case right_assign:
        R = builder->CreateLShr(builder->CreateLoad(typeL, L), R);
        break;
      case and_assign:
        R = builder->CreateAnd(builder->CreateLoad(typeL, L), R);
        break;
      case xor_assign:
        R = builder->CreateXor(builder->CreateLoad(typeL, L), R);
        break;
      case or_assign:
        R = builder->CreateOr(builder->CreateLoad(typeL, L), R);
        break;
      default:
        break;
    }
    return builder->CreateStore(R, L);
  }


  switch (expr->operator_) {
    case mul_assign:
      R = builder->CreateMul(builder->CreateLoad(typeL, L), builder->CreateLoad(typeR, R));
      break;
    case div_assign:
      R = builder->CreateSDiv(builder->CreateLoad(typeL, L), builder->CreateLoad(typeR, R));
      break;
    case mod_assign:
      R = builder->CreateSRem(builder->CreateLoad(typeL, L), builder->CreateLoad(typeR, R));
      break;
    case add_assign:
      R = builder->CreateAdd(builder->CreateLoad(typeL, L), builder->CreateLoad(typeR, R));
      break;
    case sub_assign:
      R = builder->CreateSub(builder->CreateLoad(typeL, L), builder->CreateLoad(typeR, R));
      break;
    case left_assign:
      R = builder->CreateShl(builder->CreateLoad(typeL, L), builder->CreateLoad(typeR, R));
      break;
    case right_assign:
      R = builder->CreateLShr(builder->CreateLoad(typeL, L), builder->CreateLoad(typeR, R));
      break;
    case and_assign:
      R = builder->CreateAnd(builder->CreateLoad(typeL, L), builder->CreateLoad(typeR, R));
      break;
    case xor_assign:
      R = builder->CreateXor(builder->CreateLoad(typeL, L), builder->CreateLoad(typeR, R));
      break;
    case or_assign:
      R = builder->CreateOr(builder->CreateLoad(typeL, L), builder->CreateLoad(typeR, R));
      break;
    default:
      R = builder->CreateLoad(typeR, R);
      break;
  }
  return builder->CreateStore(R, L);
}

llvm::Value *Codegen::visit(ASTFunctionCall *fncall) {
  string fnName = fncall->fn->name;

  llvm::Function *calleeF = module->getFunction(fnName);
  if (!calleeF) {
    llvm::errs() << "Unknown function referenced: " << fnName << "\n";
    return nullptr;
  }

  vector<llvm::Value *> argsV;
  if (fncall->params) {
    for (auto &arg: fncall->params->exprs) {
      llvm::Value *argVal = arg->accept(this);
      if (!argVal) {
        return nullptr;
      }
      if (llvm::isa<llvm::AllocaInst>(argVal))
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