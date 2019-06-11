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
	vector<MemberDeclNode*> *memberDecls;
	vector<ModifierType> *memberModifiers;
	ModifierType memberModifierType;
	vector<IdentifierNode*> *ids;
	vector<FormalParamNode*> *formalParamNodes;
	vector<BlockStatementNode*> *blockStatementNodes;
	vector<ExprNode*> *exprNodes;
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
%token <token> SINGLES ASSIGNS

%type <node> CompilationUnit PackageDecl  TypeDecl MemberDecl TypeType MethodBody
%type <node> ClassDecl ClassBodyDecl QualifiedName ClassBody  MethodDecl Literal
%type <node> VariableDeclaratorId Blcok BlockStatement Statement Expression Primary
%type <token> LRBrackList LRBrackListOptional
%type <importNodes> ImportDeclListOptional
%type <typeDeclNodes> TypeDeclListOptional
%type <memberModifiers> MemberModifierListOptional ClassOrInterfaceModifierListOptional
%type <memberModifierType> MemberModifier ClassOrInterfaceModifier
%type <memberDecls> ClassBodyDeclList
%type <formalParamNodes> FormalParams FormalParameterWithCommaList
%type <blockStatementNodes> BlockStatementList
%type <ids> IdentifierListWithDot
%type <exprNodes> ExpressionList

%left ASSIGNS
%left OR
%left AND
%left BITOR
%left CARET
%left BITAND
%left EQUAL NEQUAL
%left LT GT LTOE GTOE INSTANCEOF
%left LSHIFT RSHIFT URSHIFT
%left ADD SUB
%left MUL DIV MOD
%left SINGLES
%left LPAREN LBRACK DOT

%right ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN OR_ASSIGN XOR_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN URSHIFT_ASSIGN 
%right BANG TILDE INCRE DECRE
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
	ImportDeclListOptional ImportDecl { $1->push_back(dynamic_cast<ImportNode*>($2)); $$ = $1; }
	| { $$ = new vector<ImportNode*>; }
	;

ImportDecl:
	SingleImportDecl { $$ = new ImportNode(); }
	| TypeImportDecl { $$ = new ImportNode(); }
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
		$$ = new TypeDeclNode(CLASS, dynamic_cast<ClassDeclNode*>($2));
		$$->modifiers = $1;
	}
	| ClassOrInterfaceModifierListOptional InterfaceDecl { debugInfo("This is an Interface declaration"); }
	| SEMIC {$$ = NULL;}
	;

ClassDecl:
	CLASS IDENTIFIER ClassBody { 
		$$ = new ClassDeclNode(*$2, dynamic_cast<ClassBodyNode*>($3));
	}
	| CLASS IDENTIFIER IMPLEMENTS TypeList ClassBody {
		$$ = new ClassDeclNode(*$2, dynamic_cast<ClassBodyNode*>($5));
	}
	;

InterfaceDecl:
	INTERFACE IDENTIFIER InterfaceBody
	;

 /* ClassBody */
ClassBody:
	LBRACE RBRACE {
		$$ = new ClassBodyNode();
		$$->memberDecls = new vector<MemberDeclNode*>;
	}
	| LBRACE ClassBodyDeclList RBRACE {
		$$ = new ClassBodyNode();
		$$->memberDecls = $2;
	}
	;

ClassBodyDeclList:
	MemberDecl {
		$$ = new vector<MemberDeclNode*>;
		$$->push_back(dynamic_cast<MemberDecl*>($1));
	}
	| ClassBodyDeclList MemberDecl {
		$1->push_back(dynamic_cast<MemberDecl*>($2));
		$$ = $1;
	}
	;

ForControl:
	ForInitOptional SEMIC Expression SEMIC ExpressionList { debugInfo("three things all up"); }
	| ForInitOptional SEMIC SEMIC ExpressionList
	| ForInitOptional SEMIC Expression SEMIC
	| ForInitOptional SEMIC SEMIC
	;

ForInitOptional:
	LocalVariableDecl { debugInfo("do local variable decl"); }
	| ExpressionList
	|
	;

 /* Expressions */

MethodCallWithoutName:
	LPAREN ExpressionList RPAREN {
		$$ = new MethodCallParamsNode();
		dynamic_cast<MethodCallParamsNode*>($$)->exprs = $2;
	}
	| LPAREN RPAREN
	;

