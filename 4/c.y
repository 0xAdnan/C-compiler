%{
#include <cstdio>
#include <iostream>

#include "base.h"
#include "enums.h"
#include "decl.h"
#include "expr.h"
#include "prog.h"
#include "stmt.h"

using namespace std;

ASTNode* program_ast = NULL;

// stuff from flex that bison needs to know about:
extern "C" FILE *yyin;
extern "C" char yytext[];

extern "C" int yylex();
 
int yyparse();
void yyerror(const char *s);
void todo(int);
%}


%token	I_CONSTANT F_CONSTANT STRING_LITERAL FUNC_NAME SIZEOF
%token	PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token	AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token	SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token	XOR_ASSIGN OR_ASSIGN
%token	TYPEDEF_NAME ENUMERATION_CONSTANT

%token	TYPEDEF EXTERN STATIC AUTO REGISTER INLINE
%token	CONST RESTRICT VOLATILE
%token	BOOL CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token	COMPLEX IMAGINARY 
%token	STRUCT UNION ENUM ELLIPSIS

%token	CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token	ALIGNAS ALIGNOF ATOMIC GENERIC NORETURN STATIC_ASSERT THREAD_LOCAL

%start translation_unit

%code requires {
#include "base.h"
#include "enums.h"
#include "decl.h"
#include "expr.h"
#include "prog.h"
#include "stmt.h"
}

%union value {
  ASTPostExpr* postfix_expr;
  ASTArgExprList* arg_expr_l;
  ASTUnaryExpr* unary_expr;
  unary_op u_op;
  ASTExpr* expr;
  assignment_op ass_op;
  ASTExprList* expr_l;
  ASTDeclList* decl;
  ASTDeclSpec* decl_spec;
  ASTInitDeclList* init_decl_list;
  ASTInitDecl* init_decl;
  ctype_ type;
  ASTDirectDeclarator* d_declarator;
  ASTPtr* ptr;
  ASTParamList* param_list;
  ASTParamDecl* param_decl;
  ASTInitializer* init;
  ASTInitializerList* init_list;
  ASTDesignator* design;
  ASTDesignatorList* design_list;
  ASTStmt* stmt;
  ASTLabeledStmt* lab_stmt;
  ASTSelectStmt* sel_stmt;
  ASTIterStmt* iter_stmt;
  ASTJmpStmt* jmp_stmt;
  ASTBlockItemList* blk_ilist;
  ASTBlockItem* blk_i;
  ASTProgram* prog;
  ASTExternDecl* ext_decl;
  ASTFnDef* fn_def;
  ASTDeclList* decl_list;
  char* str;
}

%token <str> IDENTIFIER

%nterm <postfix_expr> postfix_expression
%nterm <arg_expr_l> argument_expression_list
%nterm <unary_expr> unary_expression
%nterm <u_op> unary_operator
%nterm <mul_expr> multiplicative_expression
%nterm <add_expr> additive_expression
%nterm <shift_expr> shift_expression
%nterm <rel_expr> relational_expression
%nterm <eq_expr> equality_expression
%nterm <and_expr> and_expression
%nterm <exor_expr> exclusive_or_expression
%nterm <inor_expr> inclusive_or_expression
%nterm <l_and_expr> logical_and_expression
%nterm <l_or_expr> logical_or_expression
%nterm <cond_expr> conditional_expression
%nterm <expr> assignment_expression
%nterm <ass_op> assignment_operator
%nterm <expr_l> expression
%nterm <cond_expr> constant_expression
%nterm <decl> declaration
%nterm <decl_spec> declaration_specifiers
%nterm <init_decl_list> init_declarator_list
%nterm <init_decl> init_declarator
%nterm <type> type_specifier
// %nterm <ast> specifier_qualifier_list
%nterm <d_declarator> declarator
%nterm <d_declarator> direct_declarator
%nterm <ptr> pointer
%nterm <param_list> parameter_type_list
%nterm <param_list> parameter_list
%nterm <param_decl> parameter_declaration
// %nterm <ast> type_name
// %nterm <ast> abstract_declarator
// %nterm <ast> direct_abstract_declarator
%nterm <init> initializer
%nterm <init_list> initializer_list
%nterm <stmt> statement
%nterm <lab_stmt> labeled_statement
%nterm <blk_ilist> compound_statement
%nterm <blk_ilist> block_item_list
%nterm <blk_i> block_item
%nterm <expr> expression_statement
%nterm <sel_stmt> selection_statement
%nterm <iter_stmt> iteration_statement
%nterm <jmp_stmt> jump_statement
%nterm <prog> translation_unit
%nterm <ext_decl> external_declaration
%nterm <fn_def> function_definition


