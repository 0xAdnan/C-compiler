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

class AlgebraSimplificationOpt;

class ConstPropagationOpt;

class DeadCodeOpt;

class Printer;

using namespace std;


class ASTNode {
protected:
    ASTNode() {}

public:

    [[nodiscard]] virtual string to_str() const = 0;

    virtual llvm::Value *accept(Codegen *);

    virtual ASTNode *accept(AlgebraSimplificationOpt *);

    virtual ASTNode *accept(ConstPropagationOpt *);

    virtual ASTNode *accept(DeadCodeOpt *);

    virtual string accept(Printer *, int);
};


#endif //CCOMPILER_BASE_H
