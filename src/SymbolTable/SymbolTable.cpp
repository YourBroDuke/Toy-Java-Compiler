#include <iostream>
#include "SymbolTable.h"
#include <string>
#include <stdlib.h>
#include "../MetaType.h"

using namespace std;


SymbolTable::SymbolTable() {
    int initCount;
    for( initCount = 0;initCount < MaxSize;initCount++ ){    
        varTableHead[initCount]->nextVar = NULL;
        methodTableHead[initCount]->nextMethod = NULL;
    }
}

int SymbolTable::HashVar(const string& nameOfVar) {
    int count, returnNum;
    for(count = 0; count < nameOfVar.length();count++ )
        returnNum += nameOfVar[count];
    returnNum = (returnNum * returnNum * returnNum / 2)%MaxSize;
}

int SymbolTable::HashMethod(const string& nameOfMethod) {
    int count, returnMeth;
    for(count = 0; count < nameOfMethod.length();count++)
        returnMeth += nameOfMethod[count];
    returnMeth = (returnMeth * returnMeth * returnMeth / 2)%MaxSize;
}

void SymbolTable::PopScope() {
    CurrentScope++;
}

void SymbolTable::PushScope() {
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

int SymbolTable::AddVarNode(vector<ModifierType> *varModifierType, const string& Name, TypeTypeNode* varType){
    VarNode *newVar;
    newVar->varModifierType = varModifierType;
    newVar->varName = Name;
    newVar->varType = varType;
    newVar->scopeLv = CurrentScope;

    newVar->nextVar = varTableHead[HashVar(newVar->varName)]->nextVar;
    varTableHead[HashVar(newVar->varName)]->nextVar = newVar;
}

int SymbolTable::AddMethodNode(vector<ModifierType> *methodModifiers, const string& Name, vector<FormalParamNode*> *Params, TypeTypeNode* returnType){
    MethodNode *newMethod;
    newMethod->methodName = Name;
    int ParamCount;
    vector<TypeTypeNode*> *TmpMethod;
    for(ParamCount = 0;ParamCount <= Params->size(); ParamCount++){
        TmpMethod->push_back((*Params)[ParamCount]->paramType);
    }
    newMethod->ParamsList.push_back(TmpMethod);

    newMethod->returnTypeList.push_back(returnType);
    newMethod->methodModifierTypesList.push_back(methodModifiers);

    newMethod->nextMethod = methodTableHead[HashMethod(newMethod->methodName)]->nextMethod;
    methodTableHead[HashMethod(newMethod->methodName)]->nextMethod = newMethod; 
}

ReturnMethodNode *SymbolTable::SearchMethod(const string& MethodName, vector<TypeTypeNode*> *paramTypes){
    MethodNode *tmpPtr;
    ReturnMethodNode toBeReturn;
    int TmpCount, sig;
    tmpPtr = methodTableHead[HashMethod(MethodName)]->nextMethod;

    paramTypes = paramTypes;
    TmpCount = 0;
    while(tmpPtr->methodName != MethodName || tmpPtr->ParamsList[TmpCount] != paramTypes){
        TmpCount++;
        tmpPtr = tmpPtr->nextMethod;
        if(TmpCount > paramTypes->size()){
            sig = 0;
            printf("No such method\n");
            break;
        }
    }
    if(sig == 1){
        toBeReturn.methodName = tmpPtr->methodName;
        toBeReturn.ParamsList = tmpPtr->ParamsList[TmpCount];
        toBeReturn.methodModifierTypesList = tmpPtr->methodModifierTypesList[TmpCount];
        toBeReturn.returnTypeList = (tmpPtr->returnTypeList)[TmpCount];
    }

    return NULL;
}

VarNode *SymbolTable::SearchVar(const string& VarName) {
    VarNode *tmpPtr;
    
    tmpPtr = varTableHead[HashVar(VarName)]->nextVar;
    while( tmpPtr->varName != VarName ) {
        tmpPtr = tmpPtr->nextVar;
        if(tmpPtr == NULL) {
            printf("No such variable\n");
            return NULL;
        }
    }
    return tmpPtr;
}