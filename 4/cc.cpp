#include "ast.hpp"
#include "c.tab.hpp"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" int yylex();
extern ASTProgram *program_ast;
/* extern int yydebug; */
int yyparse();
extern "C" FILE *yyin;

static void usage() { printf("Usage: cc <prog.c>\n"); }

int main(int argc, char **argv) {
  if (argc != 2) {
    usage();
    exit(1);
  }
  char const *filename = argv[1];
  yyin = fopen(filename, "r");
  assert(yyin);

  /* yydebug = 1; */

  int ret = yyparse();
  printf("retv = %d\n", ret);
  if (ret != 0)
    exit(ret);
  program_ast->dump_ast(0);
  CodeGen *cg = new CodeGen();
  SemanticAnalyzer sa = SemanticAnalyzer(cg);
  if (!sa.analyze(program_ast)) {
    cout << "Semantic Analysis Failed" << endl;
    exit(1);
  }
  exit(0);
}
