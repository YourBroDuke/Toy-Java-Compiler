#include <iostream>
#include "SymbolTable.h"
#include <string>

#define MaxSize 1000

using namespace std;

int Hash(string name);

class VaribleNode{
    public:
        string name;
        int type;
        int Type;
        //VaribleNode* NextNode;
        VaribleNode(string InName, int InType){
            name = InName;
            type = InType;
        }
};

VaribleNode* VaribleTable[MaxSize];

int Hash(string name){

}

void insert(VaribleNode* N){
    int tmp = Hash(N->name);
    if ( VaribleTable[tmp]!=NULL ) {
        
    }
}

void lookup(string LookUpName){
    int key = Hash(LookUpName);

}