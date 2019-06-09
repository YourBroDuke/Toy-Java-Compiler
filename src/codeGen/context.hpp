#ifndef CONTEXT_H
#define CONTEXT_H

#include "../node.h"
class JContext{
    private:
        Node* root;
    public:
        JContext(Node* node);
        ~JContext();
};
#endif