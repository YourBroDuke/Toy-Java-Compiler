%{
#include "node.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include "SymbolTable/SymbolTable.h"
extern int yylex();
extern char *yytext;
void yyerror(const char *s) {
	printf("Error: %s\n", s);
	printf("Error text: %s\n", yytext);
	exit(1);
}
using namespace std;
FileNode *rootNode = new FileNode();
SymbolTable *symbolTable = new SymbolTable();
// AddVarNode()
// AddMethodNode()
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
	ModifierType memberModifierType;
	PrimitiveTypeOrNot primitiveType;
	LocalVarType localVarType;
	vector<ImportNode*> *importNodes;
	vector<TypeDeclNode*> *typeDeclNodes;
	vector<MemberDeclNode*> *memberDecls;
	vector<ModifierType> *memberModifiers;
	vector<IdentifierNode*> *ids;
	vector<FormalParamNode*> *formalParamNodes;
	vector<BlockStatementNode*> *blockStatementNodes;
	vector<ExprNode*> *exprNodes;
	vector<VariableInitializerNode*> *arrayInitializer;
	vector<VariableDeclaratorNode*> *varDecls;
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
%type <node> ClassDecl QualifiedName ClassBody  MethodDecl Literal ImportDecl
%type <node> VariableDeclaratorId Block BlockStatement Statement Expression Primary
%type <node> MethodCallWithoutName FormalParam LocalVariableDecl VariableDeclarator VariableInitializer
%type <token> LRBrackList
%type <importNodes> ImportDeclListOptional
%type <typeDeclNodes> TypeDeclListOptional
%type <memberModifiers> MemberModifierListOptional ClassOrInterfaceModifierListOptional
%type <memberModifierType> MemberModifier ClassOrInterfaceModifier
%type <memberDecls> ClassBodyDeclList
%type <formalParamNodes> FormalParams FormalParameterWithCommaList
%type <blockStatementNodes> BlockStatementList
%type <arrayInitializer> ArrayInitializer VariableInitializerListWithComma
%type <ids> IdentifierListWithDot
%type <exprNodes> ExpressionList
%type <primitiveType> PrimitiveType
%type <localVarType> VariableModifier VariableModifierList
%type <varDecls> VariableDeclarators

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

%nonassoc IFX
%nonassoc ELSE
/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */


/* Operator precedence for mathematical operators */

%start CompilationUnit

%%

 /* done */
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
 /* done */
PackageDecl:
	PACKAGE QualifiedName SEMIC { $$ = new PackageNode(dynamic_cast<QualifiedNameNode*>($2)); }
	;
 /* done */
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

 /* done */
TypeDeclListOptional:
	TypeDeclListOptional TypeDecl {
		$1->push_back(dynamic_cast<TypeDeclNode*>($2));
		$$ = $1;
	}
	| {$$ = new vector<TypeDeclNode*>;}
	;

 /* almost done */
TypeDecl:
	ClassOrInterfaceModifierListOptional ClassDecl {
		$$ = new TypeDeclNode(CLASS_TYPE, dynamic_cast<ClassDeclNode*>($2));
		dynamic_cast<TypeDeclNode*>($$)->modifiers = $1;
	}
	| ClassOrInterfaceModifierListOptional InterfaceDecl { debugInfo("This is an Interface declaration"); }
	| SEMIC {$$ = NULL;}
	;

 /* done */
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

 /* done */
ClassBody:
	LBRACE RBRACE {
		$$ = new ClassBodyNode();
		dynamic_cast<ClassBodyNode*>($$)->memberDecls = new vector<MemberDeclNode*>;
	}
	| LBRACE ClassBodyDeclList RBRACE {
		$$ = new ClassBodyNode();
		dynamic_cast<ClassBodyNode*>($$)->memberDecls = $2;
	}
	;

 /* done */
ClassBodyDeclList:
	MemberDecl {
		$$ = new vector<MemberDeclNode*>;
		$$->push_back(dynamic_cast<MemberDeclNode*>($1));
	}
	| ClassBodyDeclList MemberDecl {
		$1->push_back(dynamic_cast<MemberDeclNode*>($2));
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
	| LPAREN RPAREN {
		$$ = new MethodCallParamsNode();
		dynamic_cast<MethodCallParamsNode*>($$)->exprs = new vector<ExprNode*>;
	}
	;

Expression:
	Primary {
		$$ = new ExprNode(PRIMARY_TYPE, dynamic_cast<PrimaryNode*>($1));
	}
	| IdentifierListWithDot { }
	| IdentifierListWithDot MethodCallWithoutName {
		ExprNode *tmp = new ExprNode(IDEN_DOT_METHOD);
		tmp->ids = $1;
		tmp->methodCallParams = dynamic_cast<MethodCallParamsNode*>($2);
		$$ = tmp;
	}
	| IDENTIFIER LBRACK Expression RBRACK { }
	| IdentifierListWithDot LBRACK Expression RBRACK { }
	| IDENTIFIER MethodCallWithoutName {
		ExprNode *tmp = new ExprNode(IDEN_METHOD);
		tmp->ids = new vector<IdentifierNode*>;
		tmp->ids->push_back(new IdentifierNode(*$1));
		tmp->methodCallParams = dynamic_cast<MethodCallParamsNode*>($2);
		$$ = tmp;
	}
	| Expression INCRE %prec INCRE {
		$$ = new ExprNode(POST_INCRE, dynamic_cast<ExprNode*>($1));
	}
	| Expression DECRE %prec INCRE {
		$$ = new ExprNode(POST_DECRE, dynamic_cast<ExprNode*>($1));
	}
	| ADD Expression %prec SINGLES {
		$$ = new ExprNode(POS_EXPR, dynamic_cast<ExprNode*>($2));
	}
	| SUB Expression %prec SINGLES {
		$$ = new ExprNode(NEG_EXPR, dynamic_cast<ExprNode*>($2));
	}
	| INCRE Expression %prec SINGLES {
		$$ = new ExprNode(PRE_INCRE, dynamic_cast<ExprNode*>($2));
	}
	| DECRE Expression %prec SINGLES {
		$$ = new ExprNode(PRE_DECRE, dynamic_cast<ExprNode*>($2));
	}
	| TILDE Expression %prec SINGLES {
		$$ = new ExprNode(TILDE_EXPR, dynamic_cast<ExprNode*>($2));
	}
	| BANG Expression %prec SINGLES {
		$$ = new ExprNode(BANG_EXPR, dynamic_cast<ExprNode*>($2));
	}
	| Expression MUL Expression {
		$$ = new ExprNode(OP_MUL, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression DIV Expression {
		$$ = new ExprNode(OP_DIV, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression MOD Expression {
		$$ = new ExprNode(OP_MOD, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression ADD Expression {
		$$ = new ExprNode(OP_ADD, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression SUB Expression {
		$$ = new ExprNode(OP_SUB, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression LSHIFT Expression {
		$$ = new ExprNode(OP_LSHIFT, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression RSHIFT Expression {
		$$ = new ExprNode(OP_RSHIFT, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression URSHIFT Expression {
		$$ = new ExprNode(OP_URSHIFT, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression LT Expression {
		$$ = new ExprNode(OP_LT, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression GT Expression {
		$$ = new ExprNode(OP_GT, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression LTOE Expression {
		$$ = new ExprNode(OP_LTOE, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression GTOE Expression {
		$$ = new ExprNode(OP_GTOE, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression EQUAL Expression {
		$$ = new ExprNode(OP_EQ, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression NEQUAL Expression {
		$$ = new ExprNode(OP_NEQ, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression BITAND Expression {
		$$ = new ExprNode(OP_BAND, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression CARET Expression {
		$$ = new ExprNode(OP_CARET, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression BITOR Expression {
		$$ = new ExprNode(OP_BOR, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression AND Expression {
		$$ = new ExprNode(OP_AND, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression OR Expression {
		$$ = new ExprNode(OP_OR, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression ASSIGN Expression {
		$$ = new ExprNode(OP_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression ADD_ASSIGN Expression {
		$$ = new ExprNode(OP_ADD_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression SUB_ASSIGN Expression {
		$$ = new ExprNode(OP_SUB_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression MUL_ASSIGN Expression {
		$$ = new ExprNode(OP_MUL_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression DIV_ASSIGN Expression {
		$$ = new ExprNode(OP_DIV_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression MOD_ASSIGN Expression {
		$$ = new ExprNode(OP_MOD_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression AND_ASSIGN Expression {
		$$ = new ExprNode(OP_AND_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression OR_ASSIGN Expression {
		$$ = new ExprNode(OP_OR_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression XOR_ASSIGN Expression {
		$$ = new ExprNode(OP_XOR_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression RSHIFT_ASSIGN Expression {
		$$ = new ExprNode(OP_RSHIFT_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression URSHIFT_ASSIGN Expression {
		$$ = new ExprNode(OP_URSHIFT_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
	| Expression LSHIFT_ASSIGN Expression {
		$$ = new ExprNode(OP_LSHIFT_ASN, dynamic_cast<ExprNode*>($1), dynamic_cast<ExprNode*>($3));
	}
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
	| Literal { $$ = new PrimaryNode(PRIMARY_LITERAL, dynamic_cast<LiteralNode*>$1); }
	| IDENTIFIER { $$ = new PrimaryNode(PRIMARY_IDEN, *$1); }
	;


VariableModifier:
	FINAL {
		$$ = FINAL_TYPE_L;
	}
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
	InterfaceMethodModifierListOptional TypeTypeOrVoid IDENTIFIER FormalParams LRBrackList THROWS QualifiedNameList MethodBody
	| InterfaceMethodModifierListOptional TypeTypeOrVoid IDENTIFIER FormalParams LRBrackList MethodBody
	| InterfaceMethodModifierListOptional TypeTypeOrVoid IDENTIFIER FormalParams THROWS QualifiedNameList MethodBody
	| InterfaceMethodModifierListOptional TypeTypeOrVoid IDENTIFIER FormalParams MethodBody
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
	| DEFAULT { $$ = DEFAULT_TYPE; }
	| STATIC { $$ = STATIC_TYPE; }
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
		$$ = new FormalParamNode(dynamic_cast<TypeTypeNode*>($1), dynamic_cast<VariableDeclaratorIdNode*>($2));
	}
	;

 /* ---- End Params ----*/

QualifiedNameList:
	QualifiedName
	| QualifiedNameList COMMA QualifiedName
	;

VariableModifierList:
	VariableModifier { $$ = $1; }
	| VariableModifierList VariableModifier { $$ = $2; }
	;

PrimitiveType:
	BOOLEAN { $$ = BOOLEAN_TYPE; }
	| CHAR { $$ = CHAR_TYPE; }
	| BYTE { $$ = BYTE_TYPE; }
	| SHORT { $$ = SHORT_TYPE; }
	| INT { $$ = INT_TYPE; }
	| LONG { $$ = LONG_TYPE; }
	| FLOAT { $$ = FLOAT_TYPE; }
	| DOUBLE { $$ = DOUBLE_TYPE; }
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
	IdentifierListWithDot {
		TypeTypeNode* tmp = new TypeTypeNode(NONPR_TYPE);
		tmp->typeInfo = $1;
		tmp->arrayDim = 0;
		$$ = tmp;
	}
	| IDENTIFIER {
		TypeTypeNode* tmp = new TypeTypeNode(NONPR_TYPE);
		tmp->typeInfo = new vector<IdentifierNode*>;
		tmp->typeInfo->push_back(new IdentifierNode(*$1));
		tmp->arrayDim = 0;
		$$ = tmp;
	}
	| IDENTIFIER LRBrackList {
		TypeTypeNode* tmp = new TypeTypeNode(NONPR_TYPE);
		tmp->typeInfo = new vector<IdentifierNode*>;
		tmp->typeInfo->push_back(new IdentifierNode(*$1));
		tmp->arrayDim = $2;
		$$ = tmp;
	}
	| PrimitiveType {
		TypeTypeNode *tmp = new TypeTypeNode($1);
		tmp->typeInfo = new vector<IdentifierNode*>;
		tmp->arrayDim = 0;
		$$ = tmp;
	}
	| PrimitiveType LRBrackList {
		TypeTypeNode *tmp = new TypeTypeNode($1);
		tmp->typeInfo = new vector<IdentifierNode*>;
		tmp->arrayDim = $2;
		$$ = tmp;
	}
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
	VariableDeclarator {
		$$ = new vector<VariableDeclaratorNode*>;
		$$->push_back(dynamic_cast<VariableDeclaratorNode*>($1));
	}
	| VariableDeclarators COMMA VariableDeclarator {
		$1->push_back(dynamic_cast<VariableDeclaratorNode*>($3));
		$$ = $1;
	}
	;

VariableDeclarator:
	VariableDeclaratorId {
		$$ = new VariableDeclaratorNode(dynamic_cast<VariableDeclaratorIdNode*>($1));
	}
	| VariableDeclaratorId ASSIGN VariableInitializer {
		$$ = new VariableDeclaratorNode(dynamic_cast<VariableDeclaratorIdNode*>($1), dynamic_cast<VariableInitializerNode*>($3));
	}
	;

VariableDeclaratorId:
	IDENTIFIER {
		$$ = new VariableDeclaratorIdNode(0, *$1);
	}
	;

VariableInitializer:
	ArrayInitializer {
		$$ = new VariableInitializerNode(0, $1); // it is not single expr but an array
	}
	| Expression {
		$$ = new VariableInitializerNode(1, dynamic_cast<ExprNode*>($1)); // it is a single expr
	}
	;
VariableInitializerListWithComma:
	VariableInitializer {
		$$ = new vector<VariableInitializerNode*>;
		$$->push_back(dynamic_cast<VariableInitializerNode*>($1));
	}
	| VariableInitializerListWithComma COMMA VariableInitializer {
		$1->push_back(dynamic_cast<VariableInitializerNode*>($3));
		$$ = $1;
	}
	;

ArrayInitializer:
	LBRACE VariableInitializerListWithComma COMMA RBRACE {
		$$ = $2;
	}
	| LBRACE VariableInitializerListWithComma RBRACE {
		$$ = $2;
	}
	| LBRACE RBRACE {
		$$ = new vector<VariableInitializerNode*>;
	}
	;

 /* Statements / Blocks */
 /* Finish Block */
 /* BlockStatement */
 /* (Statement) */
Block:
	LBRACE BlockStatementList RBRACE {
		$$ = new BlockNode();
		dynamic_cast<BlockNode*>($$)->stats = $2;
	}
	| LBRACE RBRACE {
		$$ = new BlockNode();
		dynamic_cast<BlockNode*>($$)->stats = new vector<BlockStatementNode*>;
	}
	;

BlockStatementList:
	BlockStatement {
		$$ = new vector<BlockStatementNode*>;
		$$->push_back(dynamic_cast<BlockStatementNode*>($1));
	}
	| BlockStatementList BlockStatement {
		$1->push_back(dynamic_cast<BlockStatementNode*>($2));
		$$ = $1;
	}
	;

BlockStatement:
	LocalVariableDecl SEMIC {
		cout << "+\n+\n+\n" << $1 << "\n-\n-\n-\n";
		$$ = new BlockStatementNode(1, dynamic_cast<Statement*>($1));
	}
	| Statement {
		$$ = new BlockStatementNode(0, dynamic_cast<Statement*>($1));	// NOT local variable decl
	}
	;

LocalVariableDecl:
	VariableModifierList TypeType VariableDeclarators {
		$$ = new LocalVariableDeclNode(1, dynamic_cast<TypeTypeNode*>($2)); // 1 - FINAL
		dynamic_cast<LocalVariableDeclNode*>($$)->decls = $3;
		cout << "-\n-\n-\n" << $$ << "\n-\n-\n-\n";
	}
	| TypeType VariableDeclarators {
		$$ = new LocalVariableDeclNode(0, dynamic_cast<TypeTypeNode*>($1));	// 0 - NOT FINAL
		dynamic_cast<LocalVariableDeclNode*>($$)->decls = $2;
		cout << "-\n-\n-\n" << $$ << "\n-\n-\n-\n";
	}
	;


 /* TODO: finish (Statement) */
Statement:
	Block {  }
	| IF LPAREN Expression RPAREN Statement ELSE Statement { debugInfo("if () else ()"); }
	| IF LPAREN Expression RPAREN Statement %prec IFX {  }
	| FOR LPAREN ForControl RPAREN Statement { debugInfo("for statement"); }
	| RETURN Expression SEMIC {
		$$ = new StatementNode(RETURN_TYPE, dynamic_cast<ExprNode*>($2));
	}
	| RETURN SEMIC {
		$$ = new StatementNode(RETURN_NONE_TYPE);
	}
	| SEMIC {  }
	| Expression SEMIC {
		$$ = new StatementNode(EXPR_TYPE, dynamic_cast<ExprNode*>($1));
	}
	;


MemberDecl:
	MemberModifierListOptional MethodDecl {
		$$ = new MemberDeclNode($2);
		dynamic_cast<MemberDeclNode*>($$)->modifiers = $1;
	}
	| MemberModifierListOptional FieldDecl { debugInfo("Reduced from FieldDecl"); }
	| MemberModifierListOptional ConstructorDecl { }
	| MemberModifierListOptional InterfaceDecl { }
	;

 /* about method */

MethodDecl:
	TypeType IDENTIFIER FormalParams THROWS QualifiedNameList MethodBody { }
	| VOID IDENTIFIER FormalParams THROWS QualifiedNameList MethodBody { }
	| TypeType IDENTIFIER FormalParams MethodBody {
		$$ = new MethodDeclNode(dynamic_cast<TypeTypeNode*>($1), *$2, dynamic_cast<BlockNode*>($4));
		dynamic_cast<MethodDeclNode*>($$)->params = $3;
	}
	| VOID IDENTIFIER FormalParams MethodBody {
		$$ = new MethodDeclNode(new TypeTypeNode(VOID_TYPE), *$2, dynamic_cast<BlockNode*>($4));
		dynamic_cast<MethodDeclNode*>($$)->params = $3;
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
	DECIMAL_LITERAL { $$ = new LiteralNode(INTEGER_LIT, (int64_t)atoi($1->c_str())); }
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

LRBrackList:
	LBRACK RBRACK { $$ = 1; }
	| LRBrackList LBRACK RBRACK { $$ = $2 + 1; }
	;

 /* End simple non terminals */

%%

// Hello
#include "codeGen/Generator.hpp"

int main() {
#define YYDEBUG 1
#ifdef YYDEBUG
  yydebug = 1;
#endif
	cout << yydebug << endl;
	yyparse();
	rootNode->Visit();
	// JContext *context = new JContext(rootNode);
	// JasminFileGenerator *g = new JasminFileGenerator(context);
	// debugInfo("start generating...");
	// g->Generate();
	// cout << endl << endl << "The Target code:" << endl << endl;
	// g->WriteTo(cout);
}