Expression:
	Primary {
		$$ = new ExprNode(PRIMARY_TYPE, dynamic_cast<PrimaryNode*>($1));
	}
	| IdentifierListWithDot { }
	| IdentifierListWithDot MethodCallWithoutName {
		ExprNode *tmp = new ExprNode(IDEN_DOT_METHOD);
		tmp->ids = $1;
		tmp->methodCallParams = $2;
		$$ = tmp;
	}
	| IDENTIFIER LBRACK Expression RBRACK
	| IdentifierListWithDot LBRACK Expression RBRACK
	| IDENTIFIER MethodCallWithoutName
	| Expression INCRE %prec INCRE { debugInfo("self increment"); }
	| Expression DECRE %prec INCRE { debugInfo("self decrement"); }
	| ADD Expression %prec SINGLES
	| SUB Expression %prec SINGLES
	| INCRE Expression %prec SINGLES
	| DECRE Expression %prec SINGLES
	| TILDE Expression %prec SINGLES
	| BANG Expression %prec SINGLES
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
	| Expression EQUAL Expression
	| Expression NEQUAL Expression
	| Expression BITAND Expression
	| Expression CARET Expression
	| Expression BITOR Expression
	| Expression AND Expression
	| Expression OR Expression
	| Expression AssignOperators Expression %prec ASSIGNS
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
	Expression {
		$$ = new vector<ExprNode*>;
		$$->push_back(dynamic_cast<ExprNode*>($1));
	}
	| ExpressionList COMMA Expression {
		$1->push_back(dynamic_cast<ExprNode*>($3));
		$$ = $1;
	}
	;

Primary:
	LPAREN Expression RPAREN {  }
	| THIS {  }
	| SUPER {  }
	| Literal { $$ = new PrimaryNode(PRIMARY_LITERAL, $1); }
	| IDENTIFIER { debugInfo($1); }
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
    Block { $$ = $1; }
    | SEMIC { $$ = NULL; }
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

MemberModifierListOptional:
	MemberModifierListOptional MemberModifier { $1->push_back($2); $$ = $1; }
	| { $$ = new vector<ModifierType>; }
	;

MemberModifier:
	PUBLIC { $$ = PUBLIC_TYPE; }
	| PROTECTED { $$ = PROTECTED_TYPE; }
	| PRIVATE { $$ = PRIVATE_TYPE; }
	| ABSTRACT { $$ = ABSTRACT_TYPE; }
	| DEFAULT { $$ = DEFAULT_VAL; }
	| STATIC { $$ = DEFAULT_VAL; }
	| STRICTFP { $$ = STRICTFP_TYPE; }
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
	LPAREN FormalParameterWithCommaList RPAREN { $$ = $2; }
	| LPAREN RPAREN { $$ = new vector<FormalParamNode*>; }
	;

FormalParameterWithCommaList:
	FormalParam {
		$$ = new vector<FormalParamNode*>;
		$$->push_back(dynamic_cast<FormalParamNode*>($1));
	}
	| FormalParameterWithCommaList COMMA FormalParam {
		$1->push_back(dynamic_cast<FormalParamNode*>($3));
		$$ = $1;
	}
	;


FormalParam:
	TypeType VariableDeclaratorId {
		$$ = new FormalParamNode(dynamic_cast<TypeTypeNode*>($1), dynamic_cast<VariableDeclaratorIdNode>($2));
	}
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

IdentifierListWithDot:
	IDENTIFIER DOT IDENTIFIER {
		$$ = new vector<IdentifierNode*>;
		$$->push_back(new IdentifierNode(*$1));
		$$->push_back(new IdentifierNode(*$3));
	}
	| IdentifierListWithDot DOT IDENTIFIER {
		$1->push_back(new IdentifierNode(*$3));
		$$ = $1;
	}
	;


TypeType:
	IdentifierListWithDot { } 
	| IDENTIFIER {
		$$ = new TypeTypeNode(NONPR_TYPE);
		$$->typeInfo = new vector<IdentifierNode*>;
		$$->typeInfo->push_back(new IdentifierNode(*$1));
	}
	| PrimitiveType LRBrackListOptional { }
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
	IDENTIFIER LRBrackList {
		$$ = new VariableDeclaratorIdNode($2, *$1);
	}
	| IDENTIFIER {
		$$ = new VariableDeclaratorIdNode(0, *$1);
	}
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
	LBRACE BlockStatementList RBRACE {
		$$ = new BlockNode();
		$$->stats = $2;
	}
	| LBRACE RBRACE {
		$$ = new BlockNode();
		$$->stats = new vector<BlockStatementNode*>;
	}
	;

