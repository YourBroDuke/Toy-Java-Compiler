#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <iostream>

#include "MetaType.h"
#include "codeGen/Jasmin.hpp"
#include "codeGen/context.hpp"
using namespace std;

class JContext;

class Node
{
public:
    virtual void Visit() = 0;
    virtual void codeGen(JContext *context) = 0;
};

class PackageNode;
class ImportNode;
class TypeDeclNode;
class QualifiedNameNode;
class ClassDeclNode;
class IdentifierNode;
class ClassBodyDeclNode;
class MemberDeclNode;
class TypeTypeNode;
class FormalParamNode;
class BlockNode;
class VariableDeclaratorIdNode;
class StatementNode;
class PrimaryNode;
class MethodCallParamsNode;
class LiteralNode;
class ClassBodyNode;
class BlockStatementNode;
class VariableInitializerNode;
class VariableDeclaratorNode;
class ForControlNode;
class ForInitNode;

class FileNode : public Node
{
public:
    PackageNode *packageNode;
    vector<ImportNode*> *importNodes;
    vector<TypeDeclNode*>  *typeDeclNodes;
    FileNode();
    ~FileNode();
    void Visit();

public:
    void codeGen(JContext* context);
};

// omit
class PackageNode : public Node
{
public:
    QualifiedNameNode *qNode;
    PackageNode(QualifiedNameNode *node);
    ~PackageNode();
    void Visit();

    // do nothing
    void codeGen(JContext *context);
};

//omit
class ImportNode : public Node
{
public:
    void Visit();
    ImportNode();
    ~ImportNode();

    // do nothing
    void codeGen(JContext *context);
};

// class specification
class TypeDeclNode : public Node
{
public:
    vector<ModifierType> *modifiers;
    ClassOrInterface type;
    ClassDeclNode *classDecl;

    void Visit();
    TypeDeclNode(ClassOrInterface t, ClassDeclNode *node);
    ~TypeDeclNode();

public:
    void codeGen(JContext *context);
    JClassSpec *classSpec;
};

class QualifiedNameNode : public Node
{
public:
    vector<IdentifierNode*> *identifiers;

    void Visit();
    QualifiedNameNode();
    ~QualifiedNameNode();

public:
    void codeGen(JContext* context);
};

class IdentifierNode : public Node
{
public:
    string name;
    
    void Visit();
    IdentifierNode(const string& name);
    ~IdentifierNode();

public:
    void codeGen(JContext* context);
};

/* START */
// class declaration block {}
class ClassDeclNode : public Node
{
public:
    IdentifierNode *className;
    ClassBodyNode *classBody;
    
    void Visit();
    ClassDeclNode(const string& className, ClassBodyNode *body);
    ~ClassDeclNode();

public:
    void codeGen(JContext* context);

};

// declarations
class ClassBodyNode : public Node
{
public:
    vector<MemberDeclNode*> *memberDecls;
    void Visit();
    ClassBodyNode();
    ~ClassBodyNode();

public:
    // do nothing
    void codeGen(JContext* context);
};

// TODO
class MemberDeclNode : public Node
{
public:
    MemberDeclType declType;
    vector<ModifierType> *modifiers;
    Node *mainDecl;
    void Visit();
    MemberDeclNode(MemberDeclType declType, Node *decl);
    MemberDeclNode(MemberDeclType declType, vector<ModifierType> *modifiers, Node *decl);
    ~MemberDeclNode();
private:
    void printType(ModifierType type);

public:
    // delegate to child node
    void codeGen(JContext *context);
};

// method -> JMethod
class MethodDeclNode : public Node
{
public:
    TypeTypeNode *typeInfo;
    IdentifierNode *nodeName;
    vector<FormalParamNode*> *params;
    BlockNode *methodBody;

    void Visit();
    MethodDeclNode(TypeTypeNode *type, const string& name, vector<FormalParamNode*> *params, BlockNode *block);
    ~MethodDeclNode();

private:
    void printType(ModifierType type);

public:
    void codeGen(JContext *context);
    JMethod *method;
};

class TypeTypeNode : public Node
{
public:
    PrimitiveTypeOrNot type;
    vector<IdentifierNode*> *typeInfo;
    int arrayDim;

    void Visit();
    TypeTypeNode(PrimitiveTypeOrNot type);
    TypeTypeNode(PrimitiveTypeOrNot type, int arrayDim);
    TypeTypeNode(PrimitiveTypeOrNot type, vector<IdentifierNode*> *typeInfo);
    TypeTypeNode(PrimitiveTypeOrNot type, vector<IdentifierNode*> *typeInfo, int arrayDim);
    TypeTypeNode(PrimitiveTypeOrNot type, const string& id);
    TypeTypeNode(PrimitiveTypeOrNot type, const string& id, int arrayDim);
    ~TypeTypeNode();
private:
    void printType();

public:
    void codeGen(JContext *context);
    string typeStr;
};

class FieldDeclNode : public Node
{
public:
    TypeTypeNode *type;
    IdentifierNode *id;
    
    FieldDeclNode(TypeTypeNode *type, const string& str);
    ~FieldDeclNode();
    void Visit();
    void codeGen(JContext *context);
};

class FormalParamNode : public Node 
{
public:
    TypeTypeNode *paramType;
    VariableDeclaratorIdNode *declNode;

    void Visit();
    FormalParamNode(TypeTypeNode *type, VariableDeclaratorIdNode *declNode);
    ~FormalParamNode();

public:
    void codeGen(JContext *context);
    string *paramStr;
};

class VariableDeclaratorIdNode : public Node
{
public:
    int arrayDim;   // No use now
    IdentifierNode *variableName;

    void Visit();
    VariableDeclaratorIdNode(int dim, const string& name);
    ~VariableDeclaratorIdNode();

public:
    void codeGen(JContext* context);
};

class BlockNode : public Node
{
public:
    vector<BlockStatementNode*> *stats;

    void Visit();
    BlockNode();
    BlockNode(vector<BlockStatementNode*> *stats);
    ~BlockNode();

public:
    vector<JStmt*> *Jstmts;
    void codeGen(JContext *context);
};

class Statement: public Node {
    public:
        vector<JStmt*> *stmt;
        Statement();
    void codeGen(JContext *context);
};

class BlockStatementNode : public Statement
{
public:
    int isVarDecl;
    // If isVarDecl --> LocalVariableDeclNode*
    // else         --> StatementNode*
    Statement *statOrdecl;

    void Visit();
    BlockStatementNode(int isVarDecl, Statement *stat);
    ~BlockStatementNode();

public:
    void codeGen(JContext* context);
};

// TODO
class StatementNode : public Statement
{
public:
    StatementType type;
    BlockNode *block;
    Statement *stat1, *stat2, *stat3;
    ForControlNode *forControl;

    void Visit();
    StatementNode(StatementType type);
    StatementNode(StatementType type, BlockNode *block);
    StatementNode(StatementType type, Statement *stat);
    StatementNode(StatementType type, Statement *stat1, Statement *stat2);
    StatementNode(StatementType type, Statement *stat1, Statement *stat2, Statement *stat3);
    StatementNode(StatementType type, ForControlNode *forControl, Statement *stat);
    ~StatementNode();
private:
    void printType();

public:
    void codeGen(JContext *context);
};

class ExprNode : public Statement
{
public:
    ExprType type;
    PrimaryNode *primary;
    vector<IdentifierNode*> *ids;
    MethodCallParamsNode *methodCallParams;
    ExprNode *subExpr1, *subExpr2;
    vector<ExprNode*> *ArrayIndexQueryList;

    void Visit();
    ExprNode(ExprType type, PrimaryNode *node);
    ExprNode(ExprType type, vector<IdentifierNode*> *ids);
    ExprNode(ExprType type, vector<IdentifierNode*> *ids, MethodCallParamsNode *methodCallParams);
    ExprNode(ExprType type, const string& id, MethodCallParamsNode *methodCallParams);
    ExprNode(ExprType type, ExprNode *node);
    ExprNode(ExprType type, ExprNode *node1, ExprNode *node2);
    ExprNode(ExprType type, const string& id, vector<ExprNode*> *ArrayIndexQueryList);
    ExprNode(ExprType type, vector<IdentifierNode*> *ids, vector<ExprNode*> *ArrayIndexQueryList);
    ~ExprNode();

public:
    void codeGen(JContext *context);
    ExprType exprType;
};

class MethodCallParamsNode : public Node
{
public:
    vector<ExprNode*> *exprs;

    void Visit();
    MethodCallParamsNode();
    MethodCallParamsNode(vector<ExprNode*> *exprs);
    ~MethodCallParamsNode();

public:
    void codeGen(JContext* context);
};

class PrimaryNode : public Statement
{
public:
    PrimaryNodeType type;
    ExprNode *expr;
    LiteralNode *literal;
    IdentifierNode *id;

    void Visit();
    PrimaryNode(PrimaryNodeType type);
    PrimaryNode(PrimaryNodeType type, ExprNode *node);
    PrimaryNode(PrimaryNodeType type, LiteralNode *node);
    PrimaryNode(PrimaryNodeType type, const string& id);
    ~PrimaryNode();

public:
    void codeGen(JContext *context);
};

class LiteralNode : public Statement
{
public:
    LiteralType type;
    int64_t intVal;
    double floatVal;
    string stringVal;

    void Visit();
    LiteralNode(LiteralType type, const string& str);
    ~LiteralNode();

public:
    void codeGen(JContext *context);

private:
    int64_t StrToInt(const string& str);
    double StrToFloat(const string& str);
};

class LocalVariableDeclNode : public Statement
{
public:
    int isFinal;
    TypeTypeNode *type;
    vector<VariableDeclaratorNode*> *decls;
    
    LocalVariableDeclNode(int isFinal, TypeTypeNode *type, vector<VariableDeclaratorNode*> *decls);
    ~LocalVariableDeclNode();
    void Visit();
    void codeGen(JContext *context);  
};

class VariableDeclaratorNode : public Statement
{
public:
    VariableDeclaratorIdNode *idNode;
    VariableInitializerNode *initializer;

    VariableDeclaratorNode(VariableDeclaratorIdNode *idNode);
    VariableDeclaratorNode(VariableDeclaratorIdNode *idNode, VariableInitializerNode *init);
    ~VariableDeclaratorNode();
    void codeGen(JContext *context);
    void Visit();
};

class VariableInitializerNode : public Statement
{
public:
    int isSingleExpr;
    ExprNode *expr;
    vector<VariableInitializerNode*> *array;

    VariableInitializerNode(int isSingleExpr, ExprNode *expr);
    VariableInitializerNode(int isSingleExpr, vector<VariableInitializerNode*> *array);
    ~VariableInitializerNode();
    void Visit();
    void codeGen(JContext *context);
};

class ForControlNode : public Node {
public:
    ForInitNode *init;
    ExprNode *CmpExpr;
    vector<ExprNode*> *finishExprList;

    ForControlNode(ForInitNode *init);
    ForControlNode(ForInitNode *init, ExprNode *CmpExpr);
    ForControlNode(ForInitNode *init, ExprNode *CmpExpr, vector<ExprNode*> *exprs);
    ForControlNode(ForInitNode *init, vector<ExprNode*> *exprs);
    ~ForControlNode();
    void Visit();
    void codeGen(JContext *context);
};

class ForInitNode : public Node {
public:
    int isVarDecl;
    LocalVariableDeclNode *varDecl;
    vector<ExprNode*> *exprs;

    ForInitNode(int isVarDecl, LocalVariableDeclNode *varDecl);
    ForInitNode(int isVarDecl, vector<ExprNode*> *exprs);
    ~ForInitNode();
    void Visit();
    void codeGen(JContext *context);
};


void IncrStack(JContext* context);

#endif