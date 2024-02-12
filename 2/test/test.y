%{
#include <stdio.h>
%}

%token c d

%%
start: S { printf("Valid input.\n"); }
     ;

S: C C
  ;

C: c C
  | d
  ;

%%

int main() {
    yyparse();
    return 0;
}

int yywrap() {
    return 1;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

