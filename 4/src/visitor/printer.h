//
// Created by satyam on 18/4/24.
//

#ifndef CCOMPILER_PRINTER_H
#define CCOMPILER_PRINTER_H


#include "visitor.h"
#include "expr.h"
#include "prog.h"

class Printer: Visitor {
public:

    // /////////////////////////////////////////////////////////////////////////////
    // ///////////////////////////////// EXPR //////////////////////////////////////
    // /////////////////////////////////////////////////////////////////////////////
    std::string visit(ASTExpr* expr, int indent){
      std::string result = common(expr, indent, expr->operands.size());
      for(auto& child: expr->operands){
        result += child->accept(this, indent+1);
      }
      result += end(indent);
      return result;
    }

    std::string visit(ASTExprList* exprList, int indent){
      std::string result = common(exprList, indent, exprList->exprs.size());
      for(auto& child: exprList->exprs){
        result += child->accept(this, indent+1);
      }
      result += end(indent);
      return result;
    }

    std::string visit(ASTConst *const_, int indent){
      return common(const_, indent, 0);
    }

    std::string visit(ASTIdExpr *expr, int indent){
      return common(expr, indent, 0);
    }

    std::string visit(ASTFunctionCall *fnCall, int indent){
      std::string result = common(fnCall, indent, 1);
      if(fnCall->params){
        result += fnCall->params->accept(this, indent+1);
        result += end(indent);
      }
      return result;
    }

    std::string visit(ASTIDDecl *idDecl, int indent){
      return common(idDecl, indent, 1);
    }

    // /////////////////////////////////////////////////////////////////////////////
    // ///////////////////////////////// DECL //////////////////////////////////////
    // /////////////////////////////////////////////////////////////////////////////

    std::string visit(ASTParamList* paramList, int indent){
      std::string result = common(paramList, indent, paramList->params.size());
      for(auto& child: paramList->params){
        result += child->accept(this, indent+1);
      }
      result += end(indent);
      return result;
    }


    std::string visit(ASTParamTypeList* paramList, int indent){
      std::string result;
      if(paramList){
        result += common(paramList, indent, 1);
        result += paramList->paramList->accept(this, indent+1);
        result += end(indent);
      }else{
        result += common(paramList, indent, 0);
      }
      return result;

    }

    std::string visit(ASTDeclSpec* declSpec, int indent){
      return common(declSpec, indent, 1);
    }

    std::string visit(ASTParamDecl* paramDecl, int indent){
      return common(paramDecl, indent, 0);
    }

    std::string visit(ASTFnDecl* fnDecl, int indent){
      std::string result;
      if(fnDecl->params){
        result += common(fnDecl, indent, 1);
        result += fnDecl->params->accept(this, indent + 1);
        result += end(indent);
      }else{
        result += common(fnDecl, indent, 0);
      }
      return result;
    }

    std::string visit(ASTProgram * prog, int indent=0) {
      std::string result = common(prog, indent, prog->extDecls.size());
      for(auto child: prog->extDecls){
        result += child->accept(this, indent+1);
      }
      result += end(indent);
      return result;
    }

    std::string visit(ASTInitDeclList *initDeclList, int indent){
      std::string result = common(initDeclList, indent, initDeclList->initializations.size());
      for(auto& child: initDeclList->initializations){
        result += child->accept(this, indent+1);
      }
      result += end(indent);
      return result;
    }

    std::string visit(ASTInitDecl* initDecl, int indent){
      std::string result;
      if(initDecl->fnDecl){
        result += common(initDecl, indent, 1);
        result += initDecl->fnDecl->accept(this, indent + 1);
        result += end(indent);
      }else{
        result += common(initDecl, indent, 0);
      }
      return result;
    }

    std::string visit(ASTFnDef *fnDef, int indent){
      std::string result = common(fnDef, indent, 3);
      result += fnDef->declSpec->accept(this, indent+1);
      result += fnDef->fnDecl->accept(this, indent+1);
      result += fnDef->body->accept(this, indent+1);
      result += end(indent);
      return result;
    }


    std::string visit(ASTGlobalVar *gv, int indent){
      std::string result = common(gv, indent, 1);
      result += gv->declaration->accept(this, indent+1);
      result += end(indent);
      return result;
    }

    std::string visit(ASTBlockList *bl, int indent){
      std::string result = common(bl, indent, bl->blocks.size());
      for(auto& child: bl->blocks){
        result += child->accept(this, indent+1);
      }
      result += end(indent);
      return result;
    }

    std::string visit(ASTBlock *block, int indent){
      std::string result = common(block, indent, 1);

      if(block->declaration != nullptr)
        result += block->declaration->accept(this, indent+1);
      if(block->stmt != nullptr)
        result += block->stmt->accept(this, indent+1);

      result += end(indent);
      return result;
    }

