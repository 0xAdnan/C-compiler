#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "c.tab.hpp"
#include "semantic_analysis.hpp"

extern "C" int yylex();
extern ASTNode *program_ast;
int yyparse();
extern "C" FILE *yyin;

static void usage()
{
  printf("Usage: cc <prog.c>\n");
}

int
main(int argc, char **argv)
{
  if (argc != 2) {
    usage();
    exit(1);
  }
  char const *filename = argv[1];
  yyin = fopen(filename, "r");
  assert(yyin);
  int ret = yyparse();
  printf("retv = %d\n", ret);
  program_ast->dump_ast(0);
  SemanticAnalyzer sa = SemanticAnalyzer();
  if (!sa.analyze(program_ast))
    exit(1);
  exit(0);
}
