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


%token	SIZEOF
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
  ASTExpr* expr;
  operators op;
  ASTExprList* expr_l;

  ASTDeclList* decl;
  ASTDeclSpec* decl_spec;
  ASTInitDeclList* init_decl_list;
  ASTInitDecl* init_decl;
  ctype_ type;
  ASTDeclarator* d_declarator;
  int ptr;
  ASTParamDecl* param_decl;
  ASTParamList* param_list;
  ASTParamTypeList* param_type_list;

  ASTStmt* stmt;
  ASTLabeledStmt* lab_stmt;
  ASTSelectStmt* sel_stmt;
  ASTIterStmt* iter_stmt;
  ASTJmpStmt* jmp_stmt;
  ASTExprStmt* expr_stmt;
  ASTBlockList* blk_ilist;
  ASTBlock* blk_i;

  ASTProgram* prog;
  ASTExternDecl* ext_decl;
  ASTFnDef* fn_def;
  ASTDeclList* decl_list;
  char* str;
}

%token <str> IDENTIFIER
%token <str> I_CONSTANT
%token <str> F_CONSTANT
%token <str> STRING_LITERAL
%token <str> FUNC_NAME

%nterm <expr> postfix_expression
%nterm <expr> unary_expression
%nterm <op> unary_operator
%nterm <expr> multiplicative_expression
%nterm <expr> additive_expression
%nterm <expr> shift_expression
%nterm <expr> relational_expression
%nterm <expr> equality_expression
%nterm <expr> and_expression
%nterm <expr> exclusive_or_expression
%nterm <expr> inclusive_or_expression
%nterm <expr> logical_and_expression
%nterm <expr> logical_or_expression
%nterm <expr> conditional_expression
%nterm <expr> assignment_expression
%nterm <op> assignment_operator

%nterm <expr_l> expression
%nterm <decl> declaration
%nterm <decl_spec> declaration_specifiers
%nterm <init_decl_list> init_declarator_list
%nterm <init_decl> init_declarator
%nterm <type> type_specifier
// %nterm <ast> specifier_qualifier_list
%nterm <d_declarator> declarator
%nterm <d_declarator> direct_declarator
%nterm <ptr> pointer
%nterm <param_type_list> parameter_type_list
%nterm <param_list> parameter_list
%nterm <param_decl> parameter_declaration
// %nterm <ast> type_name
// %nterm <ast> abstract_declarator
// %nterm <ast> direct_abstract_declarator
%nterm <stmt> statement
%nterm <lab_stmt> labeled_statement
%nterm <blk_ilist> compound_statement
%nterm <blk_ilist> block_item_list
%nterm <blk_i> block_item
%nterm <expr_stmt> expression_statement
%nterm <sel_stmt> selection_statement
%nterm <iter_stmt> iteration_statement
%nterm <jmp_stmt> jump_statement
%nterm <prog> translation_unit
%nterm <ext_decl> external_declaration
%nterm <fn_def> function_definition


%%

postfix_expression
    : IDENTIFIER                                                                     { $$ = new ASTIdExpr($1); }
	| I_CONSTANT		/* includes character_constant */                            { $$ = new ASTConst(i_const, $1); }
	| F_CONSTANT                                                                     { $$ = new ASTConst(f_const, $1); }
	| STRING_LITERAL                                                                 { $$ = new ASTConst(s_const, $1); }
	| FUNC_NAME                                                                      { $$ = new ASTConst(s_const, $1); }
	| '(' expression ')'                                                             { $$ = $2; }
	| postfix_expression '[' expression ']'                                          { $$ = new ASTArrayAccess($1, $3); }
	| postfix_expression '(' ')'                                                     { $$ = new ASTFunctionCall($1); }
	| postfix_expression '(' expression ')'                                          { $$ = new ASTFunctionCall($1, $3); }
	| postfix_expression INC_OP                                                      { $$ = new ASTPostIncrement($1, true); }
	| postfix_expression DEC_OP                                                      { $$ = new ASTPostIncrement($1, false); }
	;

unary_expression
	: postfix_expression                                                             { $$ = $1; }
	| INC_OP unary_expression                                                        { $$ = new ASTExpr(u_op_plus_plus, $2); }
	| DEC_OP unary_expression                                                        { $$ = new ASTExpr(u_op_minus_minus, $2); }
	| unary_operator unary_expression                                                { $$ = new ASTExpr($1, $2); }
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
	| multiplicative_expression '*' unary_expression                                  { $$ = new ASTExpr(b_mul, $1, $3); }
	| multiplicative_expression '/' unary_expression                                  { $$ = new ASTExpr(b_div, $1, $3); }
	| multiplicative_expression '%' unary_expression                                  { $$ = new ASTExpr(b_remainder, $1, $3); }
	;

