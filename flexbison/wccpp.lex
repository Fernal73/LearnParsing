/* just like Unix wc */
/* [a-zA-Z]+ { words++; chars += strlen(yytext); } */
%option noyywrap
%{
#include <iomanip>
int chars = 0;
int words = 0;
int lines = 0;
%}
%%
[^ \t\n\r\f\v]+ { words++; chars += strlen(yytext); }
\n { chars++; lines++; }
. { chars++; }
%%
int main(int argc, char **argv)
{
  FlexLexer* lexer = new yyFlexLexer;
  lexer->yylex();
  using namespace std;
  cout << setw(8) << lines << setw(8) << words << setw(8) << chars << endl;
}
