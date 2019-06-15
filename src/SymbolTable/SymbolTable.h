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
    VarNode *nextVar;

    VarNode(vector<ModifierType> *varModifierType, string Name, TypeTypeNode* varType, int ScopeLv);
    //Insert a Var and its info. into the table, including its name
    //type, dimension of array(0 for not an array), scope level
};

class MethodNode {
    public:
    string methodName;
    vector<vector<TypeTypeNode*>*> ParamsList;
    vector<TypeTypeNode*> *returnTypeList;
    vector<vector<ModifierType>> methodModifierTypesList;
    MethodNode *nextMethod;

    MethodNode(vector<ModifierType> *methodModifierTypesList, string MethodName, vector<FormalParamNode*> *Params, TypeTypeNode *returnType);
};

class ReturnMethodNode {
public:
    string methodName;
    vector<TypeTypeNode*> *ParamsList;
    TypeTypeNode *returnTypeList;
    vector<ModifierType> methodModifierTypesList;
    int result;
};

class SymbolTable {
public:
    int CurrentScope = 0;
    VarNode *varTableHead[MaxSize];
    MethodNode *methodTableHead[MaxSize];

    SymbolTable();

    int HashVar(string nameOfVar);
    int HashMethod(string nameOfMethod);

    void PushScope();
    void PopScope();
    
    int AddVarNode(vector<ModifierType> *varModifierType, string Name, TypeTypeNode* varType);
    int AddMethodNode(vector<ModifierType> *methodModifiers, string Name, vector<FormalParamNode*> *Params, TypeTypeNode* returnType);
    
    VarNode SearchVar(string VarName);
    ReturnMethodNode SearchMethod(string MethodName, vector<FormalParamNode*> *paramTypes);
};