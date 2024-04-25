//
// Created by satyam on 18/4/24.
//

#include "const_prop_opt.h"
#include "opt_utils.h"

ASTProgram *ConstPropagationOpt::visit(ASTProgram *prog)
{
    for (auto &extDecl : prog->extDecls)
    {
        ASTFnDef *fnDef = dynamic_cast<ASTFnDef *>(extDecl);
        if (fnDef)
        {
            fnDef = fnDef->accept(this);
        }
    }
    return prog;
}

ASTFnDef *ConstPropagationOpt::visit(ASTFnDef *fnDef)
{
    if (fnDef->body)
    {
        fnDef->body = fnDef->body->accept(this);
    }
    return fnDef;
}

ASTBlock *ConstPropagationOpt::visit(ASTBlock *block)
{
    if (block->declaration)
    {
        vector<ASTDecl *> updatedDeclarations;
        for (auto &decl : block->declaration->declarations)
        {
            updatedDeclarations.push_back(decl->accept(this));
        }
        block->declaration->declarations = updatedDeclarations;
    }

    if (block->stmt)
    {
        block->stmt = block->stmt->accept(this);
    }
    return block;
}

ASTStmt *ConstPropagationOpt::visit(ASTStmt *stmt)
{
    return stmt;
}

ASTBlockList *ConstPropagationOpt::visit(ASTBlockList *bl)
{
    vector<ASTBlock *> newBlockList;
    for (auto block : bl->blocks)
    {
        auto newBlock = block->accept(this);
        if (newBlock != nullptr)
        {
            newBlockList.push_back(newBlock);
        }
    }
    bl->blocks = newBlockList;
    return bl;
}

// ASTDecl *ConstPropagationOpt::visit(ASTDecl *Decl)
// {
//     if (Decl && Decl->value)
//     {
//         ASTConst *constNode = check_const(Decl->value);
//         if (constNode)
//         {
//             constValues[Decl->name] = constNode;
//         }
//         else
//         {
//             Decl->value = Decl->value->accept(this);
//             constNode = check_const(Decl->value);
//             if (constNode)
//             {
//                 constValues[Decl->name] = constNode;
//             }
//         }
//     }
//     return Decl;
// }

ASTDecl *ConstPropagationOpt::visit(ASTDecl *Decl)
{
    if (Decl && Decl->value)
    {
        ASTConst *constNode = check_const(Decl->value);
        if (constNode)
        {
            if (!constValues.empty())
            {
                constValues.back()[Decl->name] = constNode;
            }
        }
        else
        {
            Decl->value = Decl->value->accept(this);
            constNode = check_const(Decl->value);
            if (constNode)
            {
                if (!constValues.empty())
                {
                    constValues.back()[Decl->name] = constNode;
                }
            }
        }
    }
    return Decl;
}

ASTExprStmt *ConstPropagationOpt::visit(ASTExprStmt *expStmt)
{
    if (expStmt && expStmt->exprs)
    {
        vector<ASTExpr *> newExprs;
        for (ASTExpr *expr : expStmt->exprs->exprs)
        {
            expr = expr->accept(this);
            newExprs.push_back(expr);
        }
        expStmt->exprs->exprs = newExprs;
    }
    return expStmt;
}

ASTExpr *ConstPropagationOpt::visit(ASTIdExpr *idExpr)
{
    for (auto it = constValues.rbegin(); it != constValues.rend(); ++it)
    {
        auto found = it->find(idExpr->name);
        if (found != it->end())
        {
            return new ASTConst(*(found->second));
        }
    }
    return idExpr;
}

// ASTExpr *ConstPropagationOpt::visit(ASTIdExpr *idExpr)
// {
//     if (constValues.find(idExpr->name) != constValues.end())
//     {
//         return new ASTConst(*constValues[idExpr->name]);
//     }
//     return idExpr;
// }

ASTExpr *ConstPropagationOpt::visit(ASTExpr *expr)
{
    ASTExpr *L = nullptr;
    ASTExpr *R = nullptr;
    if (expr->operands.size() >= 2)
    {
        L = expr->operands[0]->accept(this);
        R = expr->operands[1]->accept(this);
    }

    switch (expr->operator_)
    {
    case operators::b_add:
    case operators::b_minus:
    case operators::b_mul:
    case operators::b_div:
    case operators::b_left_shift:
    case operators::b_right_shift:
    case operators::b_less:
    case operators::b_greater:
    case operators::b_less_eq:
    case operators::b_greater_eq:
    case operators::b_eq:
    case operators::b_neq:
    case operators::b_bitand:
    case operators::b_bitxor:
    case operators::b_bitor:
    case operators::b_and:
    case operators::b_or:
    {
        ASTConst *leftConst = check_const(L);
        ASTConst *rightConst = check_const(R);
        if (leftConst && rightConst)
        {
            return performOperation(leftConst, rightConst, expr->operator_);
        }
        expr->operands[0] = L;
        expr->operands[1] = R;
        return expr;
    }
    case operators::assign:
    {
        expr->operands[1] = expr->operands[1]->accept(this);

        ASTConst *rightConst = check_const(expr->operands[1]);
        if (rightConst)
        {
            if (auto idExpr = dynamic_cast<ASTIdExpr *>(expr->operands[0]))
            {
                constValues.back()[idExpr->name] = rightConst;
            }
            // constValues[static_cast<ASTIdExpr *>(expr->operands[0])->name] = rightConst;
        }

        return expr;
    }
    default:
        break;
    }
    return expr;
}

ASTConst *ConstPropagationOpt::visit(ASTConst *constant)
{
    return constant;
}

ASTExpr *ConstPropagationOpt::visit(ASTExprList *exprList)
{
    vector<ASTExpr *> newExprs;
    for (ASTExpr *expr : exprList->exprs)
    {
        ASTExpr *visitedExpr = expr->accept(this);
        newExprs.push_back(visitedExpr);
    }
    if (newExprs.size() == 1)
        return newExprs[0];
    exprList->exprs = newExprs;
    return exprList;
}

ASTIfStmt *ConstPropagationOpt::visit(ASTIfStmt *ifStmt)
{
    if (ifStmt->cond)
    {
        ASTExpr *optimizedCond = ifStmt->cond->accept(this);
        if (optimizedCond != ifStmt->cond)
        {
            ifStmt->cond = optimizedCond;
        }
    }
    if (ifStmt->stmt)
    {
        ASTStmt *optimizedStmt = ifStmt->stmt->accept(this);
        if (optimizedStmt != ifStmt->stmt)
        {
            ifStmt->stmt = optimizedStmt;
        }
    }

    return ifStmt;
}

ASTWhileStmt *ConstPropagationOpt::visit(ASTWhileStmt *whileStmt)
{
    if (whileStmt->cond)
    {
        ASTExpr *optimizedCond = whileStmt->cond->accept(this);
        if (optimizedCond != whileStmt->cond)
        {
            whileStmt->cond = optimizedCond;
        }
    }
    if (whileStmt->stmt)
    {
        ASTStmt *optimizedStmt = whileStmt->stmt->accept(this);
        if (optimizedStmt != whileStmt->stmt)
        {
            whileStmt->stmt = optimizedStmt;
        }
    }

    return whileStmt;
}