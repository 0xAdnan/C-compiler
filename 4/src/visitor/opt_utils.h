//
// Created by satyam on 19/4/24.
//

#ifndef CCOMPILER_OPT_UTILS_H
#define CCOMPILER_OPT_UTILS_H


#include "base.h"
#include "expr.h"

static bool is_const_node(ASTNode* node, const string& value){
  auto constNode = dynamic_cast<ASTConst*>(node);
  if(constNode == nullptr)
    return false;
  return constNode->value == value;
}

#endif //CCOMPILER_OPT_UTILS_H
