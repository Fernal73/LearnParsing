/* simplest version of calculator */
%{
#include <stdio.h>
%}
/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS MOD OP CP
%token EOL
%%
calclist:
 | calclist exp EOL { printf("= %d\n", $2); } 
 ;
exp: factor { $$ = $1; }
 | exp ADD factor { $$ = $1 + $3; }
 | exp SUB factor { $$ = $1 - $3; }
 ;
factor: term { $$ = $1; }
 | factor MUL term { $$ = $1 * $3; }
 | factor DIV term { 
 if ($3 == 0) {
 yyerror("cannot be divided by zero"); exit(1);
 } else
 $$ = $1 / $3; 
 }
 | factor MOD term { $$ = $1 % $3; }
 ;
term: NUMBER { $$ = $1; }
 | ABS term ABS { $$ = $2 >= 0 ? $2 : -$2; }
 | OP exp CP { $$ = $2; } 
 ;
%%
int main(int argc, char **argv)
{
 return yyparse();
}
int yyerror(char *s)
{
 return fprintf(stderr, "error: %s\n", s);
}