    std::string visit(ASTDeclList *declList, int indent){
      std::string result = common(declList, indent, declList->declarations.size());
      for(auto& child: declList->declarations){
        result += child->accept(this, indent+1);
      }
      result += end(indent);
      return result;
    }

    std::string visit(ASTDecl *decl, int indent){
      std::string result;
      if(decl->value){
        result += common(decl, indent, 1);
        result += decl->value->accept(this, indent + 1);
        result += end(indent);
      }else{
        result += common(decl, indent, 0);
      }
      return result;
    }

    // /////////////////////////////////////////////////////////////////////////////
    // ///////////////////////////////// STMT //////////////////////////////////////
    // /////////////////////////////////////////////////////////////////////////////

    std::string visit(ASTIfStmt *ifStmt, int indent){
      std::string result = common(ifStmt, indent, 2);
      result += ifStmt->cond->accept(this, indent+1);
      result += ifStmt->stmt->accept(this, indent+1);
      result += end(indent);
      return result;
    }

    std::string visit(ASTIfElseStmt *ifElseStmt, int indent){
      std::string result = common(ifElseStmt, indent, 3);
      result += ifElseStmt->cond->accept(this, indent+1);
      result += ifElseStmt->stmt->accept(this, indent+1);
      result += ifElseStmt->elseStmt->accept(this, indent+1);
      result += end(indent);
      return result;
    }

    std::string visit(ASTStmt* stmt, int indent){
      return common(stmt, indent, 0);
    }

    std::string visit(ASTExprStmt *exprStmt, int indent){
      std::string result = common(exprStmt, indent, 1);
      if(exprStmt->exprs != nullptr)
        result += exprStmt->exprs->accept(this, indent+1);
      result += end(indent);
      return result;
    }

    std::string visit(ASTRetJmpStmt *retJmpStmt, int indent){
      std::string result = common(retJmpStmt, indent, 1);
      if(retJmpStmt->expr != nullptr) {
        result += retJmpStmt->expr->accept(this, indent + 1);
        result += end(indent);
      }
      return result;
    }

    std::string visit(ASTWhileStmt *whileStmt, int indent){
      std::string result = common(whileStmt, indent, 2);
      result += whileStmt->cond->accept(this, indent+1);
      result += whileStmt->stmt->accept(this, indent+1);
      result += end(indent);
      return result;
    }

    std::string visit(ASTForStmt *forStmt, int indent){
      std::string result = common(forStmt, indent, 4);
      result += forStmt->expr1->accept(this, indent+1);
      result += forStmt->expr2->accept(this, indent+1);
      result += forStmt->expr3->accept(this, indent+1);
      result += forStmt->stmt->accept(this, indent+1);
      result += end(indent);
      return result;
    }

    std::string visit(ASTForStmt2 *forStmt2, int indent){
      std::string result = common(forStmt2, indent, 3);
      result += forStmt2->expr2->accept(this, indent+1);
      result += forStmt2->expr3->accept(this, indent+1);
      result += forStmt2->stmt->accept(this, indent+1);
      result += end(indent);
      return result;

    }

    std::string visit(ASTBreakJmpStmt *breakJmpStmt, int indent){
      return common(breakJmpStmt, indent, 0);
    }

    std::string visit(ASTContJmpStmt *contJmpStmt, int indent){
      return common(contJmpStmt, indent, 0);
    }

    std::string visit(ASTGotoLabeledStmt *gotoLabeledStmt, int indent){
      return common(gotoLabeledStmt, indent, 0);
    }

    std::string visit(ASTGotoJmpStmt *gotoJmpStmt, int indent){
      return common(gotoJmpStmt, indent, 0);
    }

    std::string visit(ASTPostIncrement *postIncrement, int indent){
      std::string result = common(postIncrement, indent, 1);
      result += postIncrement->expr->accept(this, indent+1);
      result += end(indent);
      return result;
    }

private:
    static std::string common(ASTNode* node, int indent, unsigned long numChildren){
      if(node == nullptr)
        return "";

      std::string result;
      for (int i = 0; i < indent; ++i) {
        result += "\t";
      }
      result += node->to_str();
      if(numChildren > 0){
        result += "[Children: " + std::to_string(numChildren) + "]  {" + "\n";
      }else{
        result += "\n";
      }
      return result;
    }

    static std::string end(int indent) {
      std::string result;
      for (int i = 0; i < indent; ++i) {
        result += "\t";
      }
      result += "}\n";
      return result;
    }
};


#endif //CCOMPILER_PRINTER_H
