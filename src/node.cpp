#include "node.h"
#include "MetaType.h"
#include "codeGen/predefined.hpp"
#include "SymbolTable/SymbolTable.h"
#include "utils/utils.hpp"
#include <iostream>
#include <sstream>

extern SymbolTable symTable;

using namespace std;
extern SymbolTable symTable;
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
    // Semantic Check
    symTable.PushScope();
    /* -------------- */


    this->typeInfo->Visit();
    this->nodeName->Visit();
    for (auto node : *this->params)
        node->Visit();
    /* ================= */
    symTable.CurrentScope--;
    /* ================= */
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
    if (!top->hasReturn)
        this->method->JStmts->push_back(NewSimpleNoParamsInstruction("return"));
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
            this->typeStr += "java/lang/String;";
        }else{
            for (auto id : *this->typeInfo){
                this->typeStr += id->name;
                if (id != *(this->typeInfo->end()-1)){
                    this->typeStr += '/';
                }
            }
            this->typeStr += ";";
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

FieldDeclNode::FieldDeclNode(TypeTypeNode *type, const string& str) {
    this->type = type;
    this->id = new IdentifierNode(str);
}

void FieldDeclNode::Visit() {
    this->type->Visit();
    this->id->Visit();
}

void FieldDeclNode::codeGen(JContext *context) {
    
}

FormalParamNode::FormalParamNode(TypeTypeNode *type, VariableDeclaratorIdNode *node) {
    this->paramType = type;
    this->declNode = node;
}

void FormalParamNode::Visit() {
    // Semantic Check
    if (symTable.SearchVar(this->declNode->variableName->name)->scopeLv == symTable.CurrentScope) {
        string errorStr = "Erro r :Duplicate local var decl - " + this->declNode->variableName->name;
        cout << errorStr << endl;
        exit(1);
    }
    symTable.AddVarNode(new vector<ModifierType>, this->declNode->variableName->name, paramType);
    /* -------------- */
    this->paramType->Visit();
    this->declNode->Visit();
}

void FormalParamNode::codeGen(JContext *context){
    debugInfo("codeGen enter FormalParamNode");
    this->paramType->codeGen(context);
    this->paramStr = new string(this->paramType->typeStr);
    string id = this->declNode->variableName->name;
    auto crtFrame = context->currentFrame.top();
    crtFrame->varIndex[id].index = crtFrame->frameNode->method->localLimit;
    crtFrame->varIndex[id].typeName = this->paramType->typeStr;
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
    this->stats = new vector<BlockStatementNode*>;
}

BlockNode::BlockNode(vector<BlockStatementNode*> *stats) {
    this->Jstmts = new vector<JStmt*>;
    this->stats = stats;
}

void BlockNode::Visit() {
    symTable.PushScope();
    for (auto node : *this->stats) {
        node->Visit();
    }
    symTable.PopScope();
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
    if (this->type == BLOCK_TYPE){
        this->block->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            block->Jstmts->begin(),
            block->Jstmts->end()
        );
    }
    //delegate to child node
    else if (this->type == EXPR_TYPE){
        this->stat1->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            this->stat1->stmt->begin(),
            this->stat1->stmt->end()
        );
    }else if(this->type == RETURN_TYPE){
        context->currentFrame.top()->hasReturn = true;
        this->stat1->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            this->stat1->stmt->begin(),
            this->stat1->stmt->end()
        );
        auto exprNode = dynamic_cast<ExprNode*>(this->stat1);
        switch (exprNode->exprType)
        {
        case INT_TYPE:
            this->stmt->push_back(NewSimpleNoParamsInstruction("ireturn"));
            break;
        case FLOAT_TYPE:
            this->stmt->push_back(NewSimpleNoParamsInstruction("freturn"));
            break;
        case DOUBLE_TYPE:
            this->stmt->push_back(NewSimpleNoParamsInstruction("dreturn"));
            break;
        case LONG_TYPE:
            this->stmt->push_back(NewSimpleNoParamsInstruction("lreturn"));
            break;
        case REFERENCE_TYPE:
            this->stmt->push_back(NewSimpleNoParamsInstruction("areturn"));
            break;
        default:
            break;
        }
    }else if (this->type == RETURN_NONE_TYPE){
        context->currentFrame.top()->hasReturn = true;
        this->stmt->push_back(NewSimpleNoParamsInstruction("return"));
    }else if (this->type == IF_STAT_TYPE){
        // ifeq 
        // L1
        this->stat1->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            this->stat1->stmt->begin(),
            this->stat1->stmt->end()
        );
        string label = "L" + context->currentFrame.top()->labelCounter++;
        this->stmt->push_back(NewSimpleBinInstruction("ifeq", label));
        this->stat2->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            this->stat2->stmt->begin(),
            this->stat2->stmt->end()
        );
        this->stmt->push_back(new JLabel(label));
    }else if (this->type == IF_ELSE_TYPE){
        //ifeq L1
        //    ...
        //   goto L2
        //L1:
        //  ....
        //L2:
        this->stat1->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            this->stat1->stmt->begin(),
            this->stat1->stmt->end()
        );
        string L1 = "L" + context->currentFrame.top()->labelCounter++;
        this->stmt->push_back(NewSimpleBinInstruction("ifeq", L1));
        this->stat2->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            this->stat2->stmt->begin(),
            this->stat2->stmt->end()
        );
        string L2 = "L" + context->currentFrame.top()->labelCounter++;
        this->stmt->push_back(NewSimpleBinInstruction("goto", L2));
        this->stmt->push_back(new JLabel(L1));
        this->stat3->codeGen(context);
        this->stmt->push_back(new JLabel(L2));
    } else if (this->type == WHILE_STAT_TYPE){
        // L1:
        // ... 
        // ifeq L2
        // ...
        // goto L1
        string L1 = "L" + context->currentFrame.top()->labelCounter++;
        this->stmt->push_back(new JLabel(L1));
        this->stat1->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            this->stat1->stmt->begin(),
            this->stat1->stmt->end()
        );
        string L2 = "L" + context->currentFrame.top()->labelCounter++;
        this->stmt->push_back(NewSimpleBinInstruction("ifeq", L2));
        this->stat2->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            this->stat2->stmt->begin(),
            this->stat2->stmt->end()
        );
        this->stmt->push_back(NewSimpleBinInstruction("goto", L1));
    } else if (this->type == FOR_STAT_TYPE){
        // ... init stmts
        // L1 cmp stmts
        // ifeq L2
        // block stmts
        // finish stmts
        // L2
        this->forControl->init->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            forControl->init->stmt->begin(),
            forControl->init->stmt->end()
        );
        string L1 = "L" + context->currentFrame.top()->labelCounter++;
        string L2 = "L" + context->currentFrame.top()->labelCounter++;
        this->stmt->push_back(new JLabel(L1));
        this->forControl->CmpExpr->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            forControl->CmpExpr->stmt->begin(),
            forControl->CmpExpr->stmt->end()
        );
        this->stmt->push_back(NewSimpleBinInstruction("ifeq", L2));
        this->stat1->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            this->stat1->stmt->begin(),
            this->stat1->stmt->end()
        );
        for (auto expr: *this->forControl->finishExprList){
            expr->codeGen(context);
            this->stmt->insert(
                this->stmt->end(),
                expr->stmt->begin(),
                expr->stmt->end()
            );
        }
        this->stmt->push_back(new JLabel(L2));
    }
    context->nodeStack.pop();
    debugInfo("codeGen exit StatementNode");
}

