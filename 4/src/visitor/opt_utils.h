//
// Created by satyam on 19/4/24.
//

#ifndef CCOMPILER_OPT_UTILS_H
#define CCOMPILER_OPT_UTILS_H

#include "base.h"
#include "expr.h"


static bool is_const_node(ASTNode *node, const string &value)
{
    auto constNode = dynamic_cast<ASTConst *>(node);
    if (constNode == nullptr)
        return false;
    return constNode->value == value;
}

static ASTConst *check_const(ASTNode *node)
{
    return dynamic_cast<ASTConst *>(node);
}

static ASTConst *performOperation(const ASTConst *left, const ASTConst *right, operators op)
{
    if (!left || !right)
        return nullptr;

    int leftValue = (left->ct == const_type::i_const) ? stoi(left->value) : stof(left->value);
    int rightValue = (right->ct == const_type::i_const) ? stoi(right->value) : stof(right->value);
    int result;

    switch (op)
    {
    case operators::b_add:
        result = leftValue + rightValue;
        break;
    case operators::b_minus:
        result = leftValue - rightValue;
        break;
    case operators::b_mul:
        result = leftValue * rightValue;
        break;
    case operators::b_div:
        if (rightValue == 0)
        {
            throw runtime_error("Division by zero");
        }
        result = leftValue / rightValue;
        break;
    case operators::b_left_shift:
        result = leftValue << rightValue;
        break;
    case operators::b_right_shift:
        result = leftValue >> rightValue;
        break;
    case operators::b_less:
        result = leftValue < rightValue;
        break;
    case operators::b_greater:
        result = leftValue > rightValue;
        break;
    case operators::b_less_eq:
        result = leftValue <= rightValue;
        break;
    case operators::b_greater_eq:
        result = leftValue >= rightValue;
        break;
    case operators::b_eq:
        result = leftValue == rightValue;
        break;
    case operators::b_neq:
        result = leftValue != rightValue;
        break;
    case operators::b_bitand:
        result = leftValue & rightValue;
        break;
    case operators::b_bitxor:
        result = leftValue ^ rightValue;
        break;
    case operators::b_bitor:
        result = leftValue | rightValue;
        break;
    case operators::b_and:
        result = leftValue && rightValue;
        break;
    case operators::b_or:
        result = leftValue || rightValue;
        break;
    default:
        throw invalid_argument("Unsupported operator for const operation");
    }

    const_type resultType = (left->ct == const_type::f_const || right->ct == const_type::f_const) ? const_type::f_const : const_type::i_const;
    return new ASTConst(resultType, std::to_string(result));
}

#endif // CCOMPILER_OPT_UTILS_H
