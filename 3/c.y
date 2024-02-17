%{
#include <cstdio>
#include <iostream>
#include "ast.h"

using namespace std;

ASTProgram ast_program();

// stuff from flex that bison needs to know about:
extern "C" int yylex();
int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
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
%%

primary_expression
	: IDENTIFIER                                                              { $$ = ASTId($1); }
	| constant                                                                { $$ = $1; }
	| string                                                                  { $$ = $1; }
	| '(' expression ')'                                                      { $$ = $2; }
	| generic_selection                                                       { todo(); }
	;

constant
	: I_CONSTANT		/* includes character_constant */                         { $$ = ASTIConst(int($1)); }
	| F_CONSTANT                                                              { $$ = ASTFConst(float($1)); }
	| ENUMERATION_CONSTANT	/* after it has been defined as such */           { todo(); }
	;

enumeration_constant		/* before it has been defined as such */
	: IDENTIFIER
	;

string
	: STRING_LITERAL                                                         { $$ = ASTStrConst($1); }
	| FUNC_NAME                                                              { $$ = ASTFuncName($1); }
	;

generic_selection
	: GENERIC '(' assignment_expression ',' generic_assoc_list ')'
	;

generic_assoc_list
	: generic_association
	| generic_assoc_list ',' generic_association
	;

generic_association
	: type_name ':' assignment_expression
	| DEFAULT ':' assignment_expression
	;

postfix_expression
	: primary_expression                                                        { $$ = $1; }
	| postfix_expression '[' expression ']'                                     { todo(); }
	| postfix_expression '(' ')'                                                { todo(); }
	| postfix_expression '(' argument_expression_list ')'                       { todo(); }
	| postfix_expression '.' IDENTIFIER                                         { todo(); }
	| postfix_expression PTR_OP IDENTIFIER                                      { todo(); }
	| postfix_expression INC_OP                                                 { todo(); }
	| postfix_expression DEC_OP                                                 { todo(); }
	| '(' type_name ')' '{' initializer_list '}'                                { todo(); }
	| '(' type_name ')' '{' initializer_list ',' '}'                            { todo(); }
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression                                                        { $$ = $1}
	| INC_OP unary_expression                                                   { $$ = ASTUnaryExp(ASTOp($1), $2); }
	| DEC_OP unary_expression                                                   { $$ = ASTUnaryExp(ASTOp($1), $2); }
	| unary_operator cast_expression                                            { $$ = ASTUnaryExp(ASTOp($1), $2); }
	| SIZEOF unary_expression                                                   { todo(); }
	| SIZEOF '(' type_name ')'                                                  { todo(); }
	| ALIGNOF '(' type_name ')'                                                 { todo(); }
	;

unary_operator
	: '&'                                                                       { $$ = ASTOp($1); }
	| '*'                                                                       { $$ = ASTOp($1); }
	| '+'                                                                       { $$ = ASTOp($1); }
	| '-'                                                                       { $$ = ASTOp($1); }
	| '~'                                                                       { $$ = ASTOp($1); }
	| '!'                                                                       { $$ = ASTOp($1); }
	;

cast_expression
	: unary_expression                                                          { $$ = $1; }
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression                                                         { todo(); }
	| unary_expression assignment_operator assignment_expression                     { $$ = ASTAssignmentExpr($1, $2, $3);}
	;

assignment_operator
	: '='                                                                            { $$ = ASTOp($1); }
	| MUL_ASSIGN                                                                     { $$ = ASTOp($1); }
	| DIV_ASSIGN                                                                     { $$ = ASTOp($1); }
	| MOD_ASSIGN                                                                     { $$ = ASTOp($1); }
	| ADD_ASSIGN                                                                     { $$ = ASTOp($1); }
	| SUB_ASSIGN                                                                     { $$ = ASTOp($1); }
	| LEFT_ASSIGN                                                                    { $$ = ASTOp($1); }
	| RIGHT_ASSIGN                                                                   { $$ = ASTOp($1); }
	| AND_ASSIGN                                                                     { $$ = ASTOp($1); }
	| XOR_ASSIGN                                                                     { $$ = ASTOp($1); }
	| OR_ASSIGN                                                                      { $$ = ASTOp($1); }
	;

expression
	: assignment_expression                                                             { $$ = $1; }
	| expression ',' assignment_expression                                              { $$ = ASTExpr($1, $3); }
	;

constant_expression
	: conditional_expression	/* with constraints */
	;

declaration
	: declaration_specifiers ';'                      { $$ = ASTDecl($1); }
	| declaration_specifiers init_declarator_list ';' { $$ = ASTDecl($1, $2); }
	| static_assert_declaration                       { todo(); }
	;

declaration_specifiers
	: storage_class_specifier declaration_specifiers { todo(); }
	| storage_class_specifier                        { todo(); }
	| type_specifier declaration_specifiers          { $$ = ASTDeclSpec($1, $2); }
	| type_specifier                                 { $$ = ASTDeclSpec($1); }
	| type_qualifier declaration_specifiers          { todo(); }
	| type_qualifier                                 { todo(); }
	| function_specifier declaration_specifiers      { todo(); }
	| function_specifier                             { todo(); }
	| alignment_specifier declaration_specifiers     { todo(); }
	| alignment_specifier                            { todo(); }
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator '=' initializer
	| declarator
	;

storage_class_specifier
	: TYPEDEF	/* identifiers must be flagged as TYPEDEF_NAME */
	| EXTERN
	| STATIC
	| THREAD_LOCAL
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID                                          { $$ = ASTType($1); }
	| CHAR                                          { $$ = ASTType($1); }
	| SHORT                                         { $$ = ASTType($1); }
	| INT                                           { $$ = ASTType($1); }
	| LONG                                          { $$ = ASTType($1); }
	| FLOAT                                         { $$ = ASTType($1); }
	| DOUBLE                                        { $$ = ASTType($1); }
	| SIGNED                                        { $$ = ASTType($1); }
	| UNSIGNED                                      { $$ = ASTType($1); }
	| BOOL                                          { $$ = ASTType($1); }
	| COMPLEX                                       { $$ = ASTType($1); }
	| IMAGINARY	  	/* non-mandated extension */    { $$ = ASTType($1); }
	| atomic_type_specifier                         { todo(); }
	| struct_or_union_specifier                     { todo(); }
	| enum_specifier                                { todo(); }
	| TYPEDEF_NAME		                              { todo(); }
	;

struct_or_union_specifier
	: struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list ';'	/* for anonymous struct/union */
	| specifier_qualifier_list struct_declarator_list ';'
	| static_assert_declaration
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: ':' constant_expression
	| declarator ':' constant_expression
	| declarator
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator	/* identifiers must be flagged as ENUMERATION_CONSTANT */
	: enumeration_constant '=' constant_expression
	| enumeration_constant
	;

atomic_type_specifier
	: ATOMIC '(' type_name ')'
	;

type_qualifier
	: CONST
	| RESTRICT
	| VOLATILE
	| ATOMIC
	;

function_specifier
	: INLINE
	| NORETURN
	;

alignment_specifier
	: ALIGNAS '(' type_name ')'
	| ALIGNAS '(' constant_expression ')'
	;

declarator
	: pointer direct_declarator                                                       { todo();}
	| direct_declarator                                                               { $$ = ASTDeclrator($1);}
	;

direct_declarator
	: IDENTIFIER                                                                      { $$ = ASTDirectDeclrator($2);}
	| '(' declarator ')'                                                              { $$ = ASTDirectDeclrator($1);}
	| direct_declarator '[' ']'                                                       { todo(); }
	| direct_declarator '[' '*' ']'                                                   { todo(); }
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'      { todo(); }
	| direct_declarator '[' STATIC assignment_expression ']'                          { todo(); }
	| direct_declarator '[' type_qualifier_list '*' ']'                               { todo(); }
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'      { todo(); }
	| direct_declarator '[' type_qualifier_list assignment_expression ']'             { todo(); }
	| direct_declarator '[' type_qualifier_list ']'                                   { todo(); }
	| direct_declarator '[' assignment_expression ']'                                 { todo(); }
	| direct_declarator '(' parameter_type_list ')'                                   { $$ = ASTDirectDeclrator($1, $3);}
	| direct_declarator '(' ')'                                                       { $$ = ASTDirectDeclrator($1);}
	| direct_declarator '(' identifier_list ')'                                       { $$ = ASTDirectDeclrator($1, $3);}
	;

pointer
	: '*' type_qualifier_list pointer
	| '*' type_qualifier_list
	| '*' pointer
	| '*'
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list ',' ELLIPSIS
	| parameter_list
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
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
	| '[' STATIC type_qualifier_list assignment_expression ']'
	| '[' STATIC assignment_expression ']'
	| '[' type_qualifier_list STATIC assignment_expression ']'
	| '[' type_qualifier_list assignment_expression ']'
	| '[' type_qualifier_list ']'
	| '[' assignment_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' '*' ']'
	| direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
	| direct_abstract_declarator '[' STATIC assignment_expression ']'
	| direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
	| direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
	| direct_abstract_declarator '[' type_qualifier_list ']'
	| direct_abstract_declarator '[' assignment_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	| assignment_expression
	;

