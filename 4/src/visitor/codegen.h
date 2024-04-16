//
// Created by satyam on 29/3/24.
//

#ifndef CCOMPILER_CODEGEN_H
#define CCOMPILER_CODEGEN_H


#include "visitor.h"
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
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"


using namespace llvm;

class Codegen : public Visitor {
public:
    unique_ptr<llvm::LLVMContext> context;
    unique_ptr<llvm::IRBuilder<>> builder;
    unique_ptr<llvm::Module> module;

    FunctionType *fnType = nullptr;

    vector<map < std::string, llvm::Value *>> symbolTable;
    bool is_scope_incomplete = false;

    explicit Codegen(const string &file_name) : Visitor() {
      context = make_unique<llvm::LLVMContext>();
      module = make_unique<llvm::Module>(file_name, *context);
      builder = make_unique<llvm::IRBuilder<>>(*context);
    }

    void dumpCode() const {
      module->print(llvm::outs(), nullptr);
    }


    void dumpFile(const std::string &filename) const {
      std::error_code EC;
      llvm::raw_fd_ostream file(filename, EC, llvm::sys::fs::OF_Text);

      if (EC) {
        llvm::errs() << "Error opening file: " << EC.message() << "\n";
        return;
      }

      module->print(file, nullptr);
    }

    Value *visit(ASTProgram *);

    Value *visit(ASTFnDef *);

    Value *visit(ASTGlobalVar *);

    Value *visit(ASTBlockList *);

    Value *visit(ASTBlock *);

    Value *visit(ASTDeclList *);

    Value *visit(ASTDecl *);

    Value *visit(ASTIdExpr *);

    Value *visit(ASTIfStmt *);

    Value *visit(ASTIfElseStmt *);

    Value *visit(ASTExpr *);

    Value *visit(ASTConst *);

    Value *visit(ASTFunctionCall *);

    Value *visit(ASTExprStmt *);

    Value *visit(ASTRetJmpStmt *);

    Value *visit(ASTWhileStmt *);

    Value *visit(ASTForStmt *);

    Value *visit(ASTForStmt2 *);

    Value *visit(ASTBreakJmpStmt *);

    Value *visit(ASTContJmpStmt *);

    Value *visit(ASTGotoLabeledStmt *);

    Value *visit(ASTGotoJmpStmt *);

private:
    llvm::BasicBlock *breakBlock = nullptr;
    llvm::BasicBlock *contBlock = nullptr;

    llvm::BasicBlock *prevBreakBlock = nullptr;
    llvm::BasicBlock *prevContBlock = nullptr;

    map<string, llvm::BasicBlock *> labelMap;
    int completedLabels = 0;

    [[nodiscard]] llvm::Type *ctype_2_llvmtype(ctype_ ctype, bool is_ptr = false) const {
      if (is_ptr)
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

    void enter_scope() {
      map < std::string, llvm::Value * > newContext;
      if (is_scope_incomplete) {
        assert(symbolTable.size() == 1);
        is_scope_incomplete = false;
        return;
      }
      symbolTable.push_back(newContext);
    }

    void enter_scope(FunctionType *ft) {
      enter_scope();
      this->fnType = ft;
      is_scope_incomplete = true;
    }

    void add_variable(const string &name, llvm::Value *arg) {
      auto result = symbolTable.back().insert(make_pair(name, arg));
      if (!result.second) {
        string msg = "Duplicate variable: " + name;
        llvm::errs() << msg << "\n";
        assert(false);
      }
    }

    Value *find_variable(const string &name) {
      for (auto symbols = symbolTable.rbegin(); symbols != symbolTable.rend(); symbols++) {
        auto symbol = symbols->find(name);
        if (symbol != symbols->end())
          return symbol->second;
      }
      if (auto gv = module->getGlobalVariable(name) != nullptr) {
        return nullptr;
      }

      string msg = "No variable named: " + name;
      llvm::errs() << msg << "\n";
      assert(false);
    }

    void exit_scope() {
      symbolTable.pop_back();
    }

    [[nodiscard]] AllocaInst *create_alloca_of_type(ctype_ t, const string &name) const {
      switch (t) {
        case t_void:
          llvm::errs() << "Cannot be void" << "\n";
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
          llvm::errs() << "Doesn't support signed" << "\n";
          assert(false);
        case t_unsigned:
          llvm::errs() << "Doesn't support unsigned" << "\n";
          assert(false);
        case t_bool:
          return builder->CreateAlloca(Type::getInt8Ty(*context), nullptr, name);
        case t_complex:
          llvm::errs() << "Doesn't support complex" << "\n";
          assert(false);
        case t_imaginary:
          llvm::errs() << "Doesn't support imaginary" << "\n";
          assert(false);
      }
    }

    void enter_loop(llvm::BasicBlock *breakBlock, llvm::BasicBlock *contBlock) {
      prevBreakBlock = this->breakBlock;
      prevContBlock = this->contBlock;

      this->breakBlock = breakBlock;
      this->contBlock = contBlock;
    }

    void exit_loop() {
      this->breakBlock = prevBreakBlock;
      this->contBlock = prevContBlock;
    }


    llvm::Value *visit_unary(ASTExpr *expr);

    llvm::Value *visit_binary(ASTExpr *expr);

    llvm::Value *visit_conditional(ASTExpr *expr);

    llvm::Value *visit_assignment(ASTExpr *expr);

    bool is_ptr(llvm::Value* val){
      return false;
    }

    llvm::Type *get_value_type(llvm::Value *value) {
      if (!value) return nullptr;

      if (auto *allocaInst = llvm::dyn_cast<llvm::AllocaInst>(value)) {
        return allocaInst->getAllocatedType();
      } else if (auto *constant = llvm::dyn_cast<llvm::Constant>(value)) {
        return constant->getType();
      } else {
        return value->getType();
      }
    }

    static bool is_const_expr(ASTExpr *expr) {
      auto const_ = dynamic_cast<ASTConst *>(expr);
      return const_ != nullptr;
    }

    

};


#endif //CCOMPILER_CODEGEN_H
