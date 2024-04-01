//
// Created by satyam on 29/3/24.
//

#include "Codegen.h"


llvm::Value* Codegen::visit(ASTProgram* program){
  int i=0;
  for(; i<program->extDecls.size()-1; i++)
    program->extDecls[i]->accept(this);
  return program->extDecls[i]->accept(this);
}

llvm::Value *Codegen::visit(ASTFnDef *fnDef) {
  Function *fnDecl = module->getFunction(fnDef->idDecl->name);

  /*if (!fnDecl){
    fnDecl = new
  }*/

  return fnDecl;
}

llvm::Value *Codegen::visit(ASTGlobalVar *globalVar) {
  vector<llvm::Value*> values;

  for(auto &decl: globalVar->declaration->declarations){
    vector<Type*> params;
    if(decl->fnDecl){
      for(auto p: decl->fnDecl->params->paramList->params){
        params.push_back(ctype_2_llvmtype(p->type, p->num_ptr > 0));
      }

      FunctionType *FT = FunctionType::get(
         ctype_2_llvmtype(decl->type, decl->num_ptr > 0),
         params,
         decl->fnDecl->params->is_variadic
      );
      values.push_back(
          Function::Create(FT, Function::ExternalLinkage, decl->name, *module)
      );
    }
    else if(decl->value){
      for (auto global = module->global_begin(); global != module->global_end(); ++global){
        if(global->getName() == decl->name){
          global->eraseFromParent();
          break;
        }
      }
      auto constant = (llvm::Constant*)(decl->value->accept(this));
      assert(constant != nullptr);
      values.push_back(
          new llvm::GlobalVariable(
                  *module,
                  ctype_2_llvmtype(decl->type, decl->num_ptr > 0),
                  decl->is_const,
                  llvm::GlobalValue::ExternalLinkage,
                  constant, decl->name
          )
      );
    }
    else{
      for (auto global = module->global_begin(); global != module->global_end(); ++global){
        if(global->getName() == decl->name){
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
            nullptr, decl->name
        )
      );
    }
  }

  return values[0];
}

llvm::Value* Codegen::visit(ASTConst *constant) const {
  switch (constant->ct) {
    case i_const:
//      return llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), stoi(constant->value));
      return llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), 5);
    case f_const:
      return llvm::ConstantFP::get(llvm::Type::getInt32Ty(*context), stof(constant->value));
    case s_const:
      return ConstantDataArray::getString(module->getContext(), constant->value, true);
  }
}

/*
llvm::Value *Codegen::visit(ASTDecl *decl) {
  return nullptr;
}
*/