%%

postfix_expression
    : IDENTIFIER                                                                     { $$ = new ASTIdExpr($1); }
	| I_CONSTANT		/* includes character_constant */                            { $$ = new ASTConst(i_const, yytext); }
	| F_CONSTANT                                                                     { $$ = new ASTConst(f_const, yytext); }
	| STRING_LITERAL                                                                 { $$ = new ASTConst(s_const, yytext); }
	| FUNC_NAME                                                                      { $$ = new ASTConst(s_const, yytext); }
	| '(' expression ')'                                                             { $$ = $2; }
	| postfix_expression '[' expression ']'                                          { $$ = new ASTArray($1, $3); }
	| postfix_expression '(' ')'                                                     { $$ = new ASTFunctionCall($1, new ASTArgExpList()); }
	| postfix_expression '(' argument_expression_list ')'                            { $$ = new ASTFunctionCall($1, $3); }
	| postfix_expression '.' IDENTIFIER                                              { todo(180); }
	| postfix_expression PTR_OP IDENTIFIER                                           { todo(181); }
	| postfix_expression INC_OP                                                      { $$ = new ASTPostIncrement($1, new ASTIncOp(plus_plus)); }
	| postfix_expression DEC_OP                                                      { $$ = new ASTPostIncrement($1, new ASTIncOp(minus_minus)); }
	;

argument_expression_list
	: assignment_expression                                                          { $$ = new ASTArgExprList($1); }
	| argument_expression_list ',' assignment_expression                             { $$ = new ASTArgExpList($1, $3); }
	;

unary_expression
	: postfix_expression                                                             { $$ = new ASTUnaryExpr($1); }
	| INC_OP unary_expression                                                        { $$ = new ASTUnaryExpr(plus_plus, $2); }
	| DEC_OP unary_expression                                                        { $$ = new ASTUnaryExpr(minus_minus, $2); }
	| unary_operator unary_expression                                                 { $$ = new ASTUnaryExpr($1, $2); }
	;

unary_operator
	: '&'                                                                            { $$ = u_op_and; }
	| '*'                                                                            { $$ = u_op_star; }
	| '+'                                                                            { $$ = u_op_plus; }
	| '-'                                                                            { $$ = u_op_minus; }
	| '~'                                                                            { $$ = u_op_tilde; }
	| '!'                                                                            { $$ = u_op_not; }
	;

multiplicative_expression
	: unary_expression                                                                { $$ = $1; }
	| multiplicative_expression '*' unary_expression                                  { $$ = new ASTBinaryExpr($1, b_mul, $3); }
	| multiplicative_expression '/' unary_expression                                  { $$ = new ASTBinaryExpr($1, b_div, $3); }
	| multiplicative_expression '%' unary_expression                                  { $$ = new ASTBinaryExpr($1, b_remainder, $3); }
	;

additive_expression
	: multiplicative_expression                                                      { $$ = $1; }
	| additive_expression '+' multiplicative_expression                              { $$ = new ASTBinaryExpr($1, b_add, $3); }
	| additive_expression '-' multiplicative_expression                              { $$ = new ASTBinaryExpr($1, b_minus, $3); }
	;

shift_expression
	: additive_expression                                                            { $$ = $1; }
	| shift_expression LEFT_OP additive_expression                                   { $$ = new ASTBinaryExpr($1, b_left_shift, $3); }
	| shift_expression RIGHT_OP additive_expression                                  { $$ = new ASTBinaryExpr($1, b_right_shift, $3); }
	;

relational_expression
	: shift_expression                                                               { $$ = $1; }
	| relational_expression '<' shift_expression                                     { $$ = new ASTBinaryExpr($1, b_less, $3); }
	| relational_expression '>' shift_expression                                     { $$ = new ASTBinaryExpr($1, b_greater, $3); }
	| relational_expression LE_OP shift_expression                                   { $$ = new ASTBinaryExpr($1, b_less_eq, $3); }
	| relational_expression GE_OP shift_expression                                   { $$ = new ASTBinaryExpr($1, b_greater_eq, $3); }
	;

equality_expression
	: relational_expression                                                          { $$ = $1; }
	| equality_expression EQ_OP relational_expression                                { $$ = new ASTBinaryExpr($1, b_eq, $3); }
	| equality_expression NE_OP relational_expression                                { $$ = new ASTBinaryExpr($1, b_neq, $3); }
	;

and_expression
	: equality_expression                                                            { $$ = $1; }
	| and_expression '&' equality_expression                                         { $$ = new ASTBinaryExpr($1, b_bitand, $3); }
	;

