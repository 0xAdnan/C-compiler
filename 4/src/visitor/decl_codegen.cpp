//
// Created by satyam on 29/3/24.
//

#include "codegen.h"

llvm::Value *Codegen::visit(ASTProgram *program) {
  int i = 0;
  for (; i < program->extDecls.size() - 1; i++)
    program->extDecls[i]->accept(this);

  return program->extDecls[i]->accept(this);
}

llvm::Value *Codegen::visit(ASTFnDef *fnDef) {
  Function *fn = module->getFunction(fnDef->fnDecl->name);

  if (!fn) {
    vector<Type *> params;

    bool is_variadic = false;
    if (fnDef->fnDecl->params) {
      for (auto p: fnDef->fnDecl->params->paramList->params)
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
  if (fnDef->fnDecl->params) {
    for (auto &arg: fn->args()) {
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

llvm::Value *Codegen::visit(ASTBlockList *blockList) {
  llvm::Value *v;
  enter_scope();
  for (auto block: blockList->blocks) {
    v = block->accept(this);
  }
  exit_scope();
  return v;
}

Value *Codegen::visit(ASTBlock *block) {
  if (block->declaration)
    return block->declaration->accept(this);
  else
    return block->stmt->accept(this);
}

llvm::Value *Codegen::visit(ASTGlobalVar *globalVar) {
  llvm::Value *val;

  for (auto &decl: globalVar->declaration->declarations) {
    vector<Type *> params;
    if (decl->fnDecl) {
      for (auto p: decl->fnDecl->params->paramList->params)
        params.push_back(ctype_2_llvmtype(p->type, p->num_ptr > 0));

      FunctionType *FT = FunctionType::get(
              ctype_2_llvmtype(decl->type, decl->num_ptr > 0),
              params,
              decl->fnDecl->params->is_variadic);
      val = Function::Create(FT, Function::ExternalLinkage, decl->name, *module);
    } else if (decl->value) {
      for (auto global = module->global_begin(); global != module->global_end(); ++global) {
        if (global->getName() == decl->name) {
          global->eraseFromParent();
          break;
        }
      }
      auto constant = (llvm::Constant *) (decl->value->accept(this));

      if (constant == nullptr) {
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
    } else {
      for (auto global = module->global_begin(); global != module->global_end(); ++global) {
        if (global->getName() == decl->name) {
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
      ((GlobalVariable *) val)->setDSOLocal(true);
    }
  }

  return val;
}

llvm::Value *Codegen::visit(ASTDeclList *decls) {
  llvm::Value *v;
  for (auto d: decls->declarations) {
    v = d->accept(this);
  }
  return v;
}

llvm::Value *Codegen::visit(ASTDecl *decl) {
  if (decl->is_const)
    cout << "Not supporting Const Semantics" << endl;
  AllocaInst *allocaInst = create_alloca_of_type(decl->type, decl->name);

  if (decl->value) {
    llvm::Value *v = decl->value->accept(this);
    builder->CreateStore(v, allocaInst);
  }

  add_variable(decl->name, allocaInst);

  return allocaInst;
}