additive_expression
	: multiplicative_expression                                                      { $$ = $1; }
	| additive_expression '+' multiplicative_expression                              { $$ = new ASTExpr(b_add, $1, $3); }
	| additive_expression '-' multiplicative_expression                              { $$ = new ASTExpr(b_minus, $1, $3); }
	;

shift_expression
	: additive_expression                                                            { $$ = $1; }
	| shift_expression LEFT_OP additive_expression                                   { $$ = new ASTExpr(b_left_shift, $1, $3); }
	| shift_expression RIGHT_OP additive_expression                                  { $$ = new ASTExpr(b_right_shift, $1, $3); }
	;

relational_expression
	: shift_expression                                                               { $$ = $1; }
	| relational_expression '<' shift_expression                                     { $$ = new ASTExpr(b_less, $1, $3); }
	| relational_expression '>' shift_expression                                     { $$ = new ASTExpr(b_greater, $1, $3); }
	| relational_expression LE_OP shift_expression                                   { $$ = new ASTExpr(b_less_eq, $1, $3); }
	| relational_expression GE_OP shift_expression                                   { $$ = new ASTExpr(b_greater_eq, $1, $3); }
	;

equality_expression
	: relational_expression                                                          { $$ = $1; }
	| equality_expression EQ_OP relational_expression                                { $$ = new ASTExpr(b_eq, $1, $3); }
	| equality_expression NE_OP relational_expression                                { $$ = new ASTExpr(b_neq, $1, $3); }
	;

and_expression
	: equality_expression                                                            { $$ = $1; }
	| and_expression '&' equality_expression                                         { $$ = new ASTExpr(b_bitand, $1, $3); }
	;

exclusive_or_expression
	: and_expression                                                                 { $$ = $1; }
	| exclusive_or_expression '^' and_expression                                     { $$ = new ASTExpr(b_bitxor, $1,  $3); }
	;

