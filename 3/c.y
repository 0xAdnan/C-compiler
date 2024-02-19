%{
#include <cstdio>
#include <iostream>
#include "ast.hpp"

using namespace std;

ASTNode* program_ast;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
void todo(int);
%}


%token	IDENTIFIER I_CONSTANT F_CONSTANT STRING_LITERAL FUNC_NAME SIZEOF
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

%union value {
  ASTNode* ast;
}

%nterm <ast> primary_expression
%nterm <ast> constant
%nterm <ast> string
%nterm <ast> postfix_expression
%nterm <ast> argument_expression_list
%nterm <ast> unary_expression
%nterm <ast> unary_operator
%nterm <ast> cast_expression
%nterm <ast> multiplicative_expression
%nterm <ast> additive_expression
%nterm <ast> shift_expression
%nterm <ast> relational_expression
%nterm <ast> equality_expression
%nterm <ast> and_expression
%nterm <ast> exclusive_or_expression
%nterm <ast> inclusive_or_expression
%nterm <ast> logical_and_expression
%nterm <ast> logical_or_expression
%nterm <ast> conditional_expression
%nterm <ast> assignment_expression
%nterm <ast> assignment_operator
%nterm <ast> expression
%nterm <ast> constant_expression
%nterm <ast> declaration
%nterm <ast> declaration_specifiers
%nterm <ast> init_declarator_list
%nterm <ast> init_declarator
%nterm <ast> type_specifier
// %nterm <ast> specifier_qualifier_list
%nterm <ast> declarator
%nterm <ast> direct_declarator
%nterm <ast> pointer
%nterm <ast> parameter_type_list
%nterm <ast> parameter_list
%nterm <ast> parameter_declaration
%nterm <ast> identifier_list
// %nterm <ast> type_name
// %nterm <ast> abstract_declarator
// %nterm <ast> direct_abstract_declarator
%nterm <ast> initializer
%nterm <ast> initializer_list
%nterm <ast> designation
%nterm <ast> designator_list
%nterm <ast> designator
%nterm <ast> statement
%nterm <ast> labeled_statement
%nterm <ast> compound_statement
%nterm <ast> block_item_list
%nterm <ast> block_item
%nterm <ast> expression_statement
%nterm <ast> selection_statement
%nterm <ast> iteration_statement
%nterm <ast> jump_statement
%nterm <ast> translation_unit
%nterm <ast> external_declaration
%nterm <ast> function_definition
%nterm <ast> declaration_list


%%

primary_expression
	: IDENTIFIER                                                              { $$ = new ASTId(); }
	| constant                                                                { $$ = $1; }
	| string                                                                  { $$ = $1; }
	| '(' expression ')'                                                      { $$ = $2; }
	;

constant
	: I_CONSTANT		/* includes character_constant */                         { $$ = new ASTConst(i_const); }
	| F_CONSTANT                                                              { $$ = new ASTConst(f_const); }
	;

string
	: STRING_LITERAL                                                          { $$ = new ASTStrConst(); }
	| FUNC_NAME                                                               { $$ = new ASTFuncName(); }
	;

