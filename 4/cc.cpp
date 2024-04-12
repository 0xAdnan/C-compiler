#include "src/ast/prog.h"
#include "codegen.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>

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
 char *filename = argv[1];
//  char filename[1000] = "/home/satyam/dev/compiler_assignment/4/examples/positive/expr/init.c";
  // char filename[1000] = "/home/satyam/dev/compiler_assignment/4/examples/positive/stmts/ifStmt.c";
  yyin = fopen(filename, "r");
  assert(yyin);

  /* yydebug = 1; */

  int ret = yyparse();
  printf("retv = %d\n", ret);
  if (ret != 0)
    exit(ret);
  program_ast->dump_ast(0);

  auto *cg = new Codegen(filename);
  cg->visit(program_ast);
  cg->dumpCode();
  cg->dumpFile("/home/adnan/Documents/col728lab/compiler_assignment/4/src/visitor/output.ll");

//  SemanticAnalyzer sa = SemanticAnalyzer(cg);
//  if (!sa.analyze(program_ast)) {
//    cout << "Semantic Analysis Failed" << endl;
//  }
}
