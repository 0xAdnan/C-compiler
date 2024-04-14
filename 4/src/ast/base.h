//
// Created by satyam on 29/3/24.
//

#ifndef CCOMPILER_BASE_H
#define CCOMPILER_BASE_H

#include <llvm/IR/Value.h>
#include "vector"
#include "string"
#include "iostream"
#include "enums.h"


class Codegen;

using namespace std;


class ASTNode {
protected:
    ASTNode() { children = vector<ASTNode *>(); }

    void add_child(ASTNode *child);

public:
    vector<ASTNode *> children;

    [[nodiscard]] virtual string to_str() const = 0;

    void dump_ast(int indent);

    virtual llvm::Value *accept(Codegen *codegen);
};


#endif //CCOMPILER_BASE_H
