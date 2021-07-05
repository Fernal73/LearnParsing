%{
#include <stdlib.h>
#include "Parser.hpp"
#include "Scanner.hpp"
#define YY_DECL int calc::Scanner::lex(calc::Parser::semantic_type *yylval)
%}

%option c++ interactive noyywrap noyylineno nodefault outfile="Scanner.cpp"

dseq            ([[:digit:]]+)
dseq_opt        ({dseq}?)
frac            (({dseq_opt}"."{dseq})|{dseq}".")
exp             ([eE][+-]?{dseq})
exp_opt         ({exp}?)

integer         ({dseq})
float           (({frac}{exp_opt})|({dseq}{exp}))
intvar          ([[:upper:]]+)
fltvar          ([[:lower:]]+)

%%

{integer}       yylval->emplace<long long>(strtoll(YYText(), nullptr, 10)); return Parser::token::INT;
{float}         yylval->emplace<double>(strtod(YYText(), nullptr)); return Parser::token::FLT;
{intvar}        yylval->emplace<std::string>(YYText()); return Parser::token::INTVAR;
{fltvar}        yylval->emplace<std::string>(YYText()); return Parser::token::FLTVAR;
"+"             return Parser::token::PLUS;
"-"             return Parser::token::MINUS;
"*"             return Parser::token::MULTIPLY;
"/"             return Parser::token::DIVIDE;
"%"             return Parser::token::MODULO;
"!"             return Parser::token::FACTORIAL;
"^"             return Parser::token::EXPONENT;
"("             return Parser::token::LPAREN;
")"             return Parser::token::RPAREN;
"="             return Parser::token::ASSIGN;
\n              return Parser::token::EOL;
<<EOF>>         return Parser::token::YYEOF;
.               /* no action on unmatched input */

%%

int yyFlexLexer::yylex() {
    throw std::runtime_error("Invalid call to yyFlexLexer::yylex()");
}

int main() {
    calc::Scanner scanner{ std::cin, std::cerr };
    calc::Parser parser{ &scanner };
    parser.set_debug_level(0);
    std::cout.precision(10);
    parser.parse();
}