inclusive_or_expression
	: exclusive_or_expression                                                        { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression                            { $$ = new ASTExpr(b_bitor, $1, $3); }
	;

logical_and_expression
	: inclusive_or_expression                                                        { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression                          { $$ = new ASTExpr(b_and, $1, $3); }
	;

logical_or_expression
	: logical_and_expression                                                         { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression                             { $$ = new ASTExpr(b_or, $1, $3); }
	;

conditional_expression
	: logical_or_expression                                                          { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression                { $$ = new ASTExpr(t_cond, $1, $3, $5); }
	;

assignment_expression
	: conditional_expression                                                         { $$ = $1; }
	| unary_expression assignment_operator assignment_expression                     { $$ = new ASTExpr($2, $1, $3);}
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

declaration
	: declaration_specifiers init_declarator_list ';'                                { $$ = new ASTDeclList($1, $2); }
	;

declaration_specifiers
	: type_specifier CONST                                                           { $$ = new ASTDeclSpec($1); $$->is_const=true; }
	| type_specifier                                                                 { $$ = new ASTDeclSpec($1); }
	| CONST type_specifier                                                           { $$ = new ASTDeclSpec($2); $$->is_const=true; }
	;

init_declarator_list
	: init_declarator                                                                { $$ = new ASTInitDeclList($1); }
	| init_declarator_list ',' init_declarator                                       { $$ = new ASTInitDeclList($1, $3); }
	;

init_declarator
	: declarator '=' assignment_expression {
	    ASTIDDecl* id = dynamic_cast<ASTIDDecl*>($1);
	    assert(id != nullptr);
	    $$ = new ASTInitDecl(id, $3);
	}
	| declarator {
	    ASTIDDecl* id = dynamic_cast<ASTIDDecl*>($1);
	    if(id != nullptr)
    	    $$ = new ASTInitDecl(id);
    	else{
    	    ASTFnDecl* fn = dynamic_cast<ASTFnDecl*>($1);
	        assert(fn != nullptr);
    	    $$ = new ASTInitDecl(fn);
    	}
	}
	;

type_specifier
	: VOID                                                                           { $$ = t_void; }
	| CHAR                                                                           { $$ = t_char; }
	| SHORT                                                                          { $$ = t_short; }
	| INT                                                                            { $$ = t_int; }
	| FLOAT                                                                          { $$ = t_float; }
    | LONG                                                                           { $$ = t_long; }
    | LONG ' ' LONG                                                                  { $$ = t_long_long; }
	| DOUBLE                                                                         { $$ = t_double; }
	| SIGNED                                                                         { $$ = t_signed; }
	| UNSIGNED                                                                       { $$ = t_unsigned; }
	| BOOL                                                                           { $$ = t_bool; }
	| COMPLEX                                                                        { $$ = t_complex; }
	| IMAGINARY	  	/* non-mandated extension */                                     { $$ = t_imaginary; }
	| TYPEDEF_NAME		                                                             { todo(262); }
	;

declarator
	: pointer direct_declarator                                                       { $$ = $2; $2->num_ptrs = $1; }
	| direct_declarator                                                               { $$ = $1;}
	;

direct_declarator
	: IDENTIFIER                                                                      { $$ = new ASTIDDecl($1); }
	| direct_declarator '(' parameter_type_list ')' {
	    ASTIDDecl* id = dynamic_cast<ASTIDDecl*>($1);
	    assert(id != nullptr);

	    $$ = new ASTFnDecl(id, $3);
	}
	| direct_declarator '(' ')' {
	    ASTIDDecl* id = dynamic_cast<ASTIDDecl*>($1);
	    assert(id != nullptr);

	    $$ = new ASTFnDecl(id);
	}
	;

pointer
	: '*' pointer                                                                     { $$ = $2 + 1; }
	| '*'                                                                             { $$ = 1; }
	;

parameter_type_list
	: parameter_list ',' ELLIPSIS                                                      { $$ = new ASTParamTypeList($1); $$->is_variadic = true; }
	| parameter_list                                                                   { $$ = new ASTParamTypeList($1); }
	;

parameter_list
	: parameter_declaration                                                            { $$ = new ASTParamList($1); }
	| parameter_list ',' parameter_declaration                                         { $$ = new ASTParamList($1, $3); }
	;

parameter_declaration
	: declaration_specifiers declarator {
	    ASTIDDecl* id = dynamic_cast<ASTIDDecl*>($2);
	    assert(id != nullptr);
	    $$ = new ASTParamDecl($1, id);
	}
	| declaration_specifiers                                                           { $$ = new ASTParamDecl($1); }
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
	: IDENTIFIER ':' statement                                                          { $$ = new ASTGotoLabeledStmt($1, $3); }
	| CASE conditional_expression ':' statement                                         { $$ = new ASTCaseLabeledStmt($2, $4); }
	| DEFAULT ':' statement                                                             { $$ = new ASTDefLabeledStmt($3); } 
	;

compound_statement
	: '{' '}'                                                                           { $$ = new ASTBlockList(); }
	| '{'  block_item_list '}'                                                          { $$ = $2; }
	;

block_item_list
	: block_item                                                                        { $$ = new ASTBlockList($1); }
	| block_item_list block_item                                                        { $$ = new ASTBlockList($1, $2); }
	;

block_item
	: declaration                                                                       { $$ = new ASTBlock($1); }
	| statement                                                                         { $$ = new ASTBlock($1); }
	;

expression_statement
	: ';'                                                                               { $$ = new ASTExprStmt(); }
	| expression ';'                                                                    { $$ = new ASTExprStmt($1); }
	;

selection_statement
	: IF '(' expression ')' statement ELSE statement
	{
	    ASTExprList* exprs = dynamic_cast<ASTExprList*>($3);
	    assert(exprs != nullptr);
	    assert(exprs->exprs.size() == 1);

	    $$ = new ASTIfElseStmt(exprs->exprs[0], $5, $7);

	}
	| IF '(' expression ')' statement
	{
	    ASTExprList* exprs = dynamic_cast<ASTExprList*>($3);
	    assert(exprs != nullptr);
	    assert(exprs->exprs.size() == 1);

	    $$ = new ASTIfStmt(exprs->exprs[0], $5);
	}
	| SWITCH '(' expression ')' statement
	{
	    ASTExprList* exprs = dynamic_cast<ASTExprList*>($3);
	    assert(exprs != nullptr);
	    assert(exprs->exprs.size() == 1);

	    $$ = new ASTSwitchStmt(exprs->exprs[0], $5);
	}
	;

iteration_statement
	: WHILE '(' expression ')' statement                                                { $$ = new ASTWhileStmt($3, $5); }
	| DO statement WHILE '(' expression ')' ';'                                         { $$ = new ASTDoWhileStmt($5, $2); }
	| FOR '(' expression_statement expression_statement ')' statement                   { $$ = new ASTForStmt($3, $4, $6); }
	| FOR '(' expression_statement expression_statement expression ')' statement        { $$ = new ASTForStmt($3, $4, $5, $7); }
	| FOR '(' declaration expression_statement ')' statement                            { $$ = new ASTForStmt2($3, $4, $6); }
	| FOR '(' declaration expression_statement expression ')' statement                 { $$ = new ASTForStmt2($3, $4, $5, $7); }
	;

jump_statement
  : GOTO IDENTIFIER ';'                                                                 { $$ = new ASTGotoJmpStmt($2); }
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
	: function_definition                                                               { $$ = $1; }
	| declaration                                                                       { $$ = new ASTGlobalVar($1); }
	;

function_definition
	: declaration_specifiers declarator compound_statement {
	    ASTFnDecl* fn = dynamic_cast<ASTFnDecl*>($2);
	    assert(fn != nullptr);

	    $$ = new ASTFnDef($1, fn, $3);
	}
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
