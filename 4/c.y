%{
#include <cstdio>
#include <iostream>

#include "ast.hpp"
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
#include "ast.hpp"
}

%union value {
  ASTPrimaryExpr* p_expr;
  ASTConst* constant;
  ASTStrConst* str_const;
  ASTPostExpr* postfix_expr;
  ASTArgExpList* arg_expr_l;
  ASTUnaryExpr* unary_expr;
  ASTUnaryOp* unary_op;
  ASTMulExpr* mul_expr;
  ASTAddExpr* add_expr;
  ASTShiftExpr* shift_expr;
  ASTRelExpr* rel_expr;
  ASTEqExpr* eq_expr;
  ASTAndExpr* and_expr;
  ASTExclusiveOrExpr* exor_expr;
  ASTInclusiveOrExpr* inor_expr;
  ASTLogicalAndExpr* l_and_expr;
  ASTLogicalOrExpr* l_or_expr;
  ASTCondExpr* cond_expr;
  ASTAssignmentExpr* ass_expr;
  ASTAssignmentOp* ass_op;
  ASTExpr* expr;
  ASTDecl* decl;
  ASTDeclSpec* decl_spec;
  ASTInitDeclList* init_decl_list;
  ASTInitDecl* init_decl;
  ASTType* type;
  ASTDirectDeclarator* d_declarator;
  ASTPtr* ptr;
  ASTParamList* param_list;
  ASTParamDecl* param_decl;
  ASTIdList* id_list;
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

%nterm <p_expr> primary_expression
%nterm <constant> constant
%nterm <str_const> string
%nterm <postfix_expr> postfix_expression
%nterm <arg_expr_l> argument_expression_list
%nterm <unary_expr> unary_expression
%nterm <unary_op> unary_operator
%nterm <unary_expr> cast_expression
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
%nterm <ass_expr> assignment_expression
%nterm <ass_op> assignment_operator
%nterm <expr> expression
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
%nterm <id_list> identifier_list
// %nterm <ast> type_name
// %nterm <ast> abstract_declarator
// %nterm <ast> direct_abstract_declarator
%nterm <init> initializer
%nterm <init_list> initializer_list
%nterm <design_list> designation
%nterm <design_list> designator_list
%nterm <design> designator
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
%nterm <decl_list> declaration_list


%%

primary_expression
	: IDENTIFIER                                                                     { $$ = new ASTPrimaryExpr(new ASTId($1)); }
	| constant                                                                       { $$ = new ASTPrimaryExpr($1); }
	| string                                                                         { $$ = new ASTPrimaryExpr($1); }
	| '(' expression ')'                                                             { $$ = new ASTPrimaryExpr($2); }
	;

constant
	: I_CONSTANT		/* includes character_constant */                                { $$ = new ASTConst(i_const, yytext); }
	| F_CONSTANT                                                                     { $$ = new ASTConst(f_const, yytext); }
	;

string
	: STRING_LITERAL                                                                 { $$ = new ASTStrLiteralConst(); }
	| FUNC_NAME                                                                      { $$ = new ASTFuncNameConst(); }
	;

postfix_expression
	: primary_expression                                                             { $$ = new ASTPostExpr($1); }
	| postfix_expression '[' expression ']'                                          { $$ = new ASTPostExpr($1, $3); }
	| postfix_expression '(' ')'                                                     { $$ = new ASTPostExpr($1); }
	| postfix_expression '(' argument_expression_list ')'                            { $$ = new ASTPostExpr($1, $3); }
	| postfix_expression '.' IDENTIFIER                                              { $$ = new ASTPostExpr($1, new ASTPtrOp(dot_op), new ASTId($3)); }
	| postfix_expression PTR_OP IDENTIFIER                                           { $$ = new ASTPostExpr($1, new ASTPtrOp(ptr_op), new ASTId($3)); }
	| postfix_expression INC_OP                                                      { $$ = new ASTPostExpr($1, new ASTIncOp(plus_plus)); }
	| postfix_expression DEC_OP                                                      { $$ = new ASTPostExpr($1, new ASTIncOp(minus_minus)); }
	| '(' type_name ')' '{' initializer_list '}'                                     { todo(84); }
	| '(' type_name ')' '{' initializer_list ',' '}'                                 { todo(85); }
	;

argument_expression_list
	: assignment_expression                                                          { $$ = new ASTArgExpList($1); }
	| argument_expression_list ',' assignment_expression                             { $$ = new ASTArgExpList($1, $3); }
	;

unary_expression
	: postfix_expression                                                             { $$ = new ASTUnaryExpr($1); }
	| INC_OP unary_expression                                                        { $$ = new ASTUnaryExpr(new ASTIncOp(plus_plus), $2); }
	| DEC_OP unary_expression                                                        { $$ = new ASTUnaryExpr(new ASTIncOp(minus_minus), $2); }
	| unary_operator cast_expression                                                 { $$ = new ASTUnaryExpr($1, $2); }
	| SIZEOF unary_expression                                                        { todo(98); }
	| SIZEOF '(' type_name ')'                                                       { todo(99); }
	| ALIGNOF '(' type_name ')'                                                      { todo(100); }
	;

unary_operator
	: '&'                                                                            { $$ = new ASTUnaryOp(u_op_and); }
	| '*'                                                                            { $$ = new ASTUnaryOp(u_op_star); }
	| '+'                                                                            { $$ = new ASTUnaryOp(u_op_plus); }
	| '-'                                                                            { $$ = new ASTUnaryOp(u_op_minus); }
	| '~'                                                                            { $$ = new ASTUnaryOp(u_op_tilde); }
	| '!'                                                                            { $$ = new ASTUnaryOp(u_op_not); }
	;

cast_expression
	: unary_expression                                                               { $$ = $1; }
	| '(' type_name ')' cast_expression                                              { todo(160); }
	;

multiplicative_expression
	: cast_expression                                                                { $$ = new ASTMulExpr($1); }
	| multiplicative_expression '*' cast_expression                                  { $$ = new ASTMulExpr($1, new ASTArithOp(mul_op), $3); }
	| multiplicative_expression '/' cast_expression                                  { $$ = new ASTMulExpr($1, new ASTArithOp(div_op), $3); } 
	| multiplicative_expression '%' cast_expression                                  { $$ = new ASTMulExpr($1, new ASTArithOp(remainder_op), $3); }
	;

additive_expression
	: multiplicative_expression                                                      { $$ = new ASTAddExpr($1); }
	| additive_expression '+' multiplicative_expression                              { $$ = new ASTAddExpr($1, new ASTArithOp(add_op), $3); }
	| additive_expression '-' multiplicative_expression                              { $$ = new ASTAddExpr($1, new ASTArithOp(minus_op), $3); }
	;

shift_expression
	: additive_expression                                                            { $$ = new ASTShiftExpr($1); }
	| shift_expression LEFT_OP additive_expression                                   { $$ = new ASTShiftExpr($1, new ASTShiftOp(left_shift_op), $3); }
	| shift_expression RIGHT_OP additive_expression                                  { $$ = new ASTShiftExpr($1, new ASTShiftOp(right_shift_op), $3); }
	;

relational_expression
	: shift_expression                                                               { $$ = new ASTRelExpr($1); }
	| relational_expression '<' shift_expression                                     { $$ = new ASTRelExpr($1, new ASTRelOp(less_op), $3); }
	| relational_expression '>' shift_expression                                     { $$ = new ASTRelExpr($1, new ASTRelOp(greater_op), $3); }
	| relational_expression LE_OP shift_expression                                   { $$ = new ASTRelExpr($1, new ASTRelOp(less_eq), $3); }
	| relational_expression GE_OP shift_expression                                   { $$ = new ASTRelExpr($1, new ASTRelOp(greater_eq), $3); }
	;

equality_expression
	: relational_expression                                                          { $$ = new ASTEqExpr($1); }
	| equality_expression EQ_OP relational_expression                                { $$ = new ASTEqExpr($1, new ASTEqOp(eq_op), $3); }
	| equality_expression NE_OP relational_expression                                { $$ = new ASTEqExpr($1, new ASTEqOp(neq_op), $3); }
	;

and_expression
	: equality_expression                                                            { $$ = new ASTAndExpr($1); }
	| and_expression '&' equality_expression                                         { $$ = new ASTAndExpr($1, $3); }
	;

exclusive_or_expression
	: and_expression                                                                 { $$ = new ASTExclusiveOrExpr($1); }
	| exclusive_or_expression '^' and_expression                                     { $$ = new ASTExclusiveOrExpr($1, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression                                                        { $$ = new ASTInclusiveOrExpr($1); }
	| inclusive_or_expression '|' exclusive_or_expression                            { $$ = new ASTInclusiveOrExpr($1, $3); }
	;

logical_and_expression
	: inclusive_or_expression                                                        { $$ = new ASTLogicalAndExpr($1); }
	| logical_and_expression AND_OP inclusive_or_expression                          { $$ = new ASTLogicalAndExpr($1, $3); }
	;

logical_or_expression
	: logical_and_expression                                                         { $$ = new ASTLogicalOrExpr($1); }
	| logical_or_expression OR_OP logical_and_expression                             { $$ = new ASTLogicalOrExpr($1, $3); }
	;

conditional_expression
	: logical_or_expression                                                          { $$ = new ASTCondExpr($1); }
	| logical_or_expression '?' expression ':' conditional_expression                { $$ = new ASTCondExpr($1, $3, $5); }
	;

assignment_expression
	: conditional_expression                                                         { $$ = new ASTAssignmentExpr($1); }
	| unary_expression assignment_operator assignment_expression                     { $$ = new ASTAssignmentExpr($1, $2, $3);}
	;

assignment_operator
	: '='                                                                            { $$ = new ASTAssignmentOp(assign); }
	| MUL_ASSIGN                                                                     { $$ = new ASTAssignmentOp(mul_assign); }
	| DIV_ASSIGN                                                                     { $$ = new ASTAssignmentOp(div_assign); }
	| MOD_ASSIGN                                                                     { $$ = new ASTAssignmentOp(mod_assign); }
	| ADD_ASSIGN                                                                     { $$ = new ASTAssignmentOp(add_assign); }
	| SUB_ASSIGN                                                                     { $$ = new ASTAssignmentOp(sub_assign); }
	| LEFT_ASSIGN                                                                    { $$ = new ASTAssignmentOp(left_assign); }
	| RIGHT_ASSIGN                                                                   { $$ = new ASTAssignmentOp(right_assign); }
	| AND_ASSIGN                                                                     { $$ = new ASTAssignmentOp(and_assign); }
	| XOR_ASSIGN                                                                     { $$ = new ASTAssignmentOp(xor_assign); }
	| OR_ASSIGN                                                                      { $$ = new ASTAssignmentOp(or_assign); }
	;

expression
	: assignment_expression                                                          { $$ = new ASTExpr($1); }
	| expression ',' assignment_expression                                           { $$ = new ASTExpr($1, $3); }
	;

constant_expression
	: conditional_expression	/* with constraints */
	;

declaration
	: declaration_specifiers ';'                                                     { $$ = new ASTDecl($1); }
	| declaration_specifiers init_declarator_list ';'                                { $$ = new ASTDecl($1, $2); }
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
	: VOID                                                                           { $$ = new ASTType(t_void); }
	| CHAR                                                                           { $$ = new ASTType(t_char); }
	| SHORT                                                                          { $$ = new ASTType(t_short); }
	| INT                                                                            { $$ = new ASTType(t_int); }
	| FLOAT                                                                          { $$ = new ASTType(t_float); }
  | LONG                                                                           { $$ = new ASTType(t_long); }
	| DOUBLE                                                                         { $$ = new ASTType(t_double); }
	| SIGNED                                                                         { $$ = new ASTType(t_signed); }
	| UNSIGNED                                                                       { $$ = new ASTType(t_unsigned); }
	| BOOL                                                                           { $$ = new ASTType(t_bool); }
	| COMPLEX                                                                        { $$ = new ASTType(t_complex); }
	| IMAGINARY	  	/* non-mandated extension */                                     { $$ = new ASTType(t_imaginary); }
	| TYPEDEF_NAME		                                                               { todo(262); }
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
	| '(' declarator ')'                                                              { $$ = $2; }
	| direct_declarator '[' ']'                                                       { todo(352); }
	| direct_declarator '[' '*' ']'                                                   { todo(353); }
	| direct_declarator '[' CONST '*' ']'                                             { todo(363); }
	| direct_declarator '[' CONST assignment_expression ']'                           { todo(364); }
	| direct_declarator '[' CONST ']'                                                 { todo(364); }
	| direct_declarator '[' assignment_expression ']'                                 { todo(360); }
	| direct_declarator '(' parameter_type_list ')'                                   { $$ = new ASTFnDeclarator($1, $3);}
	| direct_declarator '(' ')'                                                       { $$ = new ASTFnDeclarator($1);}
	| direct_declarator '(' identifier_list ')'                                       { $$ = new ASTFnCallDeclarator($1, $3);}
	;

pointer
	: '*' CONST pointer                                                               { todo(373); }
	| '*' CONST                                                                       { todo(374); }
	| '*' pointer                                                                     { $$ = new ASTPtr($2); }
	| '*'                                                                             { $$ = new ASTPtr(); }
	;

parameter_type_list
	: parameter_list ',' ELLIPSIS                                                      { todo(285); }
	| parameter_list                                                                   { $$ = $1; }
	;

parameter_list
	: parameter_declaration                                                            { $$ = new ASTParamList($1); }
	| parameter_list ',' parameter_declaration                                         { $$ = new ASTParamList($1, $3); }
	;

parameter_declaration
	: declaration_specifiers declarator                                                { $$ = new ASTParamDecl($1, $2); }
	| declaration_specifiers abstract_declarator                                       { todo(296); }
	| declaration_specifiers                                                           { $$ = new ASTParamDecl($1); }
	;

identifier_list
	: IDENTIFIER                                                                       { $$ = new ASTIdList(new ASTId($1)); }
	| identifier_list ',' IDENTIFIER                                                   { $$ = new ASTIdList($1, new ASTId($3)); }
	;

type_name
	: specifier_qualifier_list abstract_declarator
	| specifier_qualifier_list
	;

abstract_declarator
	: pointer direct_abstract_declarator
	| pointer
	| direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' '*' ']'
	| '[' STATIC assignment_expression ']'
	| '[' assignment_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' '*' ']'
	| direct_abstract_declarator '[' assignment_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: '{' initializer_list '}'                                                          { $$ = new ASTInitializer($2); }
	| '{' initializer_list ',' '}'                                                      { $$ = new ASTInitializer($2); }
	| assignment_expression                                                             { $$ = new ASTInitializer($1); }
	;

initializer_list
	: designation initializer                                                           { $$ = new ASTInitializerList($1, $2); }
	| initializer                                                                       { $$ = new ASTInitializerList($1); }
	| initializer_list ',' designation initializer                                      { $$ = new ASTInitializerList($1, $3, $4); }
	| initializer_list ',' initializer                                                  { $$ = new ASTInitializerList($1, $3); }

	;
designation
	: designator_list '='                                                               { $$ = $1; }
	;

designator_list
	: designator                                                                        { $$ = new ASTDesignatorList($1); }
	| designator_list designator                                                        { $$ = new ASTDesignatorList($1, $2); }
	;

designator
	: '[' constant_expression ']'                                                       { $$ = new ASTDesignator($2); }
	| '.' IDENTIFIER                                                                    { $$ = new ASTDesignator(new ASTId($2)); }
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
	: declaration_specifiers declarator declaration_list compound_statement             { $$ = new ASTFnDef($1, $2, $3, $4); }
	| declaration_specifiers declarator compound_statement                              { $$ = new ASTFnDef($1, $2, $3); }
	;

declaration_list
	: declaration                                                                       { $$ = new ASTDeclList(); }
	| declaration_list declaration                                                      { $$ = new ASTDeclList($1, $2); }
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
