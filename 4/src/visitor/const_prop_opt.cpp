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
    enterScope();
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
    exitScope();
    return bl;
}



ASTDecl *ConstPropagationOpt::visit(ASTDecl *Decl)
{
    if (Decl && Decl->value){
      ASTConst *constNode = check_const(Decl->value);
      if (constNode){
        if(constNode->ct == s_const)
          return Decl;

        if(is_compatible(constNode->ct, Decl->type)){
          llvm::errs() << "Type mismatch in declaration\n";
          assert(false);
        }
        if (!constValues.empty()){
          constValues.back()[Decl->name] = constNode;
        }
      }
      else{
        Decl->value = Decl->value->accept(this);
        constNode = check_const(Decl->value);
        if (constNode){
            if (!constValues.empty()){
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
    auto found = constValues.back().find(idExpr->name);
    if (found != constValues.back().end())
    {
        return new ASTConst(*(found->second));
    }
    return idExpr;
}



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

        if (leftConst && rightConst && leftConst->ct == rightConst->ct && leftConst->ct != s_const)
        {
            if(leftConst->ct == i_const)
                return performOperationI(leftConst, rightConst, expr->operator_);
            if(leftConst->ct == f_const)
                return performOperationF(leftConst, rightConst, expr->operator_);
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
        }

        return expr;
    }
    case operators::add_assign:
    case operators::sub_assign:
    case operators::mul_assign:
    case operators::div_assign:
    case operators::mod_assign:
    case operators::and_assign:
    case operators::or_assign:
    case operators::xor_assign:
    case operators::left_assign:
    case operators::right_assign:
    {
        auto idExpr = dynamic_cast<ASTIdExpr *>(expr->operands[0]);
        if (idExpr){
            if(constValues.back().find(idExpr->name) == constValues.back().end()){
                return expr;
            }
        }
        expr->operands[1] = expr->operands[1]->accept(this);

        ASTConst *rightConst = check_const(expr->operands[1]);
        if(!rightConst)
            return expr;
        
        operators o;
        switch (expr->operator_)
        {
            case operators::add_assign:
                o = b_add;
                break;
            case operators::sub_assign:
                o = b_minus;
                break;
            case operators::mul_assign:
                o = b_mul;
                break;
            case operators::div_assign:
                o = b_div;
                break;
            case operators::mod_assign:
                o = b_remainder;
                break;
            case operators::and_assign:
                o = b_and;
                break;
            case operators::or_assign:
                o = b_or;
                break;
            case operators::xor_assign:
                o = b_bitxor;
                break;
            case operators::left_assign:
                o = b_left_shift;
                break;
            case operators::right_assign:
                o = b_right_shift;
                break;
            default:
                assert(false);
                break;
        }
        auto leftConst = constValues.back()[idExpr->name];
        if (leftConst && rightConst && leftConst->ct == rightConst->ct && leftConst->ct != s_const)
        {
            if(leftConst->ct == i_const)
                return (new ASTExpr(assign, idExpr, performOperationI(leftConst, rightConst, o)))->accept(this);
            if(leftConst->ct == f_const)
                return (new ASTExpr(assign, idExpr, performOperationF(leftConst, rightConst, o)))->accept(this);
        }
        return expr;
    }

    case operators::u_op_plus_plus:
    case operators::u_op_minus_minus:
    default:
        return expr;

    
    return expr;
    }
}

ASTExpr *ConstPropagationOpt::visit(ASTPostIncrement* pi){
    if(constValues.back().find(pi->expr->name) != constValues.back().end()){
        auto c = constValues.back()[pi->expr->name];
        if(pi->is_inc)
            constValues.back()[pi->expr->name] = increase_by_1(c);
        else
            constValues.back()[pi->expr->name] = decrease_by_1(c);
        return c;
    }
    else{
        return pi;
    }
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

ASTFunctionCall *ConstPropagationOpt::visit(ASTFunctionCall* fn){
    if(!fn->params)
        return fn;
    auto newParams = fn->params->accept(this);
    // If ASTExpr instead of ASTExprList, create a nwe ASTExprList with one element.
    ASTExprList* newParams2;
    if(newParams2 = dynamic_cast<ASTExprList*>(newParams)){
        fn->params = newParams2;
    }else{
        newParams2 = new ASTExprList(newParams);
        fn->params = newParams2;
    }
    return fn;
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

ASTIfElseStmt *ConstPropagationOpt::visit(ASTIfElseStmt *ifElseStmt) {
    if (ifElseStmt->cond) {
        ifElseStmt->cond = ifElseStmt->cond->accept(this);
    }
    if (ifElseStmt->stmt) {
        ifElseStmt->stmt = ifElseStmt->stmt->accept(this);
    }
    if (ifElseStmt->elseStmt) {
        ifElseStmt->elseStmt = ifElseStmt->elseStmt->accept(this);
    }

    return ifElseStmt;
}

