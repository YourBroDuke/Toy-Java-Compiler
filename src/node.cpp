#include "node.h"
#include "MetaType.h"
#include <iostream>
#include <sstream>
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
    if (this->type == CLASS_TYPE) {
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

MemberDeclNode::MemberDeclNode(MemberDeclType declType, Node *decl) {
    this->declType = declType;
    this->modifiers = new vector<ModifierType>;
    this->mainDecl = decl;
}
MemberDeclNode::MemberDeclNode(MemberDeclType declType, vector<ModifierType> *modifiers, Node *decl) {
    this->declType = declType;
    this->modifiers = modifiers;
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
MethodDeclNode::MethodDeclNode(TypeTypeNode *type, const string& name, vector<FormalParamNode*> *params, BlockNode *block) {
    this->typeInfo = type;
    this->nodeName = new IdentifierNode(name);
    this->params = params;
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
    context->currentFrame = this;
    
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
    context->currentFrame = nullptr;

    context->classFile->JMethods = new vector<JMethod*>;
    context->classFile->JMethods->push_back(this->method);
    debugInfo("codeGen exit MethodDeclNode");
}

TypeTypeNode::TypeTypeNode(PrimitiveTypeOrNot type) {
    this->type = type;
    this->typeInfo = NULL;
    this->arrayDim = 0;
}

TypeTypeNode::TypeTypeNode(PrimitiveTypeOrNot type, int arrayDim) {
    this->type = type;
    this->typeInfo = NULL;
    this->arrayDim = arrayDim;
}

TypeTypeNode::TypeTypeNode(PrimitiveTypeOrNot type, vector<IdentifierNode*> *typeInfo) {
    this->type = type;
    this->typeInfo = typeInfo;
    this->arrayDim = 0;
}

TypeTypeNode::TypeTypeNode(PrimitiveTypeOrNot type, vector<IdentifierNode*> *typeInfo, int arrayDim) {
    this->type = type;
    this->typeInfo = typeInfo;
    this->arrayDim = arrayDim;
}

TypeTypeNode::TypeTypeNode(PrimitiveTypeOrNot type, const string& id) {
    this->type = type;
    this->typeInfo = new vector<IdentifierNode*>;
    this->typeInfo->push_back(new IdentifierNode(id));
    this->arrayDim = 0;
}

TypeTypeNode::TypeTypeNode(PrimitiveTypeOrNot type, const string& id, int arrayDim) {
    this->type = type;
    this->typeInfo = new vector<IdentifierNode*>;
    this->typeInfo->push_back(new IdentifierNode(id));
    this->arrayDim = arrayDim;
}

// TODO
void TypeTypeNode::printType() {
    if (this->type != NONPR_TYPE)
        cout << "This is a " << PrimitiveTypeOrNotMap.at(this->type) << " type method" << endl;
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

// TODO
void TypeTypeNode::Visit() {
    this->printType();

    if (this->typeInfo == NULL) return;
    for (auto node : *this->typeInfo)
        node->Visit();
    
    cout << "It has " << this->arrayDim << " dimensions" << endl;
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
    this->stats = new vector<BlockStatementNode*>;
}

BlockNode::BlockNode(vector<BlockStatementNode*> *stats) {
    this->Jstmts = new vector<JStmt*>;
    this->stats = stats;
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

StatementNode::StatementNode(StatementType type) {
    this->type = type;
    this->block = NULL;
    this->stat1 = this->stat2 = this->stat3 = NULL;
    this->forControl = NULL;
}

StatementNode::StatementNode(StatementType type, BlockNode *block) {
    this->type = type;
    this->block = block;
    this->stat1 = this->stat2 =this->stat3 = NULL;
    this->forControl = NULL;
}

StatementNode::StatementNode(StatementType type, Statement *stat) {
    this->type = type;
    this->stat1 = stat;
    this->block = NULL;
    this->stat2 = this->stat3 = NULL;
    this->forControl = NULL;
}

StatementNode::StatementNode(StatementType type, Statement *stat1, Statement *stat2) {
    this->type = type;
    this->stat1 = stat1;
    this->stat2 = stat2;
    this->block = NULL;
    this->stat3 = NULL;
    this->forControl = NULL;

    // If the expression of control is empty means always true
    if ((type == WHILE_STAT_TYPE || type == DO_WHILE_STAT_TYPE) && stat1 == NULL) {
        LiteralNode *tmpLit = new LiteralNode(BOOL_LIT, "true");
        PrimaryNode *tmpPri = new PrimaryNode(PRIMARY_LITERAL, tmpLit);
        this->stat1 = new ExprNode(PRIMARY_TYPE, tmpPri);
    }
}

StatementNode::StatementNode(StatementType type, Statement *stat1, Statement *stat2, Statement *stat3) {
    this->type = type;
    this->stat1 = stat1;
    this->stat2 = stat2;
    this->stat3 = stat3;
    this->block = NULL;
    this->forControl = NULL;
}
StatementNode::StatementNode(StatementType type, ForControlNode *forControl, Statement *stat) {
    this->type = type;
    this->forControl = forControl;
    this->stat1 = stat;
    this->block = NULL;
    this->stat2 = this->stat3 = NULL;
}

// TODO
void StatementNode::printType() {
    cout << "statement type : " << StatementTypeMap_forVisit.at(this->type) << endl;
}

void StatementNode::Visit() {
    this->printType();
    if (this->block != NULL) this->block->Visit();
    if (this->stat1 != NULL) this->stat1->Visit();
    if (this->stat2 != NULL) this->stat2->Visit();
    if (this->stat3 != NULL) this->stat3->Visit();
    if (this->forControl != NULL) this->forControl->Visit();
}

// TODO
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

ExprNode::ExprNode(ExprType type, vector<IdentifierNode*> *ids) {
    this->type = type;
    this->primary = NULL;
    this->ids = ids;
    this->methodCallParams = NULL;
    this->subExpr1 = this->subExpr2 = NULL;
}

ExprNode::ExprNode(ExprType type, vector<IdentifierNode*> *ids, MethodCallParamsNode *methodCallParams) {
    this->type = type;
    this->primary = NULL;
    this->ids = ids;
    this->methodCallParams = methodCallParams;
    this->subExpr1 = this->subExpr2 = NULL;
}

ExprNode::ExprNode(ExprType type, const string& id, MethodCallParamsNode *methodCallParams) {
    this->type = type;
    this->primary = NULL;
    this->ids = new vector<IdentifierNode*>;
    this->ids->push_back(new IdentifierNode(id));
    this->methodCallParams = methodCallParams;
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

// TODO
void ExprNode::Visit() {
    if (this->primary != NULL) this->primary->Visit();
    if (this->ids != NULL) {
        for (auto node : *this->ids)
            node->Visit();
    }
    if (this->methodCallParams != NULL)
        this->methodCallParams->Visit();
    if (this->subExpr1 != NULL)
        this->subExpr1->Visit();
    if (this->subExpr2 != NULL)
        this->subExpr2->Visit();
}

// MAYBE TODO
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
        
    }
}

MethodCallParamsNode::MethodCallParamsNode() {
    this->exprs = new vector<ExprNode*>;
}

MethodCallParamsNode::MethodCallParamsNode(vector<ExprNode*> *exprs) {
    this->exprs = exprs;
}

void MethodCallParamsNode::Visit() {
    for (auto node : *this->exprs)
        node->Visit();
}

void MethodCallParamsNode::codeGen(JContext* context) {
    // ignore for now
    // TODO:
}

PrimaryNode::PrimaryNode(PrimaryNodeType type) {
    this->type = type;
    this->expr = NULL;
    this->literal = NULL;
    this->id = NULL;
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

// TODO
void PrimaryNode::Visit() {
    // this->printType()
    if (this->expr != NULL)
        this->expr->Visit();
    if (this->literal != NULL)
        this->literal->Visit();
    if (this->id != NULL)
        this->id->Visit();
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

LiteralNode::LiteralNode(LiteralType type, const string& val) {
    if (type == CHAR_LIT) {
        // TODO
        this->intVal = 255;
    } else if (type == STRING_LIT) {
        this->stringVal = val;
    } else if (type == BOOL_LIT) {
        this->intVal = val=="true" ? 1 : 0;
    } else if (type == NULL_LIT) {
        this->stringVal = val;
    } else if (type == INTEGER_LIT) {
        this->intVal = StrToInt(val);
    } else if (type == FLOAT_LIT) {
        this->floatVal = StrToFloat(val);
    }
}

int64_t LiteralNode::StrToInt(const string& str) {
    int64_t ans;
    stringstream ss;
    ss << str;
    ss >> ans;
    return ans;
}

double LiteralNode::StrToFloat(const string& str) {
    double ans;
    stringstream ss;
    ss << str;
    ss >> ans;
    return ans;
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
    if (context->currentFrame != nullptr){
        context->currentFrame->method->stackLimit++;
    }
}

LocalVariableDeclNode::LocalVariableDeclNode(int isFinal, TypeTypeNode *type, vector<VariableDeclaratorNode*> *decls) {
    this->isFinal = isFinal;
    this->type = type;
    this->decls = decls;
}

void LocalVariableDeclNode::Visit() {
    if (this->isFinal) cout << "final variable" << endl;
    this->type->Visit();
    for (auto node : *this->decls) {
        node->Visit();
    }
}

void LocalVariableDeclNode::codeGen(JContext *context) {

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

}

ForControlNode::ForControlNode(ForInitNode *init) {
    this->init;
    LiteralNode *tmpLit = new LiteralNode(BOOL_LIT, "true");
    PrimaryNode *tmpPri = new PrimaryNode(PRIMARY_LITERAL, tmpLit);
    this->CmpExpr = new ExprNode(PRIMARY_TYPE, tmpPri);
    this->finishExprList = new vector<ExprNode*>;
}

ForControlNode::ForControlNode(ForInitNode *init, ExprNode *CmpExpr) {
    this->init = init;
    this->CmpExpr = CmpExpr;
    this->finishExprList = new vector<ExprNode*>;
}

ForControlNode::ForControlNode(ForInitNode *init, ExprNode *CmpExpr, vector<ExprNode*> *exprs) {
    this->init = init;
    this->CmpExpr = CmpExpr;
    this->finishExprList = exprs;
}

ForControlNode::ForControlNode(ForInitNode *init, vector<ExprNode*> *exprs) {
    this->init = init;
    LiteralNode *tmpLit = new LiteralNode(BOOL_LIT, "true");
    PrimaryNode *tmpPri = new PrimaryNode(PRIMARY_LITERAL, tmpLit);
    this->CmpExpr = new ExprNode(PRIMARY_TYPE, tmpPri);
    this->finishExprList = exprs;
}

void ForControlNode::Visit() {
    cout << "FOR statement:\n Init:" << endl;
    this->init->Visit();
    this->CmpExpr->Visit();
    for (auto node : *this->finishExprList) {
        node->Visit();
    }
}

void ForControlNode::codeGen(JContext *context) {
    
}

ForInitNode::ForInitNode(int isVarDecl, LocalVariableDeclNode *varDecl) {
    this->isVarDecl = isVarDecl;
    this->varDecl = varDecl;
    this->exprs = NULL;
}

ForInitNode::ForInitNode(int isVarDecl, vector<ExprNode*> *exprs) {
    this->isVarDecl =isVarDecl;
    this->varDecl = NULL;
    this->exprs = exprs;
}

void ForInitNode::Visit() {
    if (isVarDecl) {
        cout << "This is an local var decl" << endl;
        this->varDecl->Visit();
    } else {
        for (auto node : *this->exprs) {
            node->Visit();
        }
    }
}

void ForInitNode::codeGen(JContext *context) {

}