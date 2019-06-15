#include <iostream>
#include "SymbolTable.h"
#include <string>
#include <stdlib.h>
#include "../MetaType.h"

using namespace std;

SymbolTable::SymbolTable() {
    int initCount;
    CurrentScope = 0;
    for(initCount = 0; initCount < MaxSize;initCount++ ){    
        varTableHead[initCount] = new VarNode();
        methodTableHead[initCount] = new MethodNode();
    }
    vector<ModifierType> *testModi =  new vector<ModifierType>;
    TypeTypeNode *testTTN;
    AddVarNode(testModi, "i", testTTN);
}

int SymbolTable::HashVar(const string& nameOfVar) {
    int count, returnNum;
    for(count = 0; count < nameOfVar.length();count++ )
        returnNum += nameOfVar[count];
    return returnNum = (returnNum * returnNum * returnNum / 2)%MaxSize;
}

int SymbolTable::HashMethod(const string& nameOfMethod) {
    int count, returnMeth;
    for(count = 0; count < nameOfMethod.length();count++)
        returnMeth += nameOfMethod[count];
    return returnMeth = (returnMeth * returnMeth * returnMeth / 2)%MaxSize;
}

void SymbolTable::PushScope() {
    CurrentScope++;
}

void SymbolTable::PopScope() {
    int goThroughCount;
    VarNode *tmpDelet;
    for( goThroughCount = 0;goThroughCount < MaxSize;goThroughCount++) {
        while(varTableHead[goThroughCount]->nextVar) {
            if(varTableHead[goThroughCount]->nextVar->scopeLv == CurrentScope){
                tmpDelet = varTableHead[goThroughCount]->nextVar;
                varTableHead[goThroughCount]->nextVar = varTableHead[goThroughCount]->nextVar->nextVar;
                delete tmpDelet;
            }
        }
    }
    CurrentScope--;
}

int SymbolTable::AddVarNode(vector<ModifierType> *varModifierType, const string& Name, TypeTypeNode* varType){
    VarNode *newVar = new VarNode(varModifierType, Name, varType, CurrentScope);

    newVar->nextVar = varTableHead[HashVar(newVar->varName)]->nextVar;
    varTableHead[HashVar(newVar->varName)]->nextVar = newVar;

    return 1;
}

int SymbolTable::AddMethodNode(vector<ModifierType> *methodModifiers, const string& Name, vector<FormalParamNode*> *Params, TypeTypeNode* returnType){
    MethodNode *newMethod = new MethodNode(methodModifiers, Name, Params, returnType);

    newMethod->nextMethod = methodTableHead[HashMethod(newMethod->methodName)]->nextMethod;
    methodTableHead[HashMethod(newMethod->methodName)]->nextMethod = newMethod; 

    return 1;
}

ReturnMethodNode *SymbolTable::SearchMethod(const string& MethodName, vector<TypeTypeNode*> *paramTypes){
    MethodNode *tmpPtr;
    int TmpCount, sig;
    ReturnMethodNode *toBeReturn;
    tmpPtr = methodTableHead[HashMethod(MethodName)]->nextMethod;
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
        toBeReturn = new ReturnMethodNode(MethodName, paramTypes, (tmpPtr->returnTypeList)[TmpCount], tmpPtr->methodModifierTypesList[TmpCount]);
    }
    return toBeReturn;
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