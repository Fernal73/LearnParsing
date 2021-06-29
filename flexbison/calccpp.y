/* simplest version of calculator */
%require "3.2"
%language "c++"
//%define api.value.type variant
//%define api.token.constructor
%{
#include <cmath>
using namespace std;
%}

/* declare type possibilities of symbols */
%union {
  double value;
}
/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS MOD OP CP
%token EOL
%type<value> exp
%type<value> term
%type<value> factor
%type<value> NUMBER

%%
calclist:
 | calclist exp EOL { cout << "= " << $2 << endl; } 
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
 | factor MOD term { $$ = std::fmod($1,$3); }
 ;
term: NUMBER { $$ = $1; }
 | ABS term ABS { $$ = $2 >= 0 ? $2 : -$2; }
 | OP exp CP { $$ = $2; } 
 ;
%%
int main(int argc, char **argv)
{
  yy::parser parse;
  return parse ();
}
int yyerror(char *s)
{
using namespace std;
cerr << "error: " <<  s << endl;
}
