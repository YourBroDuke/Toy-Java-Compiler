% {
#include <stdio.h>
% }
CHARS [A - Za - z]
words {CHARS}+
%%

{words} {wordCount++; }

%%

// other C statements
// yyin yyout yytext yyleng yylineno yylex() yywrap() yyless() yymore()