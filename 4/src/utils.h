#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Instructions.h>
#include "expr.h"

//
// Created by satyam on 13/4/24.
//
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

