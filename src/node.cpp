#include "node.h"
#include "MetaType.h"
#include <iostream>
using namespace std;
FileNode::FileNode(){

}

FileNode::~FileNode(){

}

void FileNode::Visit(){
    this->packageNode->Visit();
    for (auto node: *this->importNodes){
        node->Visit();
    }
    for (auto node: *this->typeDeclNodes){
        node->Visit();
    }
}

PackageNode::PackageNode(QualifiedNameNode *node) {
    this->qNode = node;
}

void PackageNode::Visit() {
    this->qNode->Visit();
}

ImportNode::ImportNode() {

}

void ImportNode::Visit() {

}

IdentifierNode::IdentifierNode(const string& name) {
    this->name = name;
}

void IdentifierNode::Visit() {
    cout << this->name << endl;
}

TypeDeclNode::TypeDeclNode(ClassOrInterface t, ClassDeclNode *node) {
    this->type = t;
    this->classDecl = node;
}

void TypeDeclNode::Visit() {
    if (this->type == CLASS_TYPE){
        cout << "class" << endl;
    }else{
        cout << "interface" << endl;
    }

    this->classDecl->Visit();
}

void TypeDeclNode::codeGen(JContext* context){
    context->nodeStack.push(this);
    this->classSpec = new JClassSpec;
    this->classSpec->accessSpec = "";
    for (auto modifer: *this->modifiers){
        this->classSpec->accessSpec += ModifierMap.at(modifer) + " ";
    }
    this->classSpec->className = this->classDecl->className->name;
    context->classFile->jasminHeader->classSpec = this->classSpec;
    context->nodeStack.pop();

    this->classDecl->codeGen(context);
}

ClassDeclNode::ClassDeclNode(const string& name, ClassBodyNode *classBody) {
    this->classBody = classBody;
    this->className = new IdentifierNode(name);
}

void ClassDeclNode::Visit() {
    this->className->Visit();
    this->classBody->Visit();
}

QualifiedNameNode::QualifiedNameNode() {
    this->identifiers = new vector<IdentifierNode*>;
}

void QualifiedNameNode::Visit() {
    for (auto node : *this->identifiers){
        node->Visit();
    }
}


ClassBodyNode::ClassBodyNode() {
}

void ClassBodyNode::codeGen(JContext *context){
    for (auto node : *this->memberDecls){
        node->codeGen(context);
    }
}

void ClassBodyNode::Visit() {
    for (auto node : *this->memberDecls)
        node->Visit();
}

MemberDeclNode::MemberDeclNode(Node *decl) {
    this->mainDecl = decl;
}

void MemberDeclNode::codeGen(JContext *context){
    context->nodeStack.push(this);
    this->mainDecl->codeGen(context);
}

void MemberDeclNode::printType(ModifierType type) {
    if (type == PUBLIC_TYPE) cout << "it has public attribute" << endl;
    if (type == STATIC_TYPE) cout << "it has static attribute" << endl;
}

void MemberDeclNode::Visit() {
    this->mainDecl->Visit();
    for (auto crt : *this->modifiers)
        this->printType(crt);
}

MethodDeclNode::MethodDeclNode(TypeTypeNode *type, const string& name, BlockNode *block) {
    this->typeInfo = type;
    this->nodeName = new IdentifierNode(name);
    this->methodBody = block;
}

void MethodDeclNode::Visit() {
    this->typeInfo->Visit();
    this->nodeName->Visit();
    for (auto node : *this->params)
        node->Visit();
    this->methodBody->Visit();
}

void MethodDeclNode::codeGen(JContext *context){
    auto parNode = dynamic_cast<MemberDeclNode*>(context->nodeStack.top());
    this->method = new JMethod;
    this->method->accessSpec = new string();
    for (auto modifier : *parNode->modifiers){
        *this->method->accessSpec += ModifierMap.at(modifier) + " ";
    }
    this->method->methodName = new string(this->nodeName->name);

    for (auto p : *this->params){
        p->codeGen(context);
    }

    this->typeInfo->codeGen(context);
    
        
}

TypeTypeNode::TypeTypeNode(PrimitiveTypeOrNot type) {
    this->type = type;
}

