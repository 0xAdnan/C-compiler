//
// Created by satyam on 29/3/24.
//

#ifndef CCOMPILER_BASE_H
#define CCOMPILER_BASE_H

#include "vector"
#include "string"
#include "iostream"

#include "../visitor/Visitor.h"
using namespace std;


class ASTNode {
protected:
    ASTNode() { children = vector<ASTNode *>(); }
    void add_child(ASTNode *child);

public:
    vector<ASTNode *> children;
    virtual string to_str() const = 0;
    void dump_ast(int indent);
    void accept(Visitor *visitor);
};


#endif //CCOMPILER_BASE_H
