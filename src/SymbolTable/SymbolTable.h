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
    
    VarNode(vector<ModifierType> *varModifierType, const string& Name, TypeTypeNode* varType, int ScopeLv) {
        this->varName = Name;
        this->varType = varType;
        this->varModifierType = varModifierType;
        this->scopeLv = ScopeLv;
    };
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

    MethodNode(vector<ModifierType> *methodModifierTypesList, string MethodName, vector<FormalParamNode*> *Params, TypeTypeNode *returnType);
    MethodNode *nextMethod;
};

class ReturnMethodNode {
public:
    string methodName;
    vector<TypeTypeNode*> *ParamsList;
    TypeTypeNode *returnTypeList;
    vector<ModifierType> *methodModifierTypesList;
};

class SymbolTable {
public:
    int CurrentScope = 0;
    VarNode *varTableHead[MaxSize];
    MethodNode *methodTableHead[MaxSize];

    SymbolTable();
    
    int AddVarNode(vector<ModifierType> *varModifierType, const string& Name, TypeTypeNode* varType);
    int AddMethodNode(vector<ModifierType> *methodModifiers, const string& Name, vector<FormalParamNode*> *Params, TypeTypeNode* returnType);
    
    VarNode *SearchVar(const string& VarName);
    ReturnMethodNode *SearchMethod(const string& MethodName, vector<TypeTypeNode*> *paramTypes);

private:
    int HashVar(const string& nameOfVar);
    int HashMethod(const string& nameOfMethod);

    void PushScope();
    void PopScope();
};