BlockStatementList:
	BlockStatement {
		$$ = new vector<BlockStatementNode*>;
		$$->push_back(dynamic_cast<BlockStatement*>($1));
	}
	| BlockStatementList BlockStatement {
		$1->push_back(dynamic_cast<BlockStatement*>($2));
		$$ = $1;
	}
	;

BlockStatement:
	LocalVariableDecl SEMIC {
		$$ = NULL;
	}
	| Statement {
		$$ = new BlockStatementNode(dynamic_cast<StatementNode*>($1));
	}
	;

LocalVariableDecl:
	VariableModifierList TypeType VariableDeclarators
	| TypeType VariableDeclarators
	;


 /* TODO: finish (Statement) */
Statement:
	Block {  }
	| IF ParExpression Statement ELSE Statement { debugInfo("if () else ()"); }
	| IF ParExpression Statement {  }
	| FOR LPAREN ForControl RPAREN Statement { debugInfo("for statement"); }
	| RETURN Expression SEMIC {  }
	| RETURN SEMIC { debugInfo("return;"); }
	| SEMIC {  }
	| Expression SEMIC {
		$$ = new StatementNode(EXPR_TYPE, $1);
	}
	;


MemberDecl:
	MemberModifierListOptional MethodDecl {
		$$ = new MemberDeclNode($2);
		$$->modifiers = $1;
	}
	| MemberModifierListOptional FieldDecl { debugInfo("Reduced from FieldDecl"); }
	| MemberModifierListOptional ConstructorDecl { }
	| MemberModifierListOptional InterfaceDecl { }
	;

 /* about method */

MethodDecl:
	TypeType IDENTIFIER FormalParams THROWS QualifiedNameList MethodBody { }
	| VOID IDENTIFIER FormalParams THROWS QualifiedNameList MethodBody { }
	| TypeType IDENTIFIER FormalParams MethodBody { debugInfo("Reduced MethodDecl"); }
	| VOID IDENTIFIER FormalParams MethodBody {
		$$ = new MethodDeclNode(new TypeTypeNode(VOID_TYPE), *$2, dynamic_cast<BlockNode*>($4));
		$$->params = $3;
	}
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


ClassOrInterfaceModifierListOptional:
	ClassOrInterfaceModifierListOptional ClassOrInterfaceModifier {
		$1->push_back($2);
		$$ = $1;
	}
	| { $$ = new vector<ModifierType>; }
	;

ClassOrInterfaceModifier:
	PUBLIC { $$ = PUBLIC_TYPE; }
	| PRIVATE { $$ = PRIVATE_TYPE; }
	| PROTECTED { $$ = PROTECTED_TYPE; }
	| STATIC { $$ = STATIC_TYPE; }
	| ABSTRACT { $$ = ABSTRACT_TYPE; }
	| FINAL { $$ = FINAL_TYPE; }
	| STRICTFP { $$ = STRICTFP_TYPE; }
	;

Literal:
	DECIMAL_LITERAL { }
	| HEX_LITERAL { }
	| OCT_LITERAL { }
	| BINARY_LITERAL { }
	| FLOAT_LITERAL { }
	| HEXFLOAT_LITERAL { }
	| CHAR_LITERAL { }
	| STRING_LITERAL { $$ = new LiteralNode(STRING_LIT, *$1); }
	| TRUE_LITERAL { }
	| FALSE_LITERAL { }
	| NULL_LITERAL { }
	;


LRBrackListOptional:
	LRBrackListOptional LBRACK RBRACK
	|
	;

LRBrackList:
	LBRACK RBRACK { $$ = 1; }
	| LRBrackList LBRACK RBRACK { $$ = $2 + 1; }
	;

 /* End simple non terminals */

%%

// Hello
#include "codeGen/Genrator.hpp"
int main() {
	#define YYDEBUG 1
#ifdef YYDEBUG
  yydebug = 1;
#endif
	cout << yydebug << endl;
	yyparse();
	// rootNode->Visit();
	JContext *context = new JContext(rootNode);
	JasminFileGenrator *g = new JasminFileGenrator(context);
}