void Statement::codeGen(JContext* context){
    cerr << "ERROR! This should not be entered!" << endl;
}

ExprNode::ExprNode(ExprStatType type, PrimaryNode *node) {
    this->type = type;
    this->primary = node;
    this->ids = NULL;
    this->methodCallParams = NULL;
    this->subExpr1 = this->subExpr2 = NULL;
    this->ArrayIndexQueryList = NULL;
}

ExprNode::ExprNode(ExprStatType type, vector<IdentifierNode*> *ids) {
    this->type = type;
    this->primary = NULL;
    this->ids = ids;
    this->methodCallParams = NULL;
    this->subExpr1 = this->subExpr2 = NULL;
    this->ArrayIndexQueryList = NULL;
}

ExprNode::ExprNode(ExprStatType type, vector<IdentifierNode*> *ids, MethodCallParamsNode *methodCallParams) {
    this->type = type;
    this->primary = NULL;
    this->ids = ids;
    this->methodCallParams = methodCallParams;
    this->subExpr1 = this->subExpr2 = NULL;
    this->ArrayIndexQueryList = NULL;
}

ExprNode::ExprNode(ExprStatType type, const string& id, MethodCallParamsNode *methodCallParams) {
    this->type = type;
    this->primary = NULL;
    this->ids = new vector<IdentifierNode*>;
    this->ids->push_back(new IdentifierNode(id));
    this->methodCallParams = methodCallParams;
    this->subExpr1 = this->subExpr2 = NULL;
    this->ArrayIndexQueryList = NULL;
}

