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

    FunctionType* fnType = nullptr;

    vector<map<std::string, llvm::Value *>> symbolTable;
    bool is_scope_incomplete = false;

    explicit Codegen(const string& file_name): Visitor(){
      context = make_unique<llvm::LLVMContext>();
      module = make_unique<llvm::Module>(file_name, *context);
      builder = make_unique<llvm::IRBuilder<>>(*context);
    }

    void dump_ast() const{
      module->print(llvm::outs(), nullptr);
    }

    Value* visit(ASTProgram*);

    Value* visit(ASTFnDef*);

    Value* visit(ASTGlobalVar*);

    Value *visit(ASTConst *) const;

    Value *visit(ASTBlockList*);

    Value *visit(ASTBlock*);

    Value *visit(ASTDeclList *decls);

    Value *visit(ASTDecl *decl);

    Value *visit(ASTIdExpr* idExpr);

private:
    [[nodiscard]] llvm::Type *ctype_2_llvmtype(ctype_ ctype, bool is_ptr=false) const {
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

    void enter_scope(){
      map<std::string, llvm::Value *> newContext;
      if(is_scope_incomplete){
        assert(symbolTable.size() == 1);
        is_scope_incomplete = false;
        return;
      }
      symbolTable.push_back(newContext);
    }

    void enter_scope(FunctionType* ft){
      enter_scope();
      this->fnType = ft;
      is_scope_incomplete = true;
    }

    void add_variable(const string& name, llvm::Value* arg){
      auto result = symbolTable.back().insert(make_pair(name, arg));
      if(!result.second){
        cout << "Duplicate variable name" << endl;
        assert(false);
      }
    }

    Value* find_variable(const string& name){
      for(auto symbols = symbolTable.rbegin(); symbols != symbolTable.rend(); symbols++){
        auto symbol = symbols->find(name);
        if(symbol != symbols->end())
          return symbol->second;
      }
      if(auto gv = module->getGlobalVariable(name) != nullptr){
        return nullptr;
      }

      cout << "No variable named " << name << endl;
      assert(false);
    }

    void exit_scope(){
      symbolTable.pop_back();
    }

    [[nodiscard]] AllocaInst* create_alloca_of_type(ctype_ t, const string& name) const{
      switch (t) {
        case t_void:
          cout << "Cannot be void";
          assert(false);
        case t_char:
          return builder->CreateAlloca(Type::getInt8Ty(*context), nullptr, name);
        case t_short:
          return builder->CreateAlloca(Type::getInt16Ty(*context), nullptr, name);
        case t_int:
        case t_long:
          return builder->CreateAlloca(Type::getInt32Ty(*context), nullptr, name);
        case t_long_long:
          return builder->CreateAlloca(Type::getInt64Ty(*context), nullptr, name);
        case t_float:
          return builder->CreateAlloca(Type::getFloatTy(*context), nullptr, name);
        case t_double:
          return builder->CreateAlloca(Type::getDoubleTy(*context), nullptr, name);
        case t_signed:
          cout << "Doesn't support signed";
          assert(false);
        case t_unsigned:
          cout << "Doesn't support unsigned";
          assert(false);
        case t_bool:
          return builder->CreateAlloca(Type::getInt8Ty(*context), nullptr, name);
        case t_complex:
          cout << "Doesn't support complex";
          assert(false);
        case t_imaginary:
          cout << "Doesn't support imaginary";
          assert(false);
      }
    }

};


#endif //CCOMPILER_CODEGEN_H
