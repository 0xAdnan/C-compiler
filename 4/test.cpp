//
// Created by satyam on 2/4/24.
//
#include <gtest/gtest.h>

#include "src/ast/prog.h"
#include "codegen.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>

extern "C" int yylex();
extern ASTProgram *program_ast;
//extern int yydebug;
int yyparse();
extern "C" FILE *yyin;


TEST(CompilerTest, BasicAssertions) {
  char filename[1000] = "/home/satyam/dev/compiler_assignment/4/examples/negative/expr/init.c";
  yyin = fopen(filename, "r");
  assert(yyin);

  int ret = yyparse();
  EXPECT_EQ(ret, 0);

  auto* cg = new Codegen(filename);

  EXPECT_ANY_THROW(cg->visit(program_ast));
}