ExprNode::ExprNode(ExprStatType type, ExprNode *node) {
    this->type = type;
    this->primary = NULL;
    this->ids = NULL;
    this->methodCallParams = NULL;
    this->subExpr1 = node;
    this->subExpr2 = NULL;
    this->ArrayIndexQueryList = NULL;
}

ExprNode::ExprNode(ExprStatType type, ExprNode *node1, ExprNode *node2) {
    this->type = type;
    this->primary = NULL;
    this->ids = NULL;
    this->methodCallParams = NULL;
    this->subExpr1 = node1;
    this->subExpr2 = node2;
    this->ArrayIndexQueryList = NULL;
}

ExprNode::ExprNode(ExprStatType type, const string& id, vector<ExprNode*> *ArrayIndexQueryList) {
    this->type = type;
    this->primary = NULL;
    this->ids = new vector<IdentifierNode*>;
    this->ids->push_back(new IdentifierNode(id));
    this->methodCallParams = NULL;
    this->subExpr1 = this->subExpr2 = NULL;
    this->ArrayIndexQueryList = this->ArrayIndexQueryList;
}

ExprNode::ExprNode(ExprStatType type, vector<IdentifierNode*> *ids, vector<ExprNode*> *ArrayIndexQueryList) {
    this->type = type;
    this->primary = NULL;
    this->ids = ids;
    this->methodCallParams = NULL;
    this->subExpr1 = this->subExpr2 = NULL;
    this->ArrayIndexQueryList = this->ArrayIndexQueryList;
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
    if (this->ArrayIndexQueryList != NULL) {
        for (auto node : *this->ArrayIndexQueryList) {
            node->Visit();
        }
    }

    if (this->type == IDEN_METHOD || this->type == IDEN_DOT_METHOD) {
        string methodName = IdsToString();
        ReturnMethodNode *rtn = symTable.SearchMethod( methodName, this->methodCallParams->exprs);
        if (rtn == NULL) {
            string errorStr = "Error : Unrecognized method call - " + methodName;
            cout << errorStr << endl;
            exit(1);
        }
        this->valType = rtn->returnType;
        this->val = new ExprValInfo(0);
        this->assignable = 0;
    } else if (this->type == IDEN_DOT || this->type == IDEN_ARRAY || this->type == IDEN_DOT_ARRAY) {
        string varName = IdsToString();
        VarNode *rtn = symTable.SearchVar(varName);
        if (rtn == NULL) {
            string errorStr = "Error : Unrecognized identifier - " + varName;
            cout << errorStr << endl;
            exit(1);
        }
        this->valType = rtn->varType;
        this->val = new ExprValInfo(0);
        this->assignable = 1;
    } else if (this->type == PRIMARY_TYPE) {
        PrimaryNode *pmnode = this->primary;
        if (pmnode->type == PRIMARY_EXPR) {
            this->valType = pmnode->expr->valType;
            this->val = pmnode->expr->val;
            this->assignable = pmnode->expr->assignable;
        } else if (pmnode->type == PRIMARY_THIS || pmnode->type == PRIMARY_SUPER) {
            // TODO
            this->valType = NULL;
            this->val = new ExprValInfo(0);
            this->assignable = 0;
        } else if (pmnode->type == PRIMARY_LITERAL) {
            this->valType = new TypeTypeNode(LtoP_map.at(pmnode->literal->type));
            if (pmnode->literal->type == STRING_LIT) {
                this->valType->typeInfo = new vector<IdentifierNode*>;
                this->valType->typeInfo->push_back(new IdentifierNode("String"));
            } // NO RULE FOR NULL LITERAL - NONPR_TYPE and typeInfo == NULL
            if (this->valType->type == LONG_PTYPE || this->valType->type == BOOLEAN_PTYPE) {
                this->val = new ExprValInfo(pmnode->literal->intVal);
            } else if (this->valType->type == DOUBLE_PTYPE) {
                this->val = new ExprValInfo(pmnode->literal->floatVal);
            } else if (pmnode->literal->type == STRING_LIT) {
                this->val = new ExprValInfo(pmnode->literal->stringVal);
            }
            this->assignable = 0;
        } else if (pmnode->type == PRIMARY_IDEN) {
            VarNode *rtn = symTable.SearchVar(pmnode->id->name);
            if (rtn == NULL) {
                string errorStr = "Error : Unrecognized identifier - " + pmnode->id->name;
                cout << errorStr << endl;
                exit(1);
            }
            this->valType = rtn->varType;
            this->val = new ExprValInfo(0);
            this->assignable = 0;
        }
    } else {
        // TODO
    }
}

