#ifndef CONTEXT_H
#define CONTEXT_H

#include "../node.h"
#include <stack>
using namespace std;
class Node;

class JContext{
    public:
        Node* root;
        JasminFile *classFile;
        stack<Node*> nodeStack;
    public:
        JContext(Node* node);
        ~JContext();
};
#endif