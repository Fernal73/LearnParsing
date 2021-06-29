/* simplest version of calculator */
%require "3.2"
%language "c++"
%{
#include <iostream>
#include <cmath>
#include <string>
int error(std::string& s)
{
using namespace std;
cerr << "error: " <<  s << endl;
return 0;
}
%}

/* declare type possibilities of symbols */
%union {
  double value;
}
%{
yy::parser::semantic_type yylval;
extern int yylex(yy::parser::semantic_type* yylval);
%}
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
 | calclist exp EOL { 
using namespace std;
cout << "= " << $2 << endl; } 
 ;
exp: factor { $$ = $1; }
 | exp ADD factor { $$ = $1 + $3; }
 | exp SUB factor { $$ = $1 - $3; }
 ;
factor: term { $$ = $1; }
 | factor MUL term { $$ = $1 * $3; }
 | factor DIV term { 
 if ($3 == 0) {
 error("cannot be divided by zero"); exit(1);
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
 // yy::parser parse;
 // return parse.parse();
  return 0;
}