postfix_expression
	: primary_expression                                                        { $$ = new ASTPostExpr($1); }
	| postfix_expression '[' expression ']'                                     { $$ = new ASTPostExpr($1, $3); }
	| postfix_expression '(' ')'                                                { $$ = new ASTPostExpr($1); }
	| postfix_expression '(' argument_expression_list ')'                       { $$ = new ASTPostExpr($1, $3); }
	| postfix_expression '.' IDENTIFIER                                         { $$ = new ASTPostExpr($1, ASTPtrOp(dot_op), ASTId()); }
	| postfix_expression PTR_OP IDENTIFIER                                      { $$ = new ASTPostExpr($1, ASTPtrOp(ptr_op), ASTID()); }
	| postfix_expression INC_OP                                                 { $$ = new ASTPostExpr($1, ASTIncOp(plus_plus)); }
	| postfix_expression DEC_OP                                                 { $$ = new ASTPostExpr($1, ASTIncOp(minus_minus)); }
	| '(' type_name ')' '{' initializer_list '}'                                { todo(84); }
	| '(' type_name ')' '{' initializer_list ',' '}'                            { todo(85); }
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression                                                        { $$ = new ASTUnaryExpr($1)}
	| INC_OP unary_expression                                                   { $$ = new ASTUnaryExpr(plus_plus, $2); }
	| DEC_OP unary_expression                                                   { $$ = new ASTUnaryExpr(minus_minus, $2); }
	| unary_operator cast_expression                                            { $$ = new ASTUnaryExpr($1, $2); }
	| SIZEOF unary_expression                                                   { todo(98); }
	| SIZEOF '(' type_name ')'                                                  { todo(99); }
	| ALIGNOF '(' type_name ')'                                                 { todo(100); }
	;

unary_operator
	: '&'                                                                       { $$ = new ASTUnaryOp(u_op_and); }
	| '*'                                                                       { $$ = new ASTUnaryOp(u_op_star); }
	| '+'                                                                       { $$ = new ASTUnaryOp(u_op_plus); }
	| '-'                                                                       { $$ = new ASTUnaryOp(u_op_minus); }
	| '~'                                                                       { $$ = new ASTUnaryOp(u_op_tilde); }
	| '!'                                                                       { $$ = new ASTUnaryOp(u_op_not); }
	;

cast_expression
	: unary_expression                                                          { $$ = $1; }
	| '(' type_name ')' cast_expression                                         { todo(160); }
	;

multiplicative_expression
	: cast_expression                                                            { $$ = $1; }
	| multiplicative_expression '*' cast_expression                              { $$ = new ASTMulExpr($1, new ASTArithOp(mul_op), $3); }
	| multiplicative_expression '/' cast_expression                              { $$ = new ASTMulExpr($1, new ASTArithOp(div_op), $3); } 
	| multiplicative_expression '%' cast_expression                              { $$ = new ASTMulExpr($1, new ASTArithOp(remainder_op), $3); }
	;

additive_expression
	: multiplicative_expression                                                   { $$ = new ASTAddExpr($1); }
	| additive_expression '+' multiplicative_expression                           { $$ = new ASTAddExpr($1, new ASTArithOp(add_op), $3); }
	| additive_expression '-' multiplicative_expression                           { $$ = new ASTAddExpr($1, new ASTArithOp(minus_op), $3); }
	;

shift_expression
	: additive_expression                                                          { $$ = new ASTShiftExpr($1); }
	| shift_expression LEFT_OP additive_expression                                 { $$ = new ASTShiftExpr($1, $3); }
	| shift_expression RIGHT_OP additive_expression                                { $$ = new ASTShiftExpr($1, $3); }
	;

relational_expression
	: shift_expression                                                             { $$ = new ASTRelExpr($1); }
	| relational_expression '<' shift_expression                                   { $$ = new ASTRelExpr($1, new ASTRelOp(less), $3); }
	| relational_expression '>' shift_expression                                   { $$ = new ASTRelExpr($1, new ASTRelOp(greater), $3); }
	| relational_expression LE_OP shift_expression                                 { $$ = new ASTRelExpr($1, new ASTRelOp(less_eq), $3); }
	| relational_expression GE_OP shift_expression                                 { $$ = new ASTRelExpr($1, new ASTRelOp(greater_eq), $3); }
	;

equality_expression
	: relational_expression                                                         { $$ = new ASTEqExpr($1); }
	| equality_expression EQ_OP relational_expression                               { $$ = new ASTEqExpr($1, $3); }
	| equality_expression NE_OP relational_expression                               { $$ = new ASTEqExpr($1, $3); }
	;

and_expression
	: equality_expression                                                           { $$ = new ASTAndExpr($1); }
	| and_expression '&' equality_expression                                        { $$ = new ASTAndExpr($1, $3); }
	;