exclusive_or_expression
	: and_expression                                                                 { $$ = $1; }
	| exclusive_or_expression '^' and_expression                                     { $$ = new ASTBinaryExpr($1, b_xor, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression                                                        { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression                            { $$ = new ASTBinaryExpr($1, b_bitor, $3); }
	;

logical_and_expression
	: inclusive_or_expression                                                        { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression                          { $$ = new ASTBinaryExpr($1, b_and, $3); }
	;

logical_or_expression
	: logical_and_expression                                                         { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression                             { $$ = new ASTBinaryExpr($1, b_or, $3); }
	;

conditional_expression
	: logical_or_expression                                                          { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression                { $$ = new ASTCondExpr($1, $3, $5); }
	;

assignment_expression
	: conditional_expression                                                         { $$ = $1; }
	| unary_expression assignment_operator assignment_expression                     { $$ = new ASTAssignmentExpr($1, $2, $3);}
	;

assignment_operator
	: '='                                                                            { $$ = assign; }
	| MUL_ASSIGN                                                                     { $$ = mul_assign; }
	| DIV_ASSIGN                                                                     { $$ = div_assign; }
	| MOD_ASSIGN                                                                     { $$ = mod_assign; }
	| ADD_ASSIGN                                                                     { $$ = add_assign; }
	| SUB_ASSIGN                                                                     { $$ = sub_assign; }
	| LEFT_ASSIGN                                                                    { $$ = left_assign; }
	| RIGHT_ASSIGN                                                                   { $$ = right_assign; }
	| AND_ASSIGN                                                                     { $$ = and_assign; }
	| XOR_ASSIGN                                                                     { $$ = xor_assign; }
	| OR_ASSIGN                                                                      { $$ = or_assign; }
	;

expression
	: assignment_expression                                                          { $$ = new ASTExprList($1); }
	| expression ',' assignment_expression                                           { $$ = new ASTExprList($1, $3); }
	;

constant_expression
	: conditional_expression	/* with constraints */
	;

declaration
	: declaration_specifiers init_declarator_list ';'                                { $$ = new ASTDeclList($1, $2); }
	;

declaration_specifiers
	: type_specifier declaration_specifiers                                          { $$ = new ASTDeclSpec($1, $2); }
	| type_specifier                                                                 { $$ = new ASTDeclSpec($1); }
	| CONST declaration_specifiers                                                   { todo(316); }
	| CONST                                                                          { todo(317); }
	;

init_declarator_list
	: init_declarator                                                                { $$ = new ASTInitDeclList($1); }
	| init_declarator_list ',' init_declarator                                       { $$ = new ASTInitDeclList($1, $3); }
	;

init_declarator
	: declarator '=' initializer                                                     { $$ = new ASTInitDecl($1, $3); }
	| declarator                                                                     { $$ = new ASTInitDecl($1); }
	;

type_specifier
	: VOID                                                                           { $$ = t_void; }
	| CHAR                                                                           { $$ = t_char; }
	| SHORT                                                                          { $$ = t_short; }
	| INT                                                                            { $$ = t_int; }
	| FLOAT                                                                          { $$ = t_float; }
    | LONG                                                                           { $$ = t_long; }
	| DOUBLE                                                                         { $$ = t_double; }
	| SIGNED                                                                         { $$ = t_signed; }
	| UNSIGNED                                                                       { $$ = t_unsigned; }
	| BOOL                                                                           { $$ = t_bool; }
	| COMPLEX                                                                        { $$ = t_complex; }
	| IMAGINARY	  	/* non-mandated extension */                                     { $$ = t_imaginary; }
	| TYPEDEF_NAME		                                                             { todo(262); }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| CONST specifier_qualifier_list
	| CONST
	;

declarator
	: pointer direct_declarator                                                       { $$ = $2; $2->add_ptr($1); }
	| direct_declarator                                                               { $$ = $1;}
	;

direct_declarator
	: IDENTIFIER                                                                      { $$ = new ASTIdDeclarator(new ASTId($1)); }
	| direct_declarator '(' parameter_type_list ')'                                   { $$ = new ASTFnDecl($1, $3);}
	| direct_declarator '(' ')'                                                       { $$ = new ASTFnDecl($1);}
	;

pointer
	: '*' CONST pointer                                                               { todo(373); }
	| '*' CONST                                                                       { todo(374); }
	| '*' pointer                                                                     { $$ = new ASTPtr($2); }
	| '*'                                                                             { $$ = new ASTPtr(); }
	;

parameter_type_list
	: parameter_list ',' ELLIPSIS                                                      { $$ = $1; $1->is_variadic = true; }
	| parameter_list                                                                   { $$ = $1; }
	;

parameter_list
	: parameter_declaration                                                            { $$ = new ASTParamList($1); }
	| parameter_list ',' parameter_declaration                                         { $$ = new ASTParamList($1, $3); }
	;

parameter_declaration
	: declaration_specifiers declarator                                                { $$ = new ASTParamDecl($1, $2); }
	| declaration_specifiers                                                           { $$ = new ASTParamDecl($1); }
	;

initializer
	: assignment_expression                                                           { $$ = new ASTInitializer($1); }
	;

initializer_list
	: initializer                                                                       { $$ = new ASTInitializerList($1); }
	| initializer_list ',' initializer                                                  { $$ = new ASTInitializerList($1, $3); }
	;

statement
	: labeled_statement                                                                 { $$ = $1; }
	| compound_statement                                                                { $$ = $1; }
	| expression_statement                                                              { $$ = $1; }
	| selection_statement                                                               { $$ = $1; }
	| iteration_statement                                                               { $$ = $1; }
	| jump_statement                                                                    { $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement                                                          { $$ = new ASTGotoLabeledStmt(new ASTId($1), $3); }
	| CASE constant_expression ':' statement                                            { $$ = new ASTCaseLabeledStmt($2, $4); }
	| DEFAULT ':' statement                                                             { $$ = new ASTDefLabeledStmt($3); } 
	;

compound_statement
	: '{' '}'                                                                           { $$ = new ASTBlockItemList(); }
	| '{'  block_item_list '}'                                                          { $$ = $2; }
	;

block_item_list
	: block_item                                                                        { $$ = new ASTBlockItemList($1); }
	| block_item_list block_item                                                        { $$ = new ASTBlockItemList($1, $2); }
	;

block_item
	: declaration                                                                       { $$ = new ASTBlockItem($1); }
	| statement                                                                         { $$ = new ASTBlockItem($1); }
	;

expression_statement
	: ';'                                                                               { $$ = NULL; }
	| expression ';'                                                                    { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement ELSE statement                                    { $$ = new ASTIfElseSelectStmt($3, $5, $7); }
	| IF '(' expression ')' statement                                                   { $$ = new ASTIfSelectStmt($3, $5); }
	| SWITCH '(' expression ')' statement                                               { $$ = new ASTSwitchStmt($3, $5); }
	;

iteration_statement
	: WHILE '(' expression ')' statement                                                { $$ = new ASTWhileStmt($3, $5); }
	| DO statement WHILE '(' expression ')' ';'                                         { $$ = new ASTDoWhileStmt($2, $5); }
	| FOR '(' expression_statement expression_statement ')' statement                   { $$ = new ASTForStmt($3, $4, $6); }
	| FOR '(' expression_statement expression_statement expression ')' statement        { $$ = new ASTForStmt($3, $4, $5, $7); }
	| FOR '(' declaration expression_statement ')' statement                            { $$ = new ASTForStmt($3, $4, $6); }
	| FOR '(' declaration expression_statement expression ')' statement                 { $$ = new ASTForStmt($3, $4, $5, $7); }
	;

jump_statement
  : GOTO IDENTIFIER ';'                                                               { $$ = new ASTGotoJmpStmt(new ASTId($2)); }
	| CONTINUE ';'                                                                      { $$ = new ASTContJmpStmt(); }
  | BREAK ';'                                                                         { $$ = new ASTBreakJmpStmt(); }
	| RETURN ';'                                                                        { $$ = new ASTRetJmpStmt(); }
	| RETURN expression ';'                                                             { $$ = new ASTRetJmpStmt($2); }
	;

translation_unit
	: external_declaration
	{
		$$ = new ASTProgram($1);
		program_ast = $$;
	}
	| translation_unit external_declaration
	{
		$$ = new ASTProgram($1, $2);
		program_ast = $$;
	}
	;

external_declaration
	: function_definition                                                               { $$ = new ASTExternDecl($1); }
	| declaration                                                                       { $$ = new ASTExternDecl($1); }
	;

function_definition
	: declaration_specifiers declarator compound_statement                              { $$ = new ASTFnDef($1, $2, $3); }
	;


%%
#include <stdio.h>

void yyerror(const char *s)
{
	fflush(stdout);
	fprintf(stderr, "*** %s\n", s);
}

void todo(int rule_no){
  char *msg;
  int formatterStrResult = asprintf(&msg, "Rule no. %d Not Supported Yet\n", rule_no);
  yyerror(msg);
  free(msg);
}
