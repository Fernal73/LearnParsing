%code top {
  #include <assert.h>
  /* isdigit. */
  #include <ctype.h>  
  /* pow. */
  #include <math.h>  
  /* printf. */
  #include <stdio.h>  
  /* abort. */
  #include <stdlib.h> 
  /* strcmp. */
  #include <string.h> 

  int yylex (void);
  void yyerror (char const *);
}


/* Generate YYSTYPE from the types used in %token and %type.  */
%define api.value.type union
%token <double> NUM "number"
%nterm  <double> expr term fact
%left '-' '+'
%left '*' '/' '%'
/* negation--unary minus */
%precedence NEG   
/* exponentiation */
%right '^'        

/* Generate the parser description file (calc.output).  */
%verbose

%define parse.assert true
/* Nice error messages with details. */
%define parse.error detailed

/* Enable run-time traces (yydebug).  */
%define parse.trace

%define parse.lac full

/* Formatting semantic values in debug traces.  */
%printer { fprintf (yyo, "%g", $$); } <double>;

%% /* The grammar follows.  */
input: %empty;
input: input line;

line: '\n';
line: expr '\n'  {
    printf ("%.10g\n", $1);} 
line: error '\n' { yyerrok; };

expr: expr '+' term { $$ = $1 + $3; };
expr: expr '-' term { $$ = $1 - $3; };
expr: term;

term: term '*' fact { $$ = $1 * $3; };
term: term '/' fact {
  if ($3 && $1)
    $$ = $1 / $3;
  else
    {
     $1 = 1;
     if ($1) {
      fprintf (stderr, "%d:%d - %d:%d:- division by zero.\n",
      @3.first_line,@3.first_column,
      @3.last_line,@3.last_column);
      yyerror("Division by zero");
     YYABORT;
      }
      else {
      fprintf (stderr, "%d:%d - %d:%d:- zero division by zero is undefined.\n",
      @1.first_line,@1.first_column,
      @3.last_line,@3.last_column);
      yyerror("Zero Division by zero is undefined.");
     YYABORT;
      }
      }
};
term: term '%' fact { $$ = fmod($1,$3); };
term: '-' fact  %prec NEG { $$ = -$2;};
term: '+' fact { $$ = $2;};
term: fact;

fact: "number";
fact: fact '^' fact { $$ = pow($1,$3);}; 
fact: '(' expr ')' { $$ = $2; };
%%

int yylex ()
{
  int c;
  /* Ignore white space, get first nonwhite character.  */
  while ((c = getchar ()) == ' ' || c == '\t') {
    ++yylloc.last_column;
    continue;
  }

  /* Step. */
  yylloc.first_line = yylloc.last_line;
  yylloc.first_column = yylloc.last_column;
 
  /* Char starts a number => parse the number.         */
  if (c == '.' || isdigit (c))
    {
      ungetc (c, stdin);
    if (scanf ("%lf", &yylval.NUM) != 1)
        abort ();
    ++yylloc.first_column;
    ++yylloc.last_column;
    return NUM;
  }

  if (c == EOF)
    return YYEOF;
    /* Return a single char, and update location. */
  if (c == '\n')
    {
      ++yylloc.last_line;
      yylloc.last_column = 0;
    }
  else
    ++yylloc.last_column;
  /* Any other character is a token by itself.        */
  return c;
}

/* Called by yyparse on error.  */
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

int main (int argc, char const* argv[])
{
  /* Enable parse traces on option -p.  */
  for (int i = 1; i < argc; ++i)
    if (!strcmp (argv[i], "-p"))
      yydebug = 1;
  yylloc.first_line = yylloc.last_line = 1;
  yylloc.first_column = yylloc.last_column = 0;
  return yyparse ();
}
