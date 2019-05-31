%{
#include "node.h"
#include <cstdio>
#include <cstdlib>
extern int yylex();
void yyerror(const char *s) {
	printf("Error: %s\n", s);
	exit(1); 
}
%}

/* Represents the many different ways we can access our data */
%union {
	Node *node;
	NBlock *block;
	NExpression *expr;
	std::string *string;
	int token;
}

/* Define our terminal symbols (tokens). This should
   match our tokens.l lex file. We also define the node type
   they represent.
 */
%token <string> IDENTIFIER DECIMAL_LITERAL HEX_LITERAL OCT_LITERAL BINARY_LITERAL
%token <string> FLOAT_LITERAL HEXFLOAT_LITERAL CHAR_LITERAL STRING_LITERAL
%token <token> PACKAGE SEMIC DOT

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */


/* Operator precedence for mathematical operators */

%start program

%%

CompilationUnit: 
	PackageDeclaration ImportDeclaration TypeDeclaration
	;

PackageDeclaration: 
	PackageAnnotation PACKAGE QualifiedName SEMIC
	;

PackageAnnotation: 
	| Annotation
	;

QualifiedName: 
	IDENTIFIER ExtIdentifier SEMIC
	;

ExtIdentifier: 
	DOT IDENTIFIER
	| DOT IDENTIFIER ExtIdentifier
	;

Annotation:
	;

ImportDeclaration:
	;

TypeDeclaration:
	;
%%

// Hello