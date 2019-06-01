%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
extern int yylex();
void yyerror(const char *s) {
	printf("Error: %s\n", s);
	exit(1); 
}
using namespace std;
#define DEBUG

void debugInfo(const char* s){
	#ifdef DEBUG
		cout << "debug: " << s << endl;
	#endif
}

void debugInfo(string *s){
	debugInfo(s->c_str());
}
%}

/* Represents the many different ways we can access our data */
%union {
	std::string *string;
	int token;
}

/* Define our terminal symbols (tokens). This should
   match our tokens.l lex file. We also define the node type
   they represent.
 */
%token <string> IDENTIFIER DECIMAL_LITERAL HEX_LITERAL OCT_LITERAL BINARY_LITERAL
%token <string> FLOAT_LITERAL HEXFLOAT_LITERAL CHAR_LITERAL STRING_LITERAL
%token <token>  ABSTRACT ASSERT AUTO BOOLEAN BREAK BYTE CASE CATCH CHAR CLASS
%token <token> CONST CONTINUE DEFAULT DO
%token <token> DOUBLE ELSE ENUM EXTENDS FINAL FINALLY FLOAT FOR IF GOTO
%token <token> IMPLEMENTS IMPORT INSTANCEOF INT INTERFACE LONG NATIVE NEW
%token <token> PACKAGE PRIVATE PROTECTED PUBLIC RETURN SHORT STATIC STRICTFP
%token <token> SUPER SWITCH SYNCHRONIZED THIS THROW THROWS TRANSIENT
%token <token> TRY VOID VOLATILE WHILE _AT _ELLIPSIS ASSIGN TILDE
%token <token> QUESTION COLON LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK
%token <token> DOT COMMA SEMIC BANG LT GT BITAND BITOR CARET ADD SUB MUL DIV
%token <token> MOD EQUAL NEQUAL LTOE GTOE AND OR LSHIFT RSHIFT INCRE
%token <token> DECRE ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN AND_ASSIGN
%token <token> OR_ASSIGN XOR_ASSIGN MOD_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN
%token <token> URSHIFT URSHIFT_ASSIGN NULL_LITERAL TRUE_LITERAL FALSE_LITERAL

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */


/* Operator precedence for mathematical operators */

%%

CompilationUnit:
	PackageDeclaration ImportDeclaration TypeDeclaration
	;

PackageDeclaration: 
	PACKAGE QualifiedName SEMIC
	| Annotation PACKAGE QualifiedName SEMIC {debugInfo("match package decl");}
	;

QualifiedName: 
	IDENTIFIER 
	| QualifiedName DOT IDENTIFIER {debugInfo("match qualified name");}
	;

AnnotationList:
	Annotation
	| AnnotationList Annotation
	;

Annotation:
	_AT QualifiedName
	| _AT QualifiedName LPAREN AnnotationValue RPAREN
	;

AnnotationValue:
	ElementValuePairs
	| ElementValue
	;

ElementValuePairs:
	ElementValuePair
	| ElementValuePairs ElementValuePair
	;

ElementValuePair:
	IDENTIFIER EQUAL ElementValue
	;

ElementValue:
	Expression
	| Annotation
	| ElementValueInitializer
	;

Expression:
	IDENTIFIER;

ElementValueInitializer:
	LBRACE ElementValues RBRACE
	| LBRACE ElementValues COMMA RBRACE
	;

ElementValues:
	ElementValue
	| ElementValues COMMA ElementValue
	;

ImportDeclaration:
	SingleImportDecl
	| TypeImportDecl
	;

SingleImportDecl:
	IMPORT QualifiedName SEMIC
	| IMPORT STATIC QualifiedName SEMIC
	;

TypeImportDecl:
	IMPORT QualifiedName DOT MUL SEMIC
	| IMPORT STATIC QualifiedName DOT MUL SEMIC
	;
	
