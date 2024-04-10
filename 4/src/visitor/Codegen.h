//
// Created by satyam on 29/3/24.
//

#ifndef CCOMPILER_CODEGEN_H
#define CCOMPILER_CODEGEN_H


#include "Visitor.h"
#include "enums.h"

#include <llvm-17/llvm/IR/GlobalVariable.h>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "prog.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <llvm-17/llvm/IR/Constant.h>
#include <llvm-17/llvm/IR/GlobalVariable.h>
#include <llvm-17/llvm/IR/Value.h>
#include <map>
#include <memory>

using namespace llvm;

class Codegen: public Visitor {
public:
    unique_ptr<llvm::LLVMContext> context;
    unique_ptr<llvm::IRBuilder<>> builder;
    unique_ptr<llvm::Module> module;

    map<std::string, llvm::Value *> env;

    Codegen(): Visitor(){
      context = make_unique<llvm::LLVMContext>();
      module = make_unique<llvm::Module>("Module", *context);
      builder = make_unique<llvm::IRBuilder<>>(*context);
    }

    void dump_ast() const{
      module->print(llvm::outs(), nullptr);
    }

    llvm::Value* visit(ASTProgram* program);

    llvm::Value* visit(ASTFnDef* fnDef);

    llvm::Value* visit(ASTGlobalVar* globalVar);

    llvm::Value *visit(ASTConst *constant) const;

    llvm::Value *visit(ASTExpr *expr);

//    llvm::Value *visit(ASTDecl *decl);

private:
    llvm::Type *ctype_2_llvmtype(ctype_ ctype, bool is_ptr=false) {
      if(is_ptr)
        return llvm::Type::getInt64PtrTy(*context);
      switch (ctype) {
        case ctype_::t_int:
          return llvm::Type::getInt32Ty(*context);
        case ctype_::t_bool:
          return llvm::Type::getInt1Ty(*context);
        case ctype_::t_char:
          return llvm::Type::getInt8Ty(*context);
        case ctype_::t_float:
          return llvm::Type::getFloatTy(*context);
        default:
          cout << "Doesn't Support DataType " << ctype << endl;
          exit(1);
      }
    }

  llvm::Value* visit_unary(ASTExpr* expr);
  llvm::Value* visit_binary(ASTExpr* expr);
  llvm::Value* visit_conditional(ASTExpr* expr);
  llvm::Value* visit_assignment(ASTExpr* expr);
  
};


#endif //CCOMPILER_CODEGEN_H
