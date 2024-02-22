#include "ast.hpp"

ASTExpr::ASTExpr(ASTAssignmentExpr *n) : ASTStmt() { this->add_child(n); }
ASTExpr::ASTExpr(ASTExpr *n1, ASTAssignmentExpr *n2) : ASTStmt()
{
    this->add_child(n1);
    this->add_child(n2);
}

ASTAssignmentExpr::ASTAssignmentExpr(ASTCondExpr *n) : ASTNode()
{
    this->add_child(n);
}
ASTAssignmentExpr::ASTAssignmentExpr(ASTUnaryExpr *n1, ASTAssignmentOp *n2,
                                     ASTAssignmentExpr *n3)
    : ASTNode()
{
    this->add_child(n1);
    this->add_child(n2);
    this->add_child(n3);
}

ASTInitializer::ASTInitializer(ASTInitializerList *n) : ASTNode()
{
    this->add_child(n);
}
ASTInitializer::ASTInitializer(ASTAssignmentExpr *n) : ASTNode()
{
    this->add_child(n);
}

ASTInitDecl::ASTInitDecl(ASTDirectDeclarator *n1, ASTInitializer *n2)
    : ASTNode()
{
    this->add_child(n1);
    this->add_child(n2);
}
ASTInitDecl::ASTInitDecl(ASTDirectDeclarator *n) : ASTNode()
{
    this->add_child(n);
}