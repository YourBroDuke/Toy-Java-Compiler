#include <iostream>
#include <string>
#include <vector>
#include "../node.h"

#define MaxSize 1000

using namespace std;

class VarNode {
public:
    int varId;//VarId = HashVar(VaribleNode) Unique identifier
    string Name;
    TypeTypeNode* varType;
    int scopeLv;

    VarNode(string Name, TypeTypeNode* varType, int ScopeLv);
    //Insert a Var and its info. into the table, including its name
    //type, dimension of array(0 for not an array), scope level
};

class MethodNode {
public:
    int methodId;//MethodId = HashVar(MethodNode) Unique identifier
    string methodName;
    vector<TypeTypeNode*> Params;
    TypeTypeNode* returnType;

    MethodNode(string MethodName, TypeTypeNode* returnType);
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

    void PopScope(int ScopeLv);
    
    void PushMethod(string MethodName, TypeTypeNode* returnType);

    MethodNode SearchMethod(string MethodName);
    VarNode SearchVar(string VarName);
};