TypeDeclaration:
	ClassOrInterfaceModifierListOptional ClassDecl
	| ClassOrInterfaceModifierListOptional EnumDecl
	| ClassOrInterfaceModifierListOptional InterfaceDecl
	| ClassOrInterfaceModifierListOptional AnnotationTypeDecl
	| SEMIC
	;

ClassOrInterfaceModifierListOptional:
	ClassOrInterfaceModifierList
	|
	;

ClassOrInterfaceModifierList:
	ClassOrInterfaceModifier
	| ClassOrInterfaceModifierList ClassOrInterfaceModifier
	;

ClassOrInterfaceModifier:
	Annotation
	| PUBLIC
	| PRIVATE
	| PROTECTED
	| STATIC
	| ABSTRACT
	| FINAL
	| STRICTFP
	;

Modifier:
	ClassOrInterfaceModifier
	| NATIVE
	| SYNCHRONIZED
	| TRANSIENT
	| VOLATILE
	;

VariableModifier:
	FINAL
	| Annotation
	;

ClassDecl:
	CLASS IDENTIFIER ClassBody
	| CLASS IDENTIFIER TypeParams ClassBody
	| CLASS IDENTIFIER EXTENDS TypeType ClassBody
	| CLASS IDENTIFIER IMPLEMENTS TypeTypes ClassBody
	| CLASS IDENTIFIER TypeParams EXTENDS TypeType ClassBody
	| CLASS IDENTIFIER TypeParams IMPLEMENTS TypeTypes ClassBody
	| CLASS IDENTIFIER TypeParams EXTENDS TypeType IMPLEMENTS TypeTypes ClassBody
	| CLASS IDENTIFIER EXTENDS TypeType IMPLEMENTS TypeTypes ClassBody
	;

TypeParams:
	LT DotTypeParams GT
	;

DotTypeParams:
	TypeParam
	| DotTypeParams DOT TypeParam
	;

TypeParam:
	IDENTIFIER
	| IDENTIFIER EXTENDS TypeBound
	| AnnotationList IDENTIFIER
	| AnnotationList IDENTIFIER EXTENDS TypeBound
	;

TypeBound:
	TypeType
	| TypeBound AND TypeType
	;

PrimitiveType:
	BOOLEAN
	| CHAR
	| BYTE
	| SHORT
	| INT 
	| LONG
	| FLOAT
	| DOUBLE
	;

ClassOrInterfaceType:
	IDENTIFIER DotClassOrInterfaceTypeList
	| IDENTIFIER TypeArguments DotClassOrInterfaceTypeList
	;

DotIDTypeArguments:
	DOT IDENTIFIER
	| DOT IDENTIFIER TypeArguments
	;

DotClassOrInterfaceTypeList:
	DotClassOrInterfaceTypeList DotIDTypeArguments
	|
	;

TypeArguments:
	LT DotTypeArguments GT
	;

DotTypeArguments:
	TypeArgument
	| DotTypeArguments DOT TypeArgument
	;

TypeArgument:
	TypeType
	| QUESTION
	| QUESTION EXTENDS TypeType
	| QUESTION SUPER TypeType
	;

TypeType:
	Annotation ClassOrInterfaceType LRBrackListOptional
	| ClassOrInterfaceType LRBrackListOptional
	| Annotation PrimitiveType LRBrackListOptional
	| PrimitiveType LRBrackListOptional
	;

LRBrackListOptional:
	LRBrackList
	|
	;

LRBrackList:
	LBRACK RBRACK
	| LRBrackList LBRACK RBRACK
	;

TypeTypes:
	TypeType
	| TypeTypes TypeType
	;

AnnotationTypeDecl:
	_AT INTERFACE IDENTIFIER LPAREN BOOLEAN IDENTIFIER LPAREN RPAREN
	;

InterfaceDecl:
	INTERFACE IDENTIFIER LBRACE RBRACE
	;

EnumDecl:
	ENUM IDENTIFIER LBRACE RBRACE
	;

ClassBody:
	LBRACE RBRACE
	;
%%

// Hello

int main(){
	return yyparse();
}