string ExprNode::IdsToString() {
    string finalName = (*this->ids)[0]->name;
    for (int i = 1; i < this->ids->size(); i++) {
        finalName += "." + (*this->ids)[0]->name;
    }
    return finalName;
}

// MAYBE TODO
void ExprNode::codeGen(JContext *context){
    debugInfo("codeGen enter ExprNode");
    debugInfo(to_string(this->type));
    // TODO: translate all expr type
    if (this->type == IDEN_METHOD || this->type == IDEN_DOT_METHOD){
        // replace predefined 
        auto res = CheckAndReplacePredefined(context,this);
        if (res != nullptr){
            this->stmt->insert(
                this->stmt->end(),
                res->begin(),
                res->end()
            );
        }
        // push context
        context->nodeStack.push(this);
        for (auto params : *methodCallParams->exprs){
            params->codeGen(context);
            this->stmt->insert(this->stmt->end(), 
                params->stmt->begin(),
                params->stmt->end());
        }
        context->nodeStack.pop();

        string fullId = IDVecToStringSlash(this->ids);
        string fullDotId = IDVecToStringDot(this->ids);
        string desc = "(";
        for (auto s : *this->methodCallParams->exprs){
            desc += s->ExprTypeStr + ';';
        }
        desc = desc.substr(0, desc.size() - 1);
        string descriptor;
        auto it = predefSymbolTable.find(fullId);
        if (it != predefSymbolTable.end()){
            for (auto s: it->second){
                if (s.rfind(desc, 0) == 0){
                    descriptor = s;
                    break;
                }
            }
        }else {
            //auto res = symTable.SearchMethod(fullDotId, this->methodCallParams->)
        }
        // TODO: invokestatic invokespecial
        JInstructionStmt *s = NewSimpleBinInstruction("invokevirtual", fullId + descriptor);

        this->stmt->push_back(s);
        auto pos = descriptor.find(")");
        this->ExprTypeStr = descriptor.substr(pos, descriptor.size() - pos);
    } else if (this->type == PRIMARY_TYPE){
        this->primary->codeGen(context);
        this->stmt->insert(this->stmt->end(),
            this->primary->stmt->begin(),
            this->primary->stmt->end()
            );
        // get type
        this->ExprTypeStr = this->primary->ExprTypeStr;
    } else if (this->type == OP_ADD){
        if (this->subExpr1->exprType == this->subExpr2->exprType){
            this->exprType = this->subExpr1->exprType;
            switch (this->subExpr1->exprType)
            {
            case INT_TYPE:
                this->ExprTypeStr = "I";
                this->stmt->push_back(NewSimpleNoParamsInstruction("iadd"));
                break;
            case FLOAT_TYPE:
                this->ExprTypeStr = "F";
                this->stmt->push_back(NewSimpleNoParamsInstruction("fadd"));
                break;
            case DOUBLE_TYPE:
                this->ExprTypeStr = "D";
                this->stmt->push_back(NewSimpleNoParamsInstruction("dadd"));
                break;
            case LONG_TYPE:
                this->ExprTypeStr = "J";
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
    debugInfo("codeGen exit ExprNode");
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
    debugInfo(to_string(this->type));
    // TODO:
    if (this->type == PRIMARY_LITERAL){
        this->literal->codeGen(context);
        this->stmt->insert(this->stmt->end(),
            this->literal->stmt->begin(),
            this->literal->stmt->end());
    }else if (this->type == PRIMARY_IDEN){
        auto indexInfo = context->currentFrame.top()->varIndex[this->id->name];
        if (indexInfo.typeName == "I" || indexInfo.typeName == "C" || indexInfo.typeName == "Z"){
            this->stmt->push_back(NewSimpleBinInstruction("iload", to_string(indexInfo.index)));
        }else if (indexInfo.typeName == "J"){
            this->stmt->push_back(NewSimpleBinInstruction("lload", to_string(indexInfo.index)));
        }else if (indexInfo.typeName == "F"){
            this->stmt->push_back(NewSimpleBinInstruction("fload", to_string(indexInfo.index)));
        }else if (indexInfo.typeName == "D"){
            this->stmt->push_back(NewSimpleBinInstruction("dload", to_string(indexInfo.index)));
        }else{
            this->stmt->push_back(NewSimpleBinInstruction("aload", to_string(indexInfo.index)));
        }
    }
    debugInfo("codeGen exit PrimaryNode");
}

LiteralNode::LiteralNode(LiteralType type, const string& val) {
    this->type = type;
    
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
    debugInfo("codeGen enter LiteralNode");
    // complete
    cout << this->type << endl;
    if (this->type == STRING_LIT){
        JInstructionStmt *s = new JInstructionStmt;
        s->opcode = new string("ldc");
        s->args = new vector<string>;
        s->args->push_back(stringVal);
        this->stmt->push_back(s);
        IncrStack(context);
        this->ExprTypeStr = "Ljava/lang/String;";
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
        switch (this->type)
        {
        case INTEGER_LIT:
            this->ExprTypeStr = "I";
            break;
        case FLOAT_LIT:
            this->ExprTypeStr = "F";
            break;
        case CHAR_LIT:
            this->ExprTypeStr = "C";
            break;
        case BOOL_LIT:
            this->ExprTypeStr = "Z";
            break;
        default:
            break;
        }
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

LocalVariableDeclNode::LocalVariableDeclNode(int isFinal, TypeTypeNode *type, vector<VariableDeclaratorNode*> *decls) {
    this->isFinal = isFinal;
    this->type = type;
    this->decls = decls;
}

void LocalVariableDeclNode::Visit() {
    // Semantic Check
    vector<ModifierType> *tmp = new vector<ModifierType>;
    if (this->isFinal) tmp->push_back(FINAL_TYPE);
    for (auto node : *this->decls) {
        if (symTable.SearchVar(node->idNode->variableName->name)->scopeLv == symTable.CurrentScope) {
            string errorStr = "Error : Duplicate local var decl - " + node->idNode->variableName->name;
            cout << errorStr << endl;
            exit(1);
        }
        symTable.AddVarNode(tmp, node->idNode->variableName->name, this->type);
    }
    /* -------------- */

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
    if (this->isVarDecl){
        this->varDecl->codeGen(context);
        this->stmt->insert(
            this->stmt->end(),
            this->varDecl->stmt->begin(),
            this->varDecl->stmt->end()
        );
    }else{
        for (auto expr : *this->exprs){
            expr->codeGen(context);
            this->stmt->insert(
                this->stmt->end(),
                expr->stmt->begin(),
                expr->stmt->end()
            );
        }
    }
}