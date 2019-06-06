%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#define YYDEBUG 1
extern int yylex();
extern char *yytext;
void yyerror(const char *s) {
	printf("Error: %s\n", s);
	printf("Error text: %s\n", yytext);
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
%token <token> QUESTION DCOLON COLON LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK
%token <token> DOT COMMA SEMIC BANG LT GT BITAND BITOR CARET ADD SUB MUL DIV
%token <token> MOD EQUAL NEQUAL LTOE GTOE AND OR LSHIFT RSHIFT INCRE DEFAULT_VAL ARROW
%token <token> DECRE ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN AND_ASSIGN
%token <token> OR_ASSIGN XOR_ASSIGN MOD_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN
%token <token> URSHIFT URSHIFT_ASSIGN NULL_LITERAL TRUE_LITERAL FALSE_LITERAL

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */


/* Operator precedence for mathematical operators */

%start CompilationUnit

%%

CompilationUnit:
	PackageDecl ImportDeclListOptional TypeDeclListOptional
	| ImportDeclListOptional TypeDeclListOptional
	;

PackageDecl:
	PACKAGE QualifiedName SEMIC { debugInfo("package"); debugInfo(";"); }
	| AnnotationList PACKAGE QualifiedName SEMIC { debugInfo("package"); debugInfo(";"); }
	;

 /* ImportDecl TypeDecl */

QualifiedName:
	IDENTIFIER { debugInfo($1); debugInfo("haha"); }
	| QualifiedName DOT IDENTIFIER { debugInfo("."); debugInfo($3); debugInfo("haha"); }
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

AnnotationListOptional:
	AnnotationList
	|
	;

AnnotationList:
	Annotation
	| AnnotationList Annotation
	;

Annotation:
	_AT QualifiedName { debugInfo("@"); }
	| _AT QualifiedName LPAREN AnnotationValue RPAREN
	;

AnnotationValue:
	ElementValuePairs
	| ElementValue
	|
	;

ElementValuePairs:
	ElementValuePair
	| ElementValuePairs COMMA ElementValuePair
	;

ElementValuePair:
	IDENTIFIER ASSIGN ElementValue
	;

ElementValue:
	Expression
	| Annotation
	| ElementValueArrayInitializer
	;

 /* Switch For */

SwitchBlockStatementGroupListOptional:
	SwitchBlockStatementGroupListOptional SwitchBlockStatementGroup
	|
	;

SwitchBlockStatementGroup:
	SwitchLabelList BlockStatementList
	;

SwitchLabelListOptional:
	SwitchLabelList
	|
	;

SwitchLabelList:
	SwitchLabel
	| SwitchLabelList SwitchLabel
	;

SwitchLabel:
	CASE Expression COLON
	| CASE IDENTIFIER COLON
	| DEFAULT COLON
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
	| THIS LPAREN ExpressionList RPAREN
	| THIS LPAREN RPAREN
	| SUPER LPAREN ExpressionList RPAREN
	| SUPER LPAREN LPAREN
	;

Expression:
	Primary
	| Expression DOT IDENTIFIER { debugInfo("."); debugInfo($3); }
	| Expression DOT MethodCall
	| Expression DOT THIS
	| Expression DOT NEW NonWildcardTypeArguments InnerCreator
	| Expression DOT NEW InnerCreator
	| Expression DOT SUPER SuperSuffix
	| Expression DOT ExplicitGenericInvocation
	| Expression LBRACK Expression RBRACK
	| MethodCall
	| NEW Creator
	| LPAREN TypeType RPAREN Expression
	| Expression INCRE { debugInfo("self increment"); }
	| Expression DECRE
	| ADD Expression
	| SUB Expression
	| INCRE Expression
	| DECRE Expression
	| TILDE Expression
	| BANG Expression
	| Expression MUL Expression
	| Expression DIV Expression
	| Expression MOD Expression
	| Expression ADD Expression
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
	| Expression QUESTION Expression COLON Expression
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

ExpressionListWithBrack:
	LBRACK Expression RBRACK
	| ExpressionListWithBrack LBRACK Expression RBRACK
	;

Primary:
	LPAREN Expression RPAREN
	| THIS
	| SUPER
	| Literal
	| IDENTIFIER { debugInfo($1); }
	| TypeTypeOrVoid DOT CLASS
	| NonWildcardTypeArguments ExplicitGenericInvocationSuffix
	| NonWildcardTypeArguments THIS Arguments
	;

Creator:
	NonWildcardTypeArguments CreatedName ClassCreatorRest
	| CreatedName ArrayCreatorRest
	| CreatedName ClassCreatorRest
	;

CreatedName:
	IDENTIFIER TypeArgumentsOrDiamondOptional CreatedNameSuffixList
	| IDENTIFIER TypeArgumentsOrDiamondOptional
	| PrimitiveType
	;

CreatedNameSuffixList:
	DOT IDENTIFIER TypeArgumentsOrDiamondOptional
	| CreatedNameSuffixList DOT IDENTIFIER TypeArgumentsOrDiamondOptional
	;

InnerCreator:
	IDENTIFIER ClassCreatorRest
	| IDENTIFIER NonWildcardTypeArgumentsOrDiamond ClassCreatorRest
	;

ArrayCreatorRest:
	LRBrackList ArrayInitializer
	| ExpressionListWithBrack LRBrackList
	| ExpressionListWithBrack
	;

ClassCreatorRest:
	Arguments ClassBody
	| Arguments
	;

ExplicitGenericInvocation:
	NonWildcardTypeArguments ExplicitGenericInvocationSuffix
	;

ElementValueArrayInitializer:
	LBRACE ElementValues RBRACE
	| LBRACE ElementValues COMMA RBRACE
	| LBRACE COMMA RBRACE
	| LBRACE RBRACE
	;

ElementValues:
	ElementValue
	| ElementValues COMMA ElementValue
	;

ImportDeclListOptional:
	ImportDeclListOptional ImportDecl { debugInfo("ImportDecl"); }
	|
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

TypeDeclListOptional:
	TypeDeclListOptional TypeDecl { debugInfo("create one typedecl!"); }
	|
	;

TypeDecl:
	ClassOrInterfaceModifierListOptional ClassDecl { debugInfo("This is an classdecl"); }
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
	| PUBLIC { debugInfo("public"); }
	| PRIVATE
	| PROTECTED
	| STATIC { debugInfo("static"); }
	| ABSTRACT
	| FINAL
	| STRICTFP
	;

Modifier:
	ClassOrInterfaceModifier { debugInfo("the modifier is ClassOrinterface"); }
	| NATIVE
	| SYNCHRONIZED
	| TRANSIENT
	| VOLATILE
	;

ModifierList:
	Modifier
	| ModifierList Modifier
	;

VariableModifier:
	FINAL
	| Annotation
	;

ClassDecl:
	CLASS IDENTIFIER ClassBody { debugInfo("CLASS"); debugInfo($2); }
	| CLASS IDENTIFIER TypeParams ClassBody
	| CLASS IDENTIFIER EXTENDS TypeType ClassBody
	| CLASS IDENTIFIER IMPLEMENTS TypeList ClassBody
	| CLASS IDENTIFIER TypeParams EXTENDS TypeType ClassBody
	| CLASS IDENTIFIER TypeParams IMPLEMENTS TypeList ClassBody
	| CLASS IDENTIFIER TypeParams EXTENDS TypeType IMPLEMENTS TypeList ClassBody
	| CLASS IDENTIFIER EXTENDS TypeType IMPLEMENTS TypeList ClassBody
	;

TypeParams:
	LT CommaTypeParams GT
	;

CommaTypeParams:
	TypeParam
	| CommaTypeParams COMMA TypeParam
	;

TypeParam:
	IDENTIFIER
	| IDENTIFIER EXTENDS TypeBound
	| AnnotationList IDENTIFIER
	| AnnotationList IDENTIFIER EXTENDS TypeBound
	;

TypeBound:
	TypeType
	| TypeBound BITAND TypeType
	;

/* We use rule this even for void methods which cannot have [] after parameters.
   This simplifies grammar and we can consider void to be a type, which
   renders the [] matching as a context-sensitive issue or a semantic check
   for invalid return type after parsing.
 */

MethodBody
    : Block { debugInfo("it has something in methodbody"); }
    | COMMA
    ;

 /* TODO: Finish InterfaceDecl */
 /* InterfaceBody */
 /* InterfaceBodyDeclList */
 /* InterfaceBodyDecl */
 /* InterfaceMemberDecl ModifierList */
 /* ClassDecl EnumDecl */


 /* ParenListOptional QualifiedNameList MethodBody */

InterfaceDecl:
	INTERFACE IDENTIFIER TypeParams EXTENDS TypeList InterfaceBody
	| INTERFACE IDENTIFIER EXTENDS TypeList InterfaceBody
	| INTERFACE IDENTIFIER TypeParams InterfaceBody
	| INTERFACE IDENTIFIER InterfaceBody
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
	TypeType VariableDeclarators SEMIC
	;

InterfaceBodyDecl:
	InterfaceMemberDecl
	| ModifierList InterfaceMemberDecl
	| SEMIC
	;

InterfaceMemberDecl:
	ConstDecl
	| InterfaceMethodDecl
	| GenericInterfaceMethodDecl
	| InterfaceDecl
	| AnnotationTypeDecl
	| ClassDecl
	| EnumDecl
	;

ConstDecl:
	TypeType ConstantDeclaratorWithCommaList SEMIC
	;

ConstantDeclaratorWithCommaList:
	ConstantDeclarator
	| ConstantDeclaratorWithCommaList COMMA ConstantDeclarator
	;

ConstantDeclarator:
	IDENTIFIER LRBrackList ASSIGN VariableInitializer
	| IDENTIFIER ASSIGN VariableInitializer
	;

InterfaceMethodDecl:
	InterfaceMethodModifierListOptional TypeTypeOrVoid IDENTIFIER FormalParams LRBrackListOptional THROWS QualifiedNameList MethodBody
	| InterfaceMethodModifierListOptional TypeTypeOrVoid IDENTIFIER FormalParams LRBrackListOptional MethodBody
	| InterfaceMethodModifierListOptional TypeParams AnnotationListOptional TypeTypeOrVoid IDENTIFIER FormalParams LRBrackListOptional THROWS QualifiedNameList MethodBody
	| InterfaceMethodModifierListOptional TypeParams AnnotationListOptional TypeTypeOrVoid IDENTIFIER FormalParams LRBrackListOptional MethodBody
	;

GenericInterfaceMethodDecl:
	TypeParams InterfaceMethodDecl
	;

InterfaceMethodModifierListOptional:
	| InterfaceMethodModifierListOptional InterfaceMethodModifier
	|
	;

InterfaceMethodModifier:
	Annotation
	| PUBLIC
	| ABSTRACT
	| DEFAULT
	| STATIC
	| STRICTFP
	;

FormalParams:
	LPAREN FormalParameterList RPAREN
	| LPAREN RPAREN
	;

FormalParameterList:
	FormalParameterWithCommaList COMMA LastFormalParameter
	| FormalParameterWithCommaList
	| LastFormalParameter
	;

FormalParameterWithCommaList:
	FormalParam
	| FormalParameterWithCommaList COMMA FormalParam
	;

LastFormalParameter:
	VariableModifierList TypeType _ELLIPSIS VariableDeclaratorId
	| TypeType _ELLIPSIS VariableDeclaratorId
	;

FormalParam:
	VariableModifierList TypeType VariableDeclaratorId
	| TypeType VariableDeclaratorId
	;

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
	LT CommaTypeArguments GT
	;

CommaTypeArguments:
	TypeArgument
	| CommaTypeArguments COMMA TypeArgument
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

TypeTypeOrVoid:
	TypeType { debugInfo("not void type"); }
	| VOID { debugInfo("void type"); }
	;

GenericConstructorDecl:
	TypeParams ConstructorDecl

ConstructorDecl:
	IDENTIFIER FormalParams THROWS QualifiedNameList Block
	| IDENTIFIER FormalParams Block
	;

LRBrackListOptional:
	LRBrackList
	|
	;

LRBrackList:
	LBRACK RBRACK
	| LRBrackList LBRACK RBRACK
	;

TypeArgumentsOrDiamondOptional:
	TypeArgumentsOrDiamond
	|
	;

TypeArgumentsOrDiamond:
	LT GT
	| TypeArguments
	;

NonWildcardTypeArgumentsOrDiamond:
	NonWildcardTypeArguments
	| LT GT
	;

NonWildcardTypeArguments:
	LT TypeList GT
	;

TypeList:
	TypeType
	| TypeList COMMA TypeType
	;

AnnotationTypeDecl:
	_AT INTERFACE IDENTIFIER AnnotationTypeBody
	;

AnnotationTypeBody:
	LBRACE RBRACE
	| LBRACE AnnotationTypeElementDeclList RBRACE
	;

AnnotationTypeElementDeclList:
	AnnotationTypeElementDecl
	| AnnotationTypeElementDeclList AnnotationTypeElementDecl
	;

AnnotationTypeElementDecl:
	ModifierList AnnotationTypeElementRest
	| AnnotationTypeElementRest
	| SEMIC
	;

AnnotationTypeElementRest:
	TypeType AnnotationMethodOrConstantRest SEMIC
	| ClassDecl SemicOptional
	| InterfaceDecl SemicOptional
	| EnumDecl SemicOptional
	| AnnotationTypeDecl SemicOptional
	;

SemicOptional:
	SEMIC
	|
	;

AnnotationMethodOrConstantRest:
	AnnotationMethodRest
	| VariableDeclarators
	;

AnnotationMethodRest:
	IDENTIFIER LPAREN RPAREN DEFAULT ElementValue
	| IDENTIFIER LPAREN RPAREN
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
	LocalVariableDecl SEMIC
	| Statement { debugInfo("this is a statement"); }
	| LocalTypeDecl
	;

LocalVariableDecl:
	VariableModifierList TypeType VariableDeclarators
	| TypeType VariableDeclarators
	;

LocalTypeDecl:
	ClassOrInterfaceModifierListOptional ClassDecl
	| ClassOrInterfaceModifierListOptional InterfaceDecl
	| SEMIC
	;

 /* TODO: finish (Statement) */
Statement:
	Block
	| ASSERT Expression COLON Expression SEMIC
	| ASSERT Expression SEMIC
	| IF ParExpression Statement ELSE Statement
	| IF ParExpression Statement
	| FOR LPAREN ForControl RPAREN Statement { debugInfo("for statement"); }
	| WHILE ParExpression Statement
	| DO Statement WHILE ParExpression SEMIC
	| TRY Block CatchClauseList FinallyBlockOptional
	| TRY Block FinallyBlock
	| TRY ResourceSpecification Block CatchClauseListOptional FinallyBlockOptional
	| SWITCH ParExpression LBRACE SwitchBlockStatementGroupListOptional SwitchLabelListOptional RBRACE
	| SYNCHRONIZED ParExpression Block
	| RETURN Expression SEMIC
	| RETURN SEMIC
	| THROW Expression SEMIC
	| BREAK IDENTIFIER SEMIC
	| BREAK SEMIC
	| CONTINUE IDENTIFIER SEMIC
	| CONTINUE SEMIC
	| SEMIC
	| Expression SEMIC
	| IDENTIFIER COLON Statement
	;

CatchClauseListOptional:
	CatchClauseList
	|
	;

CatchClauseList:
	CatchClause
	| CatchClauseList CatchClause
	;

CatchClause:
	CATCH LPAREN VariableModifierList CatchType IDENTIFIER RPAREN Block
	| CARET LPAREN CatchType IDENTIFIER RPAREN Block
	;

CatchType:
	QualifiedName
	| CatchType BITOR QualifiedName
	;

FinallyBlockOptional:
	FINALLY Block
	|
	;

FinallyBlock:
	FINALLY Block
	;

ResourceSpecification:
	LPAREN Resources SEMIC RPAREN
	| LPAREN Resources RPAREN
	;

Resources:
	Resource
	| Resources SEMIC Resource
	;

Resource:
	VariableModifierList ClassOrInterfaceType VariableDeclaratorId ASSIGN Expression
	| ClassOrInterfaceType VariableDeclaratorId ASSIGN Expression
	;

EnumDecl:
	ENUM IDENTIFIER IMPLEMENTS TypeList LPAREN EnumConstantsOptional COMMA EnumBodyDeclarationsOptional RPAREN
	| ENUM IDENTIFIER LPAREN EnumConstantsOptional COMMA EnumBodyDeclarationsOptional RPAREN
	| ENUM IDENTIFIER IMPLEMENTS TypeList LPAREN EnumConstantsOptional EnumBodyDeclarationsOptional RPAREN
	| ENUM IDENTIFIER LPAREN EnumConstantsOptional EnumBodyDeclarationsOptional RPAREN
	;

EnumConstantsOptional:
	EnumConstants
	|
	;

EnumConstants:
	EnumConstant
	| EnumConstants COMMA EnumConstant
	;

EnumConstant:
	AnnotationListOptional IDENTIFIER Arguments ClassBody
	| AnnotationListOptional IDENTIFIER Arguments
	| AnnotationListOptional IDENTIFIER ClassBody
	| AnnotationListOptional IDENTIFIER
	;

EnumBodyDeclarationsOptional:
	EnumBodyDeclarations
	|
	;

EnumBodyDeclarations:
	COMMA ClassBodyDeclList
	| COMMA
	;

ClassBody:
	LBRACE RBRACE
	| LBRACE ClassBodyDeclList RBRACE { debugInfo("it has something in decl"); }
	;

ClassBodyDeclList:
	ClassBodyDecl { debugInfo("the last classbodydecl"); }
	| ClassBodyDeclList ClassBodyDecl { debugInfo("create one classbodydecl"); }
	;

ClassBodyDecl:
	SEMIC
	| STATIC Block
	| Block
	| ModifierList MemberDecl { debugInfo("modifierlist memberdecl"); }
	| MemberDecl
	;

/* TODO */
MemberDecl:
	MethodDecl
	| GenericMethodDecl
	| FieldDecl
	| ConstructorDecl
	| GenericConstructorDecl
	| InterfaceDecl
	| AnnotationTypeDecl
	| ClassDecl
	| EnumDecl
	;

 /* about method */

MethodDecl:
	TypeTypeOrVoid IDENTIFIER FormalParams LRBrackListOptional THROWS QualifiedNameList MethodBody
	| TypeTypeOrVoid IDENTIFIER FormalParams LRBrackListOptional MethodBody { debugInfo("no throw in method decl"); }
	;

GenericMethodDecl:
	TypeParams MethodDecl
	;

SuperSuffix:
	Arguments
	| DOT IDENTIFIER Arguments
	| DOT IDENTIFIER
	;

ExplicitGenericInvocationSuffix:
	SUPER SuperSuffix
	| IDENTIFIER Arguments
	;

Arguments:
	LPAREN ExpressionList RPAREN
	| LPAREN RPAREN
	;
%%

// Hello

int main(){
	return yyparse();
}