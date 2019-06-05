%option noyywrap
%{
#include <stdio.h>
#include <string>
#include "y.tab.h"
%}

Letter [A-Za-z$_]
HexDigit [0-9a-fA-F]
LetterOrDigit [A-Za-z0-9]
Digits [0-9]([0-9_]*[0-9])?
HexDigits {HexDigit}(({HexDigit}|_)*{HexDigit})?
ExponentPart [eE][+-]?{Digits}
EscapeSequence \\[bfnrt"\\]
WhiteSpace [ \t\r\n]+
MultiLineComment /\*([^\*]|(\*)*[^\*/])*(\*)*\*/
LineComment //[^\r\n]*

decimalliteral (0|[1-9]({Digits}?|_+{Digits}))[lL]?
HexLiteral 0[xX]{HexDigit}([0-9a-f])
OctLiteral 0_*[0-7]([0-7_]*[0-7])?[lL]?
BinaryLiteral 0[bB][01]([01_]*[01])?[lL]?
FloatLiteral ({Digits}\.{Digits}?|\.{Digits}){ExponentPart}?[fFdD]?|{Digits}({ExponentPart}[fFdD]?|[fFdD])
HexFloatLiteral 0[xX]({HexDigits}\.?|{HexDigits}?\.{HexDigits})[pP][+-]?{Digits}[fFdD]?
CharLiteral '([^\\\r\n]|{EscapeSequence})'
StringLiteral "([^\\\r\n]|{EscapeSequence})*"
Identifier {Letter}{LetterOrDigit}*
%%
"abstract"      { yylval.token = ABSTRACT; return ABSTRACT; }
"assert"        { yylval.token = ASSERT; return ASSERT; }
"auto"          { yylval.token = AUTO; return AUTO; }
"boolean"       { yylval.token = BOOLEAN; return BOOLEAN; }
"break"         { yylval.token = BREAK; return BREAK; }
"byte"          { yylval.token = BYTE; return BYTE; }
"case"          { yylval.token = CASE; return CASE; }
"catch"         { yylval.token = CATCH; return CATCH; }
"char"          { yylval.token = CHAR; return CHAR; }
"class"         { yylval.token = CLASS; return CLASS; }
"const"         { yylval.token = CONST; return CONST; }
"continue"      { yylval.token = CONTINUE; return CONTINUE; }
"default"       { yylval.token = DEFAULT; return DEFAULT; }
"do"            { yylval.token = DO; return DO; }
"double"        { yylval.token = DOUBLE; return DOUBLE; }
"else"          { yylval.token = ELSE; return ELSE; }
"enum"          { yylval.token = ENUM; return ENUM; }
"extends"       { yylval.token = EXTENDS; return EXTENDS; }
"final"         { yylval.token = FINAL; return FINAL; }
"finally"       { yylval.token = FINALLY; return FINALLY; }
"float"         { yylval.token = FLOAT; return FLOAT; }
"for"           { yylval.token = FOR; return FOR; }
"if"            { yylval.token = IF; return IF; }
"goto"          { yylval.token = GOTO; return GOTO; }
"implements"    { yylval.token = IMPLEMENTS; return IMPLEMENTS; }
"import"        { yylval.token = IMPORT; return IMPORT; }
"instanceof"    { yylval.token = INSTANCEOF; return INSTANCEOF; }
"int"           { yylval.token = INT; return INT; }
"interface"     { yylval.token = INTERFACE; return INTERFACE; }
"long"          { yylval.token = LONG; return LONG; }
"native"        { yylval.token = NATIVE; return NATIVE; }
"new"           { yylval.token = NEW; return NEW; }
"package"       { yylval.token = PACKAGE; return PACKAGE; }
"private"       { yylval.token = PRIVATE; return PRIVATE; }
"protected"     { yylval.token = PROTECTED; return PROTECTED; }
"public"        { yylval.token = PUBLIC; return PUBLIC; }
"return"        { yylval.token = RETURN; return RETURN; }
"short"         { yylval.token = SHORT; return SHORT; }
"static"        { yylval.token = STATIC; return STATIC; }
"strictfp"      { yylval.token = STRICTFP; return STRICTFP; }
"super"         { yylval.token = SUPER; return SUPER; }
"switch"        { yylval.token = SWITCH; return SWITCH; }
"synchronized"  { yylval.token = SYNCHRONIZED; return SYNCHRONIZED; }
"this"          { yylval.token = THIS; return THIS; }
"throw"         { yylval.token = THROW; return THROW; }
"throws"        { yylval.token = THROWS; return THROWS; }
"transient"     { yylval.token = TRANSIENT; return TRANSIENT; }
"try"           { yylval.token = TRY; return TRY; }
"void"          { yylval.token = VOID; return VOID; }
"volatile"      { yylval.token = VOLATILE; return VOLATILE; }
"while"         { yylval.token = WHILE; return WHILE; }

"@"             { yylval.token = _AT; return _AT; }
"..."           { yylval.token = _ELLIPSIS; return _ELLIPSIS; }

"="             { yylval.token = ASSIGN; return ASSIGN; }
"~"             { yylval.token = TILDE; return TILDE; }
"?"             { yylval.token = QUESTION; return QUESTION; }
":"             { yylval.token = COLON; return COLON; }
"("             { yylval.token = LPAREN; return LPAREN; }
")"             { yylval.token = RPAREN; return RPAREN; }
"{"             { yylval.token = LBRACE; return LBRACE; }
"}"             { yylval.token = RBRACE; return RBRACE; }
"["             { yylval.token = LBRACK; return LBRACK; }
"]"             { yylval.token = RBRACK; return RBRACK; }
"."             { yylval.token = DOT; return DOT; }
","             { yylval.token = COMMA; return COMMA; }
";"             { yylval.token = SEMIC; return SEMIC; }
"!"             { yylval.token = BANG; return BANG; }
"<"             { yylval.token = LT; return LT; }
">"             { yylval.token = GT; return GT; }
"&"             { yylval.token = BITAND; return BITAND; }
"|"             { yylval.token = BITOR; return BITOR; }
"^"             { yylval.token = CARET; return CARET; }
"+"             { yylval.token = ADD; return ADD; }
"-"             { yylval.token = SUB; return SUB; }
"*"             { yylval.token = MUL; return MUL; }
"/"             { yylval.token = DIV; return DIV; }
"%"             { yylval.token = MOD; return MOD; }
"::"            { yylval.token = DCOLON; return DCOLON; }
"??"            { yylval.token = DEFAULT_VAL; return DEFAULT_VAL; }
"->"            { yylval.token = ARROW; return ARROW; }
"=="            { yylval.token = EQUAL; return EQUAL; }
"!="            { yylval.token = NEQUAL; return NEQUAL; }
"<="            { yylval.token = LTOE; return LTOE; }
">="            { yylval.token = GTOE; return GTOE; }
"&&"            { yylval.token = AND; return AND; }
"||"            { yylval.token = OR; return OR; }
"<<"            { yylval.token = LSHIFT; return LSHIFT; }
">>"            { yylval.token = RSHIFT; return RSHIFT; }
"++"            { yylval.token = INCRE; return INCRE; }
"--"            { yylval.token = DECRE; return DECRE; }
"+="            { yylval.token = ADD_ASSIGN; return ADD_ASSIGN; }
"-="            { yylval.token = SUB_ASSIGN; return SUB_ASSIGN; }
"*="            { yylval.token = MUL_ASSIGN; return MUL_ASSIGN; }
"/="            { yylval.token = DIV_ASSIGN; return DIV_ASSIGN; }
"&="            { yylval.token = AND_ASSIGN; return AND_ASSIGN; }
"|="            { yylval.token = OR_ASSIGN; return OR_ASSIGN; }
"^="            { yylval.token = XOR_ASSIGN; return XOR_ASSIGN; }
"%="            { yylval.token = MOD_ASSIGN; return MOD_ASSIGN; }
"<<="           { yylval.token = LSHIFT_ASSIGN; return LSHIFT_ASSIGN; }
">>="           { yylval.token = RSHIFT_ASSIGN; return RSHIFT_ASSIGN; }
">>>"           { yylval.token = URSHIFT; return URSHIFT; }
">>>="          { yylval.token = URSHIFT_ASSIGN; return URSHIFT_ASSIGN; }

"null"          { yylval.token = NULL_LITERAL; return NULL_LITERAL; }
"true"          { yylval.token = TRUE_LITERAL; return TRUE_LITERAL; }
"false"         { yylval.token = FALSE_LITERAL; return FALSE_LITERAL; }

{decimalliteral} {
    yylval.string = new std::string(yytext, yyleng);
    return DECIMAL_LITERAL;
}

{HexLiteral} {
    yylval.string = new std::string(yytext, yyleng);
    return HEX_LITERAL;
}

{OctLiteral} {
    yylval.string = new std::string(yytext, yyleng);
    return OCT_LITERAL;
}

{BinaryLiteral} {
    yylval.string = new std::string(yytext, yyleng);
    return BINARY_LITERAL;
}

{FloatLiteral} {
    yylval.string = new std::string(yytext, yyleng);
    return FLOAT_LITERAL;
}

{HexFloatLiteral} {
    yylval.string = new std::string(yytext, yyleng);
    return HEXFLOAT_LITERAL;
}

{CharLiteral} {
    yylval.string = new std::string(yytext, yyleng);
    return CHAR_LITERAL;
}

{StringLiteral} {
    yylval.string = new std::string(yytext, yyleng);
    return STRING_LITERAL;
}

{Identifier} {
    yylval.string = new std::string(yytext, yyleng);
    return IDENTIFIER;
}

{WhiteSpace} ;

%%

// other C st atements
// yyin yyout yytext yyleng yylineno yylex() yywrap() yyless() yymore()