initializer_list
	: designation initializer
	| initializer
	| initializer_list ',' designation initializer
	| initializer_list ',' initializer
	;

designation
	: designator_list '='
	;

designator_list
	: designator
	| designator_list designator
	;

designator
	: '[' constant_expression ']'
	| '.' IDENTIFIER
	;

static_assert_declaration
	: STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';'
	;

statement
	: labeled_statement                                           { todo(); }
	| compound_statement                                          { $$ = $1; }
	| expression_statement                                        { $$ = $1; }
	| selection_statement                                         { $$ = $1; }
	| iteration_statement                                         { todo(); }
	| jump_statement                                              { $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'                                                     { $$ = NULL; }
	| '{'  block_item_list '}'                                    { $$ = $2; }
	;

block_item_list
	: block_item                                                  { $$ = $1; }
	| block_item_list block_item                                  { $$ = ASTBlockItemList($1, $2); }
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
	: IF '(' expression ')' statement ELSE statement
	| IF '(' expression ')' statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	| FOR '(' declaration expression_statement ')' statement
	| FOR '(' declaration expression_statement expression ')' statement
	;

jump_statement
	: GOTO IDENTIFIER ';'                                                 { todo(); }
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

translation_unit
	: external_declaration                                                  { $$ = ASTTranslationUnit($1); program_ast = $$;}
	| translation_unit external_declaration                                 { $$ = ASTTranslationUnit($1, $2); program_ast = $$; }
	;

external_declaration
	: function_definition                                                   { $$ = ASTExternDecl($1); }
	| declaration                                                           { $$ = ASTExternDecl($1); }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement { $$ = ASTFnDef($1, $2, $3, $4); }
	| declaration_specifiers declarator compound_statement                  { $$ = ASTFnDef($1, $2, $3); }
	;

declaration_list
	: declaration { $$ = ASTDeclList(); }
	| declaration_list declaration { $$ = ASTDeclList($1, $2); }
	;

%%
#include <stdio.h>

void yyerror(const char *s)
{
	fflush(stdout);
	fprintf(stderr, "*** %s\n", s);
}
