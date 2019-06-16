#include <iostream>
#include <string>
#include <vector>
#include "../node.h"
#include "../MetaType.h"

#define MaxSize 1000

using namespace std;

class VarNode {
public:
    string varName;
    TypeTypeNode *varType;
    vector<ModifierType> *varModifierType;
    int scopeLv;
    
    VarNode() {
        this->varType = NULL;
        this->varModifierType = NULL;
        this->scopeLv = 0;
        this->nextVar = NULL;
    }
    VarNode(vector<ModifierType> *varModifierType, const string& Name, TypeTypeNode* varType, int ScopeLv) {
        this->varName = Name;
        this->varType = varType;
        this->varModifierType = varModifierType;
        this->scopeLv = ScopeLv;
        this->nextVar = NULL;
    }
    //Insert a Var and its info. into the table, including its name
    //type, dimension of array(0 for not an array), scope level
    VarNode *nextVar;
};

class MethodNode {
public:
    string methodName;
    vector<vector<TypeTypeNode*>*> ParamsList;
    vector<TypeTypeNode*> returnTypeList;
    vector<vector<ModifierType>*> methodModifierTypesList;

    MethodNode() {
        this->nextMethod = NULL;
    }
    MethodNode(vector<ModifierType> *methodModifierTypesList, const string& MethodName, vector<FormalParamNode*> *Params, TypeTypeNode *returnType) {
        this->methodName = MethodName;
        vector<TypeTypeNode*>* typeList = new vector<TypeTypeNode*>;
        for (auto node : *Params) {
            typeList->push_back(node->paramType);
        }
        this->ParamsList.push_back(typeList);
        this->returnTypeList.push_back(returnType);
        this->methodModifierTypesList.push_back(methodModifierTypesList);
        this->nextMethod = NULL;
    }
    MethodNode *nextMethod;
};

class ReturnMethodNode {
public:
    string methodName;
    vector<TypeTypeNode*> *ParamsList;
    TypeTypeNode *returnType;
    vector<ModifierType> *methodModifierTypesList;

    ReturnMethodNode(const string& name, vector<TypeTypeNode*> *ParamsList, TypeTypeNode *returnType, vector<ModifierType> *methodModifierTypesList) {
        this->methodName = name;
        this->ParamsList = ParamsList;
        this->returnType = returnType;
        this->methodModifierTypesList = methodModifierTypesList;
    }
    ~ReturnMethodNode() {

    }
};

class SymbolTable {
public:
    int CurrentScope;
    VarNode* varTableHead[MaxSize];
    MethodNode* methodTableHead[MaxSize];

    SymbolTable();

    void PushScope();
    void PopScope();
    
    int AddVarNode(vector<ModifierType> *varModifierType, const string& Name, TypeTypeNode* varType);
    int AddMethodNode(vector<ModifierType> *methodModifiers, const string& Name, vector<FormalParamNode*> *Params, TypeTypeNode* returnType);

    VarNode *SearchVar(const string& VarName);
    ReturnMethodNode *SearchMethod(const string& MethodName, vector<TypeTypeNode*> *paramTypes);
    ReturnMethodNode *SearchMethod(const string& MethodName, vector<FormalParamNode*> *Params);
    ReturnMethodNode *SearchMethod(const string& MethodName, vector<ExprNode*> *exprs);
private:
    int HashVar(const string& nameOfVar);
    int HashMethod(const string& nameOfMethod);
};
