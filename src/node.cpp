#include "node.h"
#include "MetaType.h"
#include "../utils/utils.hpp"
#include <iostream>
using namespace std;

#define DEBUG

void debugInfo(const string& info){
    #ifdef DEBUG
    cout << info << endl;
    #endif
}

void Node::codeGen(JContext* context) {

}

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

void FileNode::codeGen(JContext *context){
    cout << "IN" << endl;
    debugInfo("codeGen enter FileNode");
    if (this->packageNode != nullptr){
        this->packageNode->codeGen(context);
        debugInfo("codeGen packageNode done!");
    }
    for (auto import : *importNodes){
        import->codeGen(context);
    }
    debugInfo("codeGen importNodes done!");
    for (auto decl: *typeDeclNodes){
        decl->codeGen(context);
    }
    debugInfo("codeGen typeDeclNodes done!");
}

PackageNode::PackageNode(QualifiedNameNode *node) {
    this->qNode = node;
}

void PackageNode::Visit() {
    this->qNode->Visit();
}

void PackageNode::codeGen(JContext* context){
    debugInfo("codeGen enter packageNode");
}

ImportNode::ImportNode() {

}

void ImportNode::Visit() {

}

void ImportNode::codeGen(JContext* context){
    debugInfo("codeGen enter ImportNode");
}

IdentifierNode::IdentifierNode(const string& name) {
    this->name = name;
}

void IdentifierNode::Visit() {
    cout << this->name << endl;
}