void TypeTypeNode::printType() {
    if (this->type == VOID_TYPE)
        cout << "This is a void method" << endl;
}

void TypeTypeNode::Visit() {
    this->printType();
    for (auto node : *this->typeInfo)
        node->Visit();
}

FormalParamNode::FormalParamNode(TypeTypeNode *type, VariableDeclaratorIDNode *node) {
    this->paramType = type;
    this->declNode = node;
}

void FormalParamNode::Visit() {
    this->paramType->Visit();
    this->declNode->Visit();
}

VariableDeclaratorIDNode::VariableDeclaratorIDNode(int dim, const string& name) {
    this->arrayDim = dim;
    this->variableName = new IdentifierNode(name);
}

void VariableDeclaratorIDNode::Visit() {
    cout << "it has " << this->arrayDim << "dims" << endl;
    this->variableName->Visit();
}

BlockNode::BlockNode() {

}

void BlockNode::Visit() {
    for (auto node : *this->stats) {
        node->Visit();
    }
}

BlockStatementNode::BlockStatementNode(StatementNode *stat) {
    this->stat = stat;
}

void BlockStatementNode::Visit() {
    this->stat->Visit();
}

StatementNode::StatementNode(StatementType type, Node *stat) {
    this->type = type;
    this->stat = stat;
}

void StatementNode::printType() {
    if (this->type == EXPR_TYPE) {
        cout << "this is a expr statement" << endl;
    }
}

void StatementNode::Visit() {
    this->printType();
    this->stat->Visit();
}

ExprNode::ExprNode(ExprType type, PrimaryNode *node) {
    this->type = type;
    this->primary = node;
    this->ids = NULL;
    this->methodCallParams = NULL;
    this->subExpr1 = this->subExpr2 = NULL;
}

ExprNode::ExprNode(ExprType type) {
    this->type = type;
    this->primary = NULL;
    this->ids = NULL;
    this->methodCallParams = NULL;
    this->subExpr1 = this->subExpr2 = NULL;
}

ExprNode::ExprNode(ExprType type, ExprNode *node) {
    this->type = type;
    this->primary = NULL;
    this->ids = NULL;
    this->methodCallParams = NULL;
    this->subExpr1 = node;
    this->subExpr2 = NULL;
}

ExprNode::ExprNode(ExprType type, ExprNode *node1, ExprNode *node2) {
    this->type = type;
    this->primary = NULL;
    this->ids = NULL;
    this->methodCallParams = NULL;
    this->subExpr1 = node1;
    this->subExpr2 = node2;
}

void ExprNode::Visit() {
    if (this->primary != NULL) this->primary->Visit();
    if (this->ids != NULL) {
        for (auto node : *this->ids)
            node->Visit();
    }
    if (this->methodCallParams != NULL)
        this->methodCallParams->Visit();
}

MethodCallParamsNode::MethodCallParamsNode() {

}

void MethodCallParamsNode::Visit() {
    for (auto node : *this->exprs)
        node->Visit();
}

PrimaryNode::PrimaryNode(PrimaryNodeType type, ExprNode *node) {
    this->type = type;
    this->expr = node;
    this->literal = NULL;
    this->id = NULL;
}

PrimaryNode::PrimaryNode(PrimaryNodeType type, LiteralNode *node) {
    this->type = type;
    this->expr = NULL;
    this->literal = node;
    this->id = NULL;
}

PrimaryNode::PrimaryNode(PrimaryNodeType type, const string& name) {
    this->type = type;
    this->expr = NULL;
    this->literal = NULL;
    this->id = new IdentifierNode(name);
}

void PrimaryNode::Visit() {
    if (literal != NULL)
        this->literal->Visit();
}

LiteralNode::LiteralNode(LiteralType type, int64_t val) {
    this->type = type;
    this->intVal = val;
}

LiteralNode::LiteralNode(LiteralType type, double val) {
    this->type = type;
    this->floatVal = val;
}

LiteralNode::LiteralNode(LiteralType type, const string& val) {
    this->type = type;
    this->stringVal = val;
}

void LiteralNode::Visit() {
    if (this->type == STRING_LIT) {
        cout << this->stringVal << endl;
    }
}