#include <iostream>
#include <string>
#include <vector>
#include "../node.h"

#define MaxSize 1000

using namespace std;

class VarNode {
public:
    string Name;
    TypeTypeNode *varType;
    vector<ModifierType> *varModifierType;
    int scopeLv;

    VarNode(string Name, TypeTypeNode* varType, vector<ModifierType> *varModifierType, int ScopeLv);
    //Insert a Var and its info. into the table, including its name
    //type, dimension of array(0 for not an array), scope level
};

class MethodNode {
public:
    string methodName;
    vector<vector<TypeTypeNode*>*> ParamsList;
    vector<TypeTypeNode*> *returnTypeList;
    vector<vector<ModifierType>*> *methodModifierTypesList;

    MethodNode(string MethodName, vector<FormalParamNode*> *Params, TypeTypeNode *returnType);
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

    int HashVar(VarNode);
    int HashMethod(MethodNode);

    VarNode* VarTable[MaxSize];
    MethodNode* MethodTable[MaxSize];

    void PushScope(){
        CurrentScope++;
    }

    void PopScope();

    int AddVarNode(vector<ModifierType> *varModifierType, string Name, TypeTypeNode* varType);
    int AddMethodNode(vector<ModifierType> *methodModifiers, string Name, vector<FormalParamNode*> *Params, TypeTypeNode* returnType);

    MethodNode SearchMethod(string MethodName, vector<TypeTypeNode*> *paramTypes);
    VarNode SearchVar(string VarName);
};