void IdentifierNode::codeGen(JContext* context){
    // terminal
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
    debugInfo("codeGen enter TypeDeclNode");
    context->nodeStack.push(this);
    this->classSpec = new JClassSpec;
    this->classSpec->accessSpec = "";
    for (auto modifer: *this->modifiers){
        this->classSpec->accessSpec += ModifierMap.at(modifer) + " ";
    }
    this->classSpec->className = this->classDecl->className->name;
    // TODO: pointer copy
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

void ClassDeclNode::codeGen(JContext* context) {
    debugInfo("codeGen enter ClassDeclNode");
    this->classBody->codeGen(context);
}

QualifiedNameNode::QualifiedNameNode() {
    this->identifiers = new vector<IdentifierNode*>;
}

void QualifiedNameNode::Visit() {
    for (auto node : *this->identifiers){
        node->Visit();
    }
}

void QualifiedNameNode::codeGen(JContext* context){
    //TODO:
}


ClassBodyNode::ClassBodyNode() {
}

void ClassBodyNode::codeGen(JContext *context){
    debugInfo("codeGen enter ClassBodyNode");
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
    debugInfo("codeGen enter MemberDeclNode");
    context->nodeStack.push(this);
    this->mainDecl->codeGen(context);
}

void MemberDeclNode::printType(ModifierType type) {
    if (type == PUBLIC_TYPE) cout << "it has public attribute" << endl;
    if (type == STATIC_TYPE) cout << "it has static attribute" << endl;
}

void MemberDeclNode::Visit() {
    for (auto crt : *this->modifiers)
        this->printType(crt);
    this->mainDecl->Visit();
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
    debugInfo("codeGen enter MethodDeclNode");
    auto parNode = dynamic_cast<MemberDeclNode*>(context->nodeStack.top());
    context->nodeStack.pop();
    // pop
    this->method = new JMethod;
    this->method->accessSpec = new string();

    // push method
    context->nodeStack.push(this);
    
    context->currentFrame.push(new Frame(this));
    
    for (auto modifier : *parNode->modifiers){
        *this->method->accessSpec += ModifierMap.at(modifier) + " ";
    }
    this->method->methodName = new string(this->nodeName->name);
    // Refactor:
    this->method->descriptor = new JDescriptor;
    this->method->descriptor->params = new vector<string>;

    for (auto p : *this->params){
        p->codeGen(context);
        this->method->descriptor->params->push_back(*p->paramStr);
    }
    debugInfo("codeGen MethodDeclNode params generation done.");

    this->typeInfo->codeGen(context);
    this->method->descriptor->ret = this->typeInfo->typeStr;
    debugInfo("codeGen MethodDeclNode descriptor generation done.");

    context->nodeStack.push(this->methodBody);
    //push block
    this->methodBody->codeGen(context);
    // copy TODO: pointer copy
    this->method->JStmts = this->methodBody->Jstmts;

    // pop method
    context->nodeStack.pop();
    auto top = context->currentFrame.top();
    context->currentFrame.pop();
    delete top;

    context->classFile->JMethods = new vector<JMethod*>;
    context->classFile->JMethods->push_back(this->method);
    debugInfo("codeGen exit MethodDeclNode");
}

TypeTypeNode::TypeTypeNode(PrimitiveTypeOrNot type) {
    this->type = type;
    this->typeInfo = NULL;
    this->arrayDim = 0;
}

void TypeTypeNode::printType() {
    if (this->type == VOID_TYPE)
        cout << "This is a void method" << endl;
}

void TypeTypeNode::codeGen(JContext* context){
    debugInfo("codeGen enter TypeTypeNode");
    // MARK: should the ID be preserved?
    if (this->type == NONPR_TYPE){
        this->typeStr = "";
        for (int i = 0; i < this->arrayDim; ++i){
            this->typeStr += "[";
        }
        this->typeStr += "L";
        if (this->typeInfo->size() == 1 && (*this->typeInfo->begin())->name == "String"){
            this->typeStr += "java/lang/String";
        }else{
            for (auto id : *this->typeInfo){
                this->typeStr += id->name;
                if (id != *(this->typeInfo->end()-1)){
                    this->typeStr += '/';
                }
            }
        }
    }else{
        this->typeStr = PrimitiveTypeOrNotMap.at(this->type);
    }
    debugInfo("codeGen exit TypeTypeNode");
}

void TypeTypeNode::Visit() {
    this->printType();
    cout << "It has " << this->arrayDim << " dimensions" << endl;
    if (this->typeInfo == NULL) return;
    
    for (auto node : *this->typeInfo)
        node->Visit();
}

FormalParamNode::FormalParamNode(TypeTypeNode *type, VariableDeclaratorIdNode *node) {
    this->paramType = type;
    this->declNode = node;
}

void FormalParamNode::Visit() {
    this->paramType->Visit();
    this->declNode->Visit();
}

void FormalParamNode::codeGen(JContext *context){
    debugInfo("codeGen enter FormalParamNode");
    this->paramType->codeGen(context);
    this->paramStr = new string(this->paramType->typeStr);
    if (this->paramType->typeStr == "J" || this->paramType->typeStr == "D"){
        context->currentFrame.top()->frameNode->method->localLimit += 2;
    }else{
        context->currentFrame.top()->frameNode->method->localLimit += 1;
    }
}

VariableDeclaratorIdNode::VariableDeclaratorIdNode(int dim, const string& name) {
    this->arrayDim = dim;
    this->variableName = new IdentifierNode(name);
}

void VariableDeclaratorIdNode::Visit() {
    this->variableName->Visit();
}

void VariableDeclaratorIdNode::codeGen(JContext *context){
    // TODO:
}

BlockNode::BlockNode() {
    this->Jstmts = new vector<JStmt*>;
}

void BlockNode::Visit() {
    for (auto node : *this->stats) {
        node->Visit();
    }
}

void BlockNode::codeGen(JContext* context){
    debugInfo("codeGen enter BlockNode");
    context->nodeStack.push(this);
    for (auto stmt: *this->stats){
        stmt->codeGen(context);
        // TODO: pointer copy
        this->Jstmts->insert(this->Jstmts->end(), 
            stmt->stmt->begin(),
            stmt->stmt->end());
    }
    context->nodeStack.pop();
    debugInfo("codeGen exit BlockNode");
}

Statement::Statement(){
    this->stmt = new vector<JStmt*>;
}


BlockStatementNode::BlockStatementNode(int isVarDecl, Statement *stat) {
    this->isVarDecl = isVarDecl;
    this->statOrdecl = stat;
}

void BlockStatementNode::Visit() {
    this->statOrdecl->Visit();
}

void BlockStatementNode::codeGen(JContext *context){
    debugInfo("codeGen enter BlockStatementNode");
    this->statOrdecl->codeGen(context);
    this->stmt = this->statOrdecl->stmt;
    debugInfo("codeGen exit BlockStatementNode");
}

StatementNode::StatementNode(StatementType) {
    this->type = type;
}

StatementNode::StatementNode(StatementType type, Statement *stat) {
    this->type = type;
    this->stat1 = stat;
}

StatementNode::StatementNode(StatementType type, Statement *stat1, Statement *stat2) {
    this->type = type;
    this->stat1 = stat1;
    this->stat2 = stat2;
}

StatementNode::StatementNode(StatementType type, Statement *stat1, Statement *stat2, Statement *stat3) {
    this->type = type;
    this->stat1 = stat1;
    this->stat2 = stat2;
    this->stat3 = stat3;
}

void StatementNode::printType() {
    if (this->type == EXPR_TYPE) {
        cout << "this is a expr statement" << endl;
    }
}

void StatementNode::Visit() {
    this->printType();
    this->stat1->Visit();
}

void StatementNode::codeGen(JContext *context){
    debugInfo("codeGen enter StatementNode");
    // TODO: translate all type
    context->nodeStack.push(this);
    //delegate to child node
    this->stat1->codeGen(context);
    this->stmt = this->stat1->stmt;
    context->nodeStack.pop();
    debugInfo("codeGen exit StatementNode");
}

void Statement::codeGen(JContext* context){
    cerr << "ERROR! This should not be entered!" << endl;
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

void ExprNode::codeGen(JContext *context){
    debugInfo("codeGen enter ExprNode");
    // TODO: translate all expr type
    if (this->type == IDEN_METHOD || this->type == IDEN_DOT_METHOD){
        // push context
        context->nodeStack.push(this);
        for (auto params : *methodCallParams->exprs){
            params->codeGen(context);
            this->stmt->insert(this->stmt->end(), 
                params->stmt->begin(),
                params->stmt->end());
        }
        context->nodeStack.pop();

        // TODO: symbol table
        JInstructionStmt *s = new JInstructionStmt;
        s->pc = nullptr;
        s->opcode = new string("invokevirtual");
        string argStr = "";
        for (auto id : *ids){
            argStr += id->name;
            if (id != *(ids->end()-1)){
                argStr += '/';
            }
        }
        // TODO: generate descriptor
        argStr += "(Ljava/lang/String;)V";
        s->args->push_back(argStr);

        this->stmt->push_back(s);

    } else if (this->type == PRIMARY_TYPE){
        this->primary->codeGen(context);
        this->stmt->insert(this->stmt->end(),
            this->primary->stmt->begin(),
            this->primary->stmt->end()
            );
    } else if (this->type == OP_ADD){
        if (this->subExpr1->exprType == this->subExpr2->exprType){
            this->exprType = this->subExpr1->exprType;
            switch (this->subExpr1->exprType)
            {
            case INT_TYPE:
                this->stmt->push_back(NewSimpleNoParamsInstruction("iadd"));
                break;
            case FLOAT_TYPE:
                this->stmt->push_back(NewSimpleNoParamsInstruction("fadd"));
                break;
            case DOUBLE_TYPE:
                this->stmt->push_back(NewSimpleNoParamsInstruction("dadd"));
                break;
            case LONG_TYPE:
                this->stmt->push_back(NewSimpleNoParamsInstruction("ladd"));
                break;
            case STRING_TYPE:
                // TODO:
                break;
            default:
                break;
            }
        }else{
            // TODO:error handling
        }
    }
}

MethodCallParamsNode::MethodCallParamsNode() {

}

void MethodCallParamsNode::Visit() {
    for (auto node : *this->exprs)
        node->Visit();
}

void MethodCallParamsNode::codeGen(JContext* context){
    // ignore for now
    // TODO:
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

void PrimaryNode::codeGen(JContext* context){
    debugInfo("codeGen enter PrimaryNode");
    // TODO:
    if (this->type == PRIMARY_LITERAL){
        this->literal->codeGen(context);
        this->stmt->insert(this->stmt->end(),
            this->literal->stmt->begin(),
            this->literal->stmt->end());
    }
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
    } else if (this->type == INTEGER_LIT) {
        cout << this->intVal << endl;
    } else if (this->type == FLOAT_LIT) {
        cout << this->floatVal << endl;
    } else if (this->type == CHAR_LIT) {
        cout << static_cast<char>(this->intVal) << endl;
    } else if (this->type == BOOL_LIT) {
        string boolVal = this->intVal?"true":"false";
        cout << boolVal << endl;
    } else {
        cout << "NULL" << endl;
    }
}

void LiteralNode::codeGen(JContext *context){
    // complete
    if (this->type == STRING_LIT){
        JInstructionStmt *s = new JInstructionStmt;
        s->opcode = new string("ldc");
        s->args = new vector<string>;
        s->args->push_back(stringVal);
        this->stmt->push_back(s);
        IncrStack(context);
    }else if (this->type == INTEGER_LIT || this->type == FLOAT_LIT || this->type == CHAR_LIT || this->type == BOOL_LIT){
        JInstructionStmt *s = new JInstructionStmt;
        s->opcode = new string("ldc");
        s->args = new vector<string>;
        if (this->type == FLOAT_LIT)
            s->args->push_back(to_string(this->floatVal));
        else
            s->args->push_back(to_string(this->intVal));
        this->stmt->push_back(s);
        IncrStack(context);
    } else {
        // NULL_LIT
        JInstructionStmt *s = new JInstructionStmt;
        s->opcode = new string("ACONST_NULL");
        this->stmt->push_back(s);
        IncrStack(context);
    }
}


void IncrStack(JContext* context){
    if (context->currentFrame.size() != 0){
        context->currentFrame.top()->frameNode->method->stackLimit++;
    }
}

LocalVariableDeclNode::LocalVariableDeclNode(int isFinal, TypeTypeNode *type) {
    this->isFinal = isFinal;
    this->type = type;
}

void LocalVariableDeclNode::Visit() {
    if (this->isFinal) cout << "final variable" << endl;
    this->type->Visit();
    for (auto node : *this->decls) {
        node->Visit();
    }
}

void LocalVariableDeclNode::codeGen(JContext *context) {
    // TODO: final
    this->type->codeGen(context);
    context->nodeStack.push(this);
    for (auto decl : *this->decls){
        decl->codeGen(context);
        this->stmt->insert(this->stmt->end(), decl->stmt->begin(), decl->stmt->end());
    }
    context->nodeStack.pop();
}

VariableDeclaratorNode::VariableDeclaratorNode(VariableDeclaratorIdNode *idNode) {
    this->idNode = idNode;
    this->initializer = NULL;
}

VariableDeclaratorNode::VariableDeclaratorNode(VariableDeclaratorIdNode *idNode, VariableInitializerNode *init) {
    this->idNode = idNode;
    this->initializer = init;
}

void VariableDeclaratorNode::Visit() {
    this->idNode->Visit();
    if (this->initializer) this->initializer->Visit();
}

void VariableDeclaratorNode::codeGen(JContext *context) {
    LocalVariableDeclNode* parNode = dynamic_cast<LocalVariableDeclNode*>(context->nodeStack.top());

    // first push the initial value
    if (this->initializer != nullptr){
        this->initializer->codeGen(context);
        this->stmt->insert(this->stmt->end(), 
            initializer->stmt->begin(), 
            initializer->stmt->end()
            );
    }

    int size=1; 
    if (parNode->type->typeStr == "J" || parNode->type->typeStr == "D"){
        size = 2;
    }
    string typeStr = parNode->type->typeStr;

    if (context->currentFrame.size() != 0){
        // local variabel declaration
        auto frame = context->currentFrame.top();
        frame->varIndex[this->idNode->variableName->name].index = frame->frameNode->method->localLimit;
        frame->frameNode->method->localLimit += size;
        frame->varIndex[this->idNode->variableName->name].typeName = parNode->type->typeStr;
        if (this->initializer == nullptr){
            JInstructionStmt *s = new JInstructionStmt;
            s->opcode = new string("ldc");
            s->args->push_back("0");
            this->stmt->push_back(s);
        }
        int index = frame->varIndex[this->idNode->variableName->name].index;
        if (typeStr == "I"){
            this->stmt->push_back(NewSimpleBinInstruction("istore", to_string(index)));
        }else if (typeStr == "J"){
            this->stmt->push_back(NewSimpleBinInstruction("lstore", to_string(index)));
        }else if (typeStr == "F"){
            this->stmt->push_back(NewSimpleBinInstruction("fstore", to_string(index)));
        }else if (typeStr == "D"){
            this->stmt->push_back(NewSimpleBinInstruction("dstore", to_string(index)));
        }else if (typeStr.size() == 1){
            this->stmt->push_back(NewSimpleBinInstruction("istore", to_string(index)));
        }else{
            this->stmt->push_back(NewSimpleBinInstruction("astore", to_string(index)));
        }
    }
}

VariableInitializerNode::VariableInitializerNode(int isSingleExpr, ExprNode *expr) {
    this->isSingleExpr = isSingleExpr;
    this->expr = expr;
    this->array = NULL;
}

VariableInitializerNode::VariableInitializerNode(int isSingleExpr, vector<VariableInitializerNode*> *array) {
    this->isSingleExpr = isSingleExpr;
    this->expr = NULL;
    this->array = array;
}

void VariableInitializerNode::Visit() {
    if (this->isSingleExpr) this->expr->Visit();
    else {
        for (auto node : *this->array) {
            node->Visit();
        }
    }
}

void VariableInitializerNode::codeGen(JContext *context) {
    if (isSingleExpr){
        expr->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            expr->stmt->begin(),
            expr->stmt->end()
        );
    }else{
        // TODO: array initialization
    }
}