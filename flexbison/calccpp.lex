/* recognize tokens for the calculator and print them out */
%{
#include <iostream>
#include <string>
#include "calccpp.tab.hh"
using token = yy::parser::token;
%}
%%
"+" { return token::ADD; }
"-" { return token::SUB; }
"*" { return token::MUL; }
"/" { return token::DIV; }
"|" { return token::ABS; }
"%" { return token::MOD; }
[0-9]+ { yylval.value = std::stod(yytext); return token::NUMBER; }
[0-9]+.[0-9]+ { yylval.value = std::stod(yytext); return token::NUMBER; }
\n { return token::EOL; }
[ \t] { /* ignore whitespace */ }
"(" { return token::OP; }
")" { return token::CP; }
"//".* /* ignore comments */
. {
  using namespace std;
  cout << "Mystery character " << *yytext << endl; 
}
%%
