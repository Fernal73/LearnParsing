/* recognize tokens for the calculator and print them out */
%{
#include "calc.tab.h"
%}
%%
"+" { return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"|" { return ABS; }
"%" { return MOD; }
[0-9]+ { yylval = atoi(yytext); return NUMBER; }
\n { return EOL; }
[ \t] { /* ignore whitespace */ }
"(" { return OP; }
")" { return CP; }
"//".* /* ignore comments */
. { printf("Mystery character %c\n", *yytext); }
%%
