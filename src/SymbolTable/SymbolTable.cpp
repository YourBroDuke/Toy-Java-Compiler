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
    TypeTypeNode *testTTN = new TypeTypeNode(INT_PTYPE);
    FormalParamNode *fpn = new FormalParamNode(new TypeTypeNode(NONPR_TYPE, "String"), new VariableDeclaratorIdNode(0, "s"));
    FormalParamNode *fpn1 = new FormalParamNode(new TypeTypeNode(INT_PTYPE), new VariableDeclaratorIdNode(0, "s"));
    vector<FormalParamNode*> *can1 = new vector<FormalParamNode*>;
    vector<FormalParamNode*> *can2 = new vector<FormalParamNode*>;
    can1->push_back(fpn);
    // AddVarNode(testModi, "i", testTTN);
    AddMethodNode(testModi, "System.out.println", can1, testTTN);
    can2->push_back(fpn1);
    AddMethodNode(testModi, "System.out.println", can2, testTTN);
    // cout << SearchMethod("j", new vector<TypeTypeNode*>)->methodName << endl;
}


int SymbolTable::HashVar(const string& nameOfVar) {
    int count, returnNum = 0;
    for(count = 0; count < nameOfVar.length();count++ )
        returnNum += nameOfVar[count];
    return returnNum = (returnNum * returnNum * returnNum / 2)%MaxSize;
}

int SymbolTable::HashMethod(const string& nameOfMethod) {
    int count, returnMeth = 0;
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
            } else {
                break;
            }
        }
    }
    CurrentScope--;
}

int SymbolTable::AddVarNode(vector<ModifierType> *varModifierType, const string& Name, TypeTypeNode* varType){
    VarNode *newVar = new VarNode(varModifierType, Name, varType, CurrentScope);
    if (Name == "b") cout << "hehe" << endl << endl;
    newVar->nextVar = varTableHead[HashVar(newVar->varName)]->nextVar;
    varTableHead[HashVar(newVar->varName)]->nextVar = newVar;

    return 1;
}

int SymbolTable::AddMethodNode(vector<ModifierType> *methodModifiers, const string& Name, vector<FormalParamNode*> *Params, TypeTypeNode* returnType){
    MethodNode *tmpPtr = methodTableHead[HashMethod(Name)]->nextMethod;
    while (tmpPtr) {
        if (tmpPtr->methodName == Name)
            break;
        tmpPtr = tmpPtr->nextMethod;
    }

    if (tmpPtr == NULL) {
        MethodNode *newMethod = new MethodNode(methodModifiers, Name, Params, returnType);

        newMethod->nextMethod = methodTableHead[HashMethod(newMethod->methodName)]->nextMethod;
        methodTableHead[HashMethod(newMethod->methodName)]->nextMethod = newMethod; 
    } else {
        tmpPtr->methodModifierTypesList.push_back(methodModifiers);
        vector<TypeTypeNode*> *crt = new vector<TypeTypeNode*>;
        for (auto node : *Params) {
            crt->push_back(node->paramType);
        }
        tmpPtr->ParamsList.push_back(crt);
        tmpPtr->returnTypeList.push_back(returnType);
    }
    
    return 1;
}

ReturnMethodNode *SymbolTable::SearchMethod(const string& MethodName, vector<TypeTypeNode*> *paramTypes) {
    MethodNode *tmpPtr;
    int TmpCount, sig;
    ReturnMethodNode *toBeReturn;
    tmpPtr = methodTableHead[HashMethod(MethodName)]->nextMethod;
    TmpCount = 0;

    while (tmpPtr) {
        if (tmpPtr->methodName == MethodName)
            break;
        tmpPtr = tmpPtr->nextMethod;
    }
    if (tmpPtr == NULL) return NULL;

    cout << "finding" << endl;

    for (int i = 0; i < tmpPtr->ParamsList.size(); i++) {
        int match = 1;
        if (tmpPtr->ParamsList[i]->size() != paramTypes->size()) match = 0;
        else {
            for (int j = 0; j < tmpPtr->ParamsList[i]->size(); j++) {
                TypeTypeNode *t1 = (*tmpPtr->ParamsList[i])[j], *t2 = (*paramTypes)[j];

                if (t1->type != t2->type || t1->arrayDim != t2->arrayDim) match = 0;
                else {
                    if (t1->type == NONPR_TYPE) {
                        if (t1->typeInfo->size() != t2->typeInfo->size()) match = 0;
                        else {
                            for (int k = 0; k < t1->typeInfo->size(); k++) {
                                if ( (*t1->typeInfo)[k]->name != (*t1->typeInfo)[k]->name )
                                    match = 0;
                            }
                        }
                    }
                }
            }
        }
        if (match == 1) return new ReturnMethodNode(MethodName, tmpPtr->ParamsList[i], tmpPtr->returnTypeList[i], tmpPtr->methodModifierTypesList[i]);
    }

    return NULL;
}

ReturnMethodNode *SymbolTable::SearchMethod(const string& MethodName, vector<FormalParamNode*> *Params) {
    vector<TypeTypeNode*> paramTypes;
    for (auto node : *Params) {
        paramTypes.push_back(node->paramType);
    }
    return SearchMethod(MethodName, &paramTypes);
}

ReturnMethodNode *SymbolTable::SearchMethod(const string& MethodName, vector<ExprNode*> *exprs) {
    vector<TypeTypeNode*> paramTypes;
    for (auto node : *exprs) {
        paramTypes.push_back(node->valType);
    }
    return SearchMethod(MethodName, &paramTypes);
}

VarNode *SymbolTable::SearchVar(const string& VarName) {
    cout << HashVar(VarName) << endl;
    VarNode *tmpPtr = varTableHead[HashVar(VarName)]->nextVar;

    while (tmpPtr != NULL) {
        if (tmpPtr->varName == VarName)
            return tmpPtr;
        tmpPtr = tmpPtr->nextVar;
    }
    return NULL;
}