exclusive_or_expression
	: and_expression                                                                { $$ = new ASTExclusiveOrExpr($1); }
	| exclusive_or_expression '^' and_expression                                    { $$ = new ASTExclusiveOrExpr($1, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression                                                       { $$ = new ASTInclusiveOrExpr($1); }
	| inclusive_or_expression '|' exclusive_or_expression                           { $$ = new ASTInclusiveOrExpr($1, $3); }
	;

logical_and_expression
	: inclusive_or_expression                                                       { $$ = new ASTLogicalAndExpr($1); }
	| logical_and_expression AND_OP inclusive_or_expression                         { $$ = new ASTLogicalAndExpr($1, $3); }
	;

logical_or_expression
	: logical_and_expression                                                        { $$ = new ASTLogicalOrExpr($1); }
	| logical_or_expression OR_OP logical_and_expression                            { $$ = new ASTLogicalOrExpr($1, $3); }
	;

conditional_expression
	: logical_or_expression                                                         { $$ = new ASTCondExpr($1); }
	| logical_or_expression '?' expression ':' conditional_expression               { $$ = new ASTCondExpr($1, $3, $5); }
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
	: VOID                                                                           { $$ = new ASTType(tvoid); }
	| CHAR                                                                           { $$ = new ASTType(tchar); }
	| SHORT                                                                          { $$ = new ASTType(tshort); }
	| INT                                                                            { $$ = new ASTType(tint); }
	| FLOAT                                                                          { $$ = new ASTType(tfloat); }
  | LONG                                                                           { $$ = new ASTType(tlong); }
	| DOUBLE                                                                         { $$ = new ASTType(tdouble); }
	| SIGNED                                                                         { $$ = new ASTType(tsigned); }
	| UNSIGNED                                                                       { $$ = new ASTType(tunsigned); }
	| BOOL                                                                           { $$ = new ASTType(tbool); }
	| COMPLEX                                                                        { $$ = new ASTType(tcomplex); }
	| IMAGINARY	  	/* non-mandated extension */                                     { $$ = new ASTType(timaginary); }
	| TYPEDEF_NAME		                                                               { todo(262); }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	;

declarator
	: pointer direct_declarator                                                       { todo(345);}
	| direct_declarator                                                               { $$ = $1;}
	;

direct_declarator
	: IDENTIFIER                                                                      { $$ = new ASTIdDeclrator(ASTId()); }
	| '(' declarator ')'                                                              { $$ = $2; }
	| direct_declarator '[' ']'                                                       { todo(352); }
	| direct_declarator '[' '*' ']'                                                   { todo(353); }
	| direct_declarator '[' assignment_expression ']'                                 { todo(360); }
	| direct_declarator '(' parameter_type_list ')'                                   { $$ = new ASTFnDeclrator($1, $3);}
	| direct_declarator '(' ')'                                                       { $$ = new ASTFnDeclrator($1);}
	| direct_declarator '(' identifier_list ')'                                       { $$ = new ASTFnCallDeclrator($1, $3);}
	;

pointer
	: '*' pointer                                                                     { $$ = new ASTPtr($2); }
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
	: IDENTIFIER                                                                       { $$ = new ASTIdList(new ASTId()); }
	| identifier_list ',' IDENTIFIER                                                   { $$ = new ASTIdList($1, new ASTId()); }
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
	: '{' initializer_list '}'                                    { $$ = $2; }
	| '{' initializer_list ',' '}'                                { $$ = $2; }
	| assignment_expression                                       { $$ = $1 }
	;

initializer_list
	: designation initializer                                     { $$ = new ASTInitializerList($1, $2); }
	| initializer                                                 { $$ = new ASTInitializerList($1); }
	| initializer_list ',' designation initializer                { $$ = new ASTInitializerList($1, $3, $4); }
	| initializer_list ',' initializer                            { $$ = new ASTInitializerList($1, $3); }

	;
designation
	: designator_list '='                                         { $$ = $1; }
	;

designator_list
	: designator                                                  { $$ = new ASTDesignatorList($1); }
	| designator_list designator                                  { $$ = new ASTDesignatorList($1, $2); }
	;

designator
	: '[' constant_expression ']'                                 { $$ = $2; }
	| '.' IDENTIFIER                                              { $$ = new ASTId(); }
	;

statement
	: labeled_statement                                           { $$ = $1; }
	| compound_statement                                          { $$ = $1; }
	| expression_statement                                        { $$ = $1; }
	| selection_statement                                         { $$ = $1; }
	| iteration_statement                                         { $$ = $1; }
	| jump_statement                                              { $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement                                    { $$ = new ASTGotoLabeledStmt(ASTId(), $3); }
	| CASE constant_expression ':' statement                      { $$ = new ASTCaseLabeledStmt($2, $4); }
	| DEFAULT ':' statement                                       { $$ = new ASTDefLabeledStmt($3); } 
	;

compound_statement
	: '{' '}'                                                     { $$ = NULL; }
	| '{'  block_item_list '}'                                    { $$ = $2; }
	;

block_item_list
	: block_item                                                  { $$ = new ASTBlockItemList($1); }
	| block_item_list block_item                                  { $$ = new ASTBlockItemList($1, $2); }
	;

block_item
	: declaration                                                 { $$ = $1; }
	| statement                                                   { $$ = $1; }
	;

expression_statement
	: ';'                                                         { $$ = NULL; }
	| expression ';'                                              { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement ELSE statement                                { $$ = new ASTSelectStmt($3, $5, $7); }
	| IF '(' expression ')' statement                                               { $$ = new ASTSelectStmt($3, $5); }
	| SWITCH '(' expression ')' statement                                           { $$ = new ASTSelectStmt($3, $5); }
	;

iteration_statement
	: WHILE '(' expression ')' statement                                            { $$ = new ASTWhileStmt($3, $5); }
	| DO statement WHILE '(' expression ')' ';'                                     { $$ = new ASTDoWhileStmt($2, $5); }
	| FOR '(' expression_statement expression_statement ')' statement               { $$ = new ASTForStmt($3, $4, $6); }
	| FOR '(' expression_statement expression_statement expression ')' statement    { $$ = new ASTForStmt($3, $4, $5, $7); }
	| FOR '(' declaration expression_statement ')' statement                        { $$ = new ASTForStmt($3, $4, $6); }
	| FOR '(' declaration expression_statement expression ')' statement             { $$ = new ASTForStmt($3, $4, $5, $7); }
	;

jump_statement
	: GOTO IDENTIFIER ';'                                                           { new ASTGotoJmpStmt(new ASTId()); }
	| CONTINUE ';'                                                                  { new ASTContJmpStmt(); }
	| BREAK ';'                                                                     { new ASTBreakJmpStmt(); }
	| RETURN ';'                                                                    { new ASTRetJmpStmt(); }
	| RETURN expression ';'                                                         { new ASTRetmpStmt($2); }
	;

translation_unit
	: external_declaration                                                          { $$ = new ASTProgram($1); program_ast = $$;}
	| translation_unit external_declaration                                         { $$ = new ASTProgram($1, $2); program_ast = $$; }
	;

external_declaration
	: function_definition                                                           { $$ = new ASTExternDecl($1); }
	| declaration                                                                   { $$ = new ASTExternDecl($1); }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement         { $$ = new ASTFnDef($1, $2, $3, $4); }
	| declaration_specifiers declarator compound_statement                          { $$ = new ASTFnDef($1, $2, $3); }
	;

declaration_list
	: declaration                                                                   { $$ = new ASTDeclList(); }
	| declaration_list declaration                                                  { $$ = new ASTDeclList($1, $2); }
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
