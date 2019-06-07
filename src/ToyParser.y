%{
#include "node.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
extern int yylex();
extern char *yytext;
void yyerror(const char *s) {
	printf("Error: %s\n", s);
	printf("Error text: %s\n", yytext);
	exit(1);
}
using namespace std;
FileNode *rootNode = new FileNode();

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
	Node *node;
	vector<ImportNode*> *importNodes;
	vector<TypeDeclNode*> *typeDeclNodes;
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
%token <token> QUESTION DCOLON COLON LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK
%token <token> DOT COMMA SEMIC BANG LT GT BITAND BITOR CARET ADD SUB MUL DIV
%token <token> MOD EQUAL NEQUAL LTOE GTOE AND OR LSHIFT RSHIFT INCRE DEFAULT_VAL ARROW
%token <token> DECRE ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN AND_ASSIGN
%token <token> OR_ASSIGN XOR_ASSIGN MOD_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN
%token <token> URSHIFT URSHIFT_ASSIGN NULL_LITERAL TRUE_LITERAL FALSE_LITERAL

%type <node> CompilationUnit PackageDecl  TypeDecl
%type <node> ClassDecl ClassBodyDecl QualifiedName 
%type <importNodes> ImportDeclListOptional
%type <typeDeclNodes> TypeDeclListOptional
/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */


/* Operator precedence for mathematical operators */

%start CompilationUnit

%%

CompilationUnit:
	PackageDecl ImportDeclListOptional TypeDeclListOptional {
		rootNode->packageNode = dynamic_cast<PackageNode*>($1);
		rootNode->importNodes = $2;
		rootNode->typeDeclNodes = $3;
	}
	| ImportDeclListOptional TypeDeclListOptional {
		rootNode->packageNode = NULL;
		rootNode->importNodes = $1;
		rootNode->typeDeclNodes = $2;
	}
	;

PackageDecl:
	PACKAGE QualifiedName SEMIC { $$ = new PackageNode(dynamic_cast<QualifiedNameNode*>($2)); }
	;

ImportDeclListOptional:
	ImportDeclListOptional ImportDecl {  }
	| { $$ = new vector<ImportNode*>; }
	;

ImportDecl:
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

 /*  TypeDecl */
TypeDeclListOptional:
	TypeDeclListOptional TypeDecl { 
		$1->push_back(dynamic_cast<TypeDeclNode*>($2));
		$$ = $1;
	}
	| {$$ = new vector<TypeDeclNode*>;}
	;

TypeDecl:
	ClassOrInterfaceModifierListOptional ClassDecl { 
		$$ = new TypeDeclNode(Class, dynamic_cast<ClassDeclNode*>($2));
	}
	| ClassOrInterfaceModifierListOptional InterfaceDecl { debugInfo("This is an Interface declaration"); }
	| SEMIC {$$ = NULL;}
	;

ClassDecl:
	CLASS IDENTIFIER ClassBody { 
		$$ = new ClassDeclNode(*$2, NULL);
	 }
	| CLASS IDENTIFIER IMPLEMENTS TypeList ClassBody
	;

InterfaceDecl:
	INTERFACE IDENTIFIER InterfaceBody
	;

 /* ClassBody */
ClassBody:
	LBRACE RBRACE
	| LBRACE ClassBodyDeclList RBRACE { debugInfo("Reduced ClassBody"); }
	;

ClassBodyDeclList:
	ClassBodyDecl { debugInfo("the last classbodydecl"); }
	| ClassBodyDeclList ClassBodyDecl { debugInfo("create one classbodydecl"); }
	;

ClassBodyDecl:
	ModifierList MemberDecl { debugInfo("Reduced ClassBodyDecl"); }
	| MemberDecl
	;

ForControl:
	EnhancedForControl
	| ForInitOptional SEMIC Expression SEMIC ExpressionList { debugInfo("three things all up"); }
	| ForInitOptional SEMIC SEMIC ExpressionList
	| ForInitOptional SEMIC Expression SEMIC
	| ForInitOptional SEMIC SEMIC
	;

EnhancedForControl:
	VariableModifierList TypeType VariableDeclaratorId COLON Expression
	| TypeType VariableDeclaratorId COLON Expression
	;

ForInitOptional:
	ForInit
	|
	;

ForInit:
	LocalVariableDecl { debugInfo("do local variable decl"); }
	| ExpressionList
	;

 /* Expressions */

MethodCall:
	IDENTIFIER LPAREN ExpressionList RPAREN
	| IDENTIFIER LPAREN RPAREN
	;

Expression:
	Primary
	| Expression DOT IDENTIFIER { debugInfo("."); debugInfo($3); }
	| Expression DOT MethodCall { debugInfo("."); debugInfo("methodCall"); }
	| Expression LBRACK Expression RBRACK
	| MethodCall
	| Expression INCRE { debugInfo("self increment"); }
	| Expression DECRE { debugInfo("self decrement"); }
	| ADD Expression
	| SUB Expression
	| INCRE Expression
	| DECRE Expression
	| TILDE Expression
	| BANG Expression
	| Expression MUL Expression
	| Expression DIV Expression
	| Expression MOD Expression
	| Expression ADD Expression { debugInfo("add up"); }
	| Expression SUB Expression
	| Expression LSHIFT Expression
	| Expression RSHIFT Expression
	| Expression URSHIFT Expression
	| Expression LT Expression { debugInfo("lessthan expression"); }
	| Expression GT Expression
	| Expression LTOE Expression
	| Expression GTOE Expression
	| Expression INSTANCEOF TypeType
	| Expression EQUAL Expression
	| Expression NEQUAL Expression
	| Expression BITAND Expression
	| Expression CARET Expression
	| Expression BITOR Expression
	| Expression AND Expression
	| Expression OR Expression
	| Expression AssignOperators Expression
	;

AssignOperators:
	ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| AND_ASSIGN
	| OR_ASSIGN
	| XOR_ASSIGN
	| RSHIFT_ASSIGN
	| URSHIFT_ASSIGN
	| LSHIFT_ASSIGN
	;


ParExpression:
	LPAREN Expression RPAREN
	;

ExpressionList:
	Expression
	| ExpressionList COMMA Expression
	;

Primary:
	LPAREN Expression RPAREN
	| THIS
	| SUPER
	| Literal
	| IDENTIFIER { debugInfo($1); }
	| TypeTypeOrVoid DOT CLASS
	;


ModifierList:
	Modifier { debugInfo("Reduced ModifierList"); }
	| ModifierList Modifier { debugInfo("Reduced ModifierList"); }
	;

VariableModifier:
	FINAL
	;

/* We use rule this even for void methods which cannot have [] after parameters.
   This simplifies grammar and we can consider void to be a type, which
   renders the [] matching as a context-sensitive issue or a semantic check
   for invalid return type after parsing.
 */

MethodBody:
    Block { debugInfo("it has something in methodbody"); }
    | COMMA
    ;



InterfaceBody:
	LPAREN RPAREN
	| LPAREN InterfaceBodyDeclList RPAREN
	;

InterfaceBodyDeclList:
	InterfaceBodyDecl
	| InterfaceBodyDeclList InterfaceBodyDecl
	;

FieldDecl:
	TypeType VariableDeclarators SEMIC { debugInfo("variable decl in class"); }
	;

InterfaceBodyDecl:
	InterfaceMemberDecl
	| ModifierList InterfaceMemberDecl
	| SEMIC
	;

InterfaceMemberDecl:
    InterfaceMethodDecl
	| InterfaceDecl
	| ClassDecl
	;


InterfaceMethodDecl:
	InterfaceMethodModifierListOptional TypeTypeOrVoid IDENTIFIER FormalParams LRBrackListOptional THROWS QualifiedNameList MethodBody
	| InterfaceMethodModifierListOptional TypeTypeOrVoid IDENTIFIER FormalParams LRBrackListOptional MethodBody
	;

InterfaceMethodModifierListOptional:
	InterfaceMethodModifierListOptional InterfaceMethodModifier
	|
	;

InterfaceMethodModifier:
    PUBLIC
	| ABSTRACT
	| DEFAULT
	| STATIC
	| STRICTFP
	;

 /* About params */

FormalParams:
	LPAREN FormalParameterWithCommaList RPAREN { debugInfo("params"); }
	| LPAREN RPAREN
	;

FormalParameterWithCommaList:
	FormalParam
	| FormalParameterWithCommaList COMMA FormalParam
	;


FormalParam:
	TypeType VariableDeclaratorId
	;

 /* ---- End Params ----*/

QualifiedNameList:
	QualifiedName
	| QualifiedNameList COMMA QualifiedName
	;

VariableModifierList:
	VariableModifier
	| VariableModifierList VariableModifier
	;

PrimitiveType:
	BOOLEAN
	| CHAR
	| BYTE
	| SHORT
	| INT { debugInfo("int"); }
	| LONG
	| FLOAT
	| DOUBLE
	;

ClassOrInterfaceType:
	IDENTIFIER DotClassOrInterfaceTypeList
	;

DotClassOrInterfaceTypeList:
	DotClassOrInterfaceTypeList DOT IDENTIFIER
	|
	;


TypeType:
	ClassOrInterfaceType LRBrackListOptional
	| PrimitiveType LRBrackListOptional
	;

TypeTypeOrVoid:
	TypeType { debugInfo("Reduced TypeTypeOrVoid"); }
	| VOID { debugInfo("Reduced TypeTypeOrVoid"); }
	;

ConstructorDecl:
	IDENTIFIER FormalParams THROWS QualifiedNameList Block
	| IDENTIFIER FormalParams Block
	;


TypeList:
	TypeType
	| TypeList COMMA TypeType
	;


VariableDeclarators:
	VariableDeclarator
	| VariableDeclarators COMMA VariableDeclarator
	;

VariableDeclarator:
	VariableDeclaratorId
	| VariableDeclaratorId ASSIGN VariableInitializer
	;

VariableDeclaratorId:
	IDENTIFIER LRBrackList
	| IDENTIFIER
	;

VariableInitializer:
	ArrayInitializer
	| Expression
	;
VariableInitializerListWithComma:
	VariableInitializer
	| VariableInitializerListWithComma COMMA VariableInitializer
	;

ArrayInitializer:
	LBRACE VariableInitializerListWithComma COMMA RBRACE
	| LBRACE VariableInitializerListWithComma RBRACE
	| LBRACE RBRACE
	;

 /* Statements / Blocks */
 /* Finish Block */
 /* BlockStatement */
 /* (Statement) */
Block:
	LBRACE BlockStatementList RBRACE { debugInfo("it has something in block"); }
	| LBRACE RBRACE
	;

BlockStatementList:
	BlockStatement { debugInfo("last blockstatement"); }
	| BlockStatementList BlockStatement { debugInfo("create one blockstatement"); }
	;

BlockStatement:
	LocalVariableDecl SEMIC { debugInfo("decl variable in method"); }
	| Statement { debugInfo("this is a statement"); }
	;

LocalVariableDecl:
	VariableModifierList TypeType VariableDeclarators
	| TypeType VariableDeclarators
	;


 /* TODO: finish (Statement) */
Statement:
	Block
	| IF ParExpression Statement ELSE Statement { debugInfo("if () else ()"); }
	| IF ParExpression Statement
	| FOR LPAREN ForControl RPAREN Statement { debugInfo("for statement"); }
	| RETURN Expression SEMIC
	| RETURN SEMIC { debugInfo("return;"); }
	| SEMIC
	| Expression SEMIC
	;


MemberDecl:
	MethodDecl { debugInfo("Reduced MemberDecl"); }
	| FieldDecl { debugInfo("Reduced from FieldDecl"); }
	| ConstructorDecl
	| InterfaceDecl
	;

 /* about method */

MethodDecl:
	TypeType IDENTIFIER FormalParams THROWS QualifiedNameList MethodBody
	| VOID IDENTIFIER FormalParams THROWS QualifiedNameList MethodBody
	| TypeType IDENTIFIER FormalParams MethodBody { debugInfo("Reduced MethodDecl"); }
	| VOID IDENTIFIER FormalParams MethodBody { debugInfo("Reduced MethodDecl"); }
	;


 /* Some lower Non-terminals */

QualifiedName:
	IDENTIFIER { 
		$$ = new QualifiedNameNode();
		dynamic_cast<QualifiedNameNode*>($$)->identifiers->push_back(new IdentifierNode(*$1));
	}
	| QualifiedName DOT IDENTIFIER { 
		dynamic_cast<QualifiedNameNode*>($1)->identifiers->push_back(new IdentifierNode(*$3));
		$$ = $1;
	 }
	;



Modifier:
	ClassOrInterfaceModifier
	| NATIVE
	| SYNCHRONIZED
	| TRANSIENT
	| VOLATILE
	;

ClassOrInterfaceModifierListOptional:
	ClassOrInterfaceModifierList { debugInfo("Reduced ClassOrInterfaceModifierListOptional"); }
	|
	;

ClassOrInterfaceModifierList:
	ClassOrInterfaceModifier
	| ClassOrInterfaceModifierList ClassOrInterfaceModifier
	;

ClassOrInterfaceModifier:
	PUBLIC { debugInfo("public"); }
	| PRIVATE { debugInfo("private"); }
	| PROTECTED { debugInfo("protected"); }
	| STATIC { debugInfo("static"); }
	| ABSTRACT { debugInfo("abstract"); }
	| FINAL { debugInfo("final"); }
	| STRICTFP { debugInfo("strictfp"); }
	;

Literal:
	IntegerLiteral
	| FloatLiteral
	| CHAR_LITERAL
	| STRING_LITERAL
	| TRUE_LITERAL
	| FALSE_LITERAL
	| NULL_LITERAL
	;

IntegerLiteral:
	DECIMAL_LITERAL
	| HEX_LITERAL
	| OCT_LITERAL
	| BINARY_LITERAL
	;

FloatLiteral:
	FLOAT_LITERAL
	| HEXFLOAT_LITERAL
	;


LRBrackListOptional:
	LRBrackList
	|
	;

LRBrackList:
	LBRACK RBRACK
	| LRBrackList LBRACK RBRACK
	;

 /* End simple non terminals */

%%

// Hello
int main(){
	#define YYDEBUG 1
#ifdef YYDEBUG
  yydebug = 1;
#endif
	cout << yydebug << endl;
	yyparse();
	rootNode->Visit();
}