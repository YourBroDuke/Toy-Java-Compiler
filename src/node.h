#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

#include "MetaType.h"
#include "codeGen/Jasmin.hpp"
#include "codeGen/context.hpp"
using namespace std;

class Node
{
public:
    virtual void Visit() = 0;
    void codeGen(JContext *context);
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

class FileNode : public Node
{
public:
    PackageNode *packageNode;
    vector<ImportNode*> *importNodes;
    vector<TypeDeclNode*>  *typeDeclNodes;
    FileNode();
    ~FileNode();
    void Visit();
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
};

class IdentifierNode : public Node
{
public:
    string name;
    
    void Visit();
    IdentifierNode(const string& name);
    ~IdentifierNode();
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

class MemberDeclNode : public Node
{
public:
    vector<ModifierType> *modifiers;
    Node *mainDecl;
    void Visit();
    MemberDeclNode(Node *decl);
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
    MethodDeclNode(TypeTypeNode *type, const string& name, BlockNode *block);
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
    ~TypeTypeNode();
private:
    void printType();

public:
    void codeGen(JContext *context);
    string typeStr;
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
    int arrayDim;
    IdentifierNode *variableName;

    void Visit();
    VariableDeclaratorIdNode(int dim, const string& name);
    ~VariableDeclaratorIdNode();
};

class BlockNode : public Node
{
public:
    vector<BlockStatementNode*> *stats;

    void Visit();
    BlockNode();
    ~BlockNode();

public:
    vector<JStmt*> *Jstmts;
    void codeGen(JContext *context);
};

class BlockStatementNode : public Node
{
public:
    StatementNode *stat;

    void Visit();
    BlockStatementNode(StatementNode *stat);
    ~BlockStatementNode();
};

class StatementNode : public Node
{
public:
    StatementType type;
    Node *stat;

    void Visit();
    StatementNode(StatementType type, Node *stat);
    ~StatementNode();
private:
    void printType();
};

class ExprNode : public Node
{
public:
    ExprType type;
    PrimaryNode *primary;
    vector<IdentifierNode*> *ids;
    MethodCallParamsNode *methodCallParams;
    ExprNode *subExpr1, *subExpr2;

    void Visit();
    ExprNode(ExprType type, PrimaryNode *node);
    ExprNode(ExprType type);
    ExprNode(ExprType type, ExprNode *node);
    ExprNode(ExprType type, ExprNode *node1, ExprNode *node2);
    ~ExprNode();
};

class MethodCallParamsNode : public Node
{
public:
    vector<ExprNode*> *exprs;

    void Visit();
    MethodCallParamsNode();
    ~MethodCallParamsNode();
};

class PrimaryNode : public Node
{
public:
    PrimaryNodeType type;
    ExprNode *expr;
    LiteralNode *literal;
    IdentifierNode *id;

    void Visit();
    PrimaryNode(PrimaryNodeType type, ExprNode *node);
    PrimaryNode(PrimaryNodeType type, LiteralNode *node);
    PrimaryNode(PrimaryNodeType type, const string& id);
    ~PrimaryNode();
};

class LiteralNode : public Node
{
public:
    LiteralType type;
    int64_t intVal;
    double floatVal;
    string stringVal;

    void Visit();
    LiteralNode(LiteralType type, int64_t val);
    LiteralNode(LiteralType type, double val);
    LiteralNode(LiteralType type, const string& val);
    ~LiteralNode();
};

#endif