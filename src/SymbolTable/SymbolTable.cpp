#include <iostream>
#include "SymbolTable.h"
#include <string>
#include <stdlib.h>
#include "../MetaType.h"

using namespace std;

class VarNode {
public:
    string varName;
    TypeTypeNode *varType;
    vector<ModifierType> *varModifierType;
    int scopeLv;
    VarNode *nextVar;

    VarNode(vector<ModifierType> *varModifierType, string Name, TypeTypeNode* varType, int ScopeLv){
        this->varName = Name;
        this->varType = varType;
        this->varModifierType = varModifierType;
        this->scopeLv = ScopeLv;
    };
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

class SymbolTable {
public:
    int CurrentScope = 0;

    int HashVar(string nameOfVar){
        const char *tmpName = nameOfVar.c_str();
        return atoi(tmpName)%MaxSize;
    };

    int HashMethod(string nameOfMethod){
        const char *tmpName = nameOfMethod.c_str();
        return atoi(tmpName)%MaxSize;
    }

    VarNode *varTableHead[MaxSize];
    MethodNode *methodTableHead[MaxSize];

    SymbolTable(){
        int initCount;
        for( initCount = 0;initCount < MaxSize;initCount++ ){    
            varTableHead[initCount]->nextVar = NULL;
            methodTableHead[initCount]->nextMethod = NULL;
        }
    }

    void PushScope(){
        CurrentScope++;
    }

    void PopScope(){
        VarNode *currNode = varTableHead[0]->nextVar;
        int goThroughCount;
        for( goThroughCount = 0;goThroughCount < MaxSize;goThroughCount++){
            while(currNode->scopeLv == CurrentScope){
                currNode = currNode->nextVar;
            }
            varTableHead[goThroughCount]->nextVar = currNode;
        }
        CurrentScope--;
    }

    int AddVarNode(vector<ModifierType> *varModifierType, string Name, TypeTypeNode* varType){
        VarNode *newVar;
        newVar->varModifierType = varModifierType;
        newVar->varName = Name;
        newVar->varType = varType;
        newVar->scopeLv = CurrentScope;

        newVar->nextVar = varTableHead[HashVar(newVar->varName)]->nextVar;
        varTableHead[HashVar(newVar->varName)]->nextVar = newVar;
    }

    int AddMethodNode(vector<ModifierType> *methodModifiers, string Name, vector<FormalParamNode*> *Params, TypeTypeNode* returnType){
        MethodNode *newMethod;
        newMethod->methodName = Name;
        int ParamCount;
        vector<TypeTypeNode*> *TmpMethod;
        for(ParamCount = 0;ParamCount <= Params->size;ParamCount++){
            TmpMethod->push_back((*Params)[ParamCount]->paramType);
        }
        newMethod->ParamsList.push_back(TmpMethod);

        newMethod->returnTypeList->push_back(returnType);
        newMethod->methodModifierTypesList.push_back(*methodModifiers);

        newMethod->nextMethod = methodTableHead[HashMethod(newMethod->methodName)]->nextMethod;
        methodTableHead[HashMethod(newMethod->methodName)]->nextMethod = newMethod; 
    }

    ReturnMethodNode SearchMethod(string MethodName, vector<FormalParamNode*> *paramTypes){
        MethodNode *tmpPtr;
        ReturnMethodNode toBeReturn;
        int TmpCount, sig;
        tmpPtr = methodTableHead[HashMethod(MethodName)];
        sig = 1;
        vector<TypeTypeNode*> *TmpMethod;
        for(TmpCount = 0;TmpCount <= paramTypes->size;TmpCount++)
            TmpMethod->push_back((*paramTypes)[TmpCount]->paramType);
        //vector<vector<TypeTypeNode*>*> ParamsList;
        TmpCount = 0;
        while(tmpPtr->methodName != MethodName || tmpPtr->ParamsList[TmpCount] != TmpMethod){
            TmpCount++;
            tmpPtr = tmpPtr->nextMethod;
            if(TmpCount > paramTypes->size){
                sig = 0;
                printf("No such method\n");
                break;
            }
        }
        if(sig == 1){
            toBeReturn.methodName = tmpPtr->methodName;
            toBeReturn.ParamsList = tmpPtr->ParamsList[TmpCount];
            toBeReturn.methodModifierTypesList = tmpPtr->methodModifierTypesList[TmpCount];
            toBeReturn.returnTypeList = (*tmpPtr->returnTypeList)[TmpCount];
        }
        toBeReturn.result = sig;

        return toBeReturn;
    }

    VarNode SearchVar(string VarName){
        VarNode *tmpPtr;
        int TmpCount, goThroughCount;
        tmpPtr = varTableHead[HashVar(VarName)];
        while( tmpPtr->varName != VarName ) {
            TmpCount++;
            tmpPtr = tmpPtr->nextVar;
            if(tmpPtr->nextVar == NULL){
                printf("No such variable\n");
                break;
            }
        }
        return *tmpPtr;
    }
};