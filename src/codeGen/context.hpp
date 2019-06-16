#ifndef CONTEXT_H
#define CONTEXT_H

#include "../node.h"
#include <stack>
#include <map>
using namespace std;
class Node;
class MethodDeclNode;
class Frame;
class JContext{
    public:
        Node* root;
        JasminFile *classFile;
        stack<Node*> nodeStack;
        stack<Frame*> currentFrame;
        string className;
    public:
        JContext(Node* node);
        ~JContext();
};

struct varIndexInfo{
    int index;
    string typeName;
};

class Frame{
    public:
        Frame(MethodDeclNode* node);
        MethodDeclNode * frameNode;
        map<string, varIndexInfo> varIndex;
        bool hasReturn;
        int labelCounter;
};
#endif