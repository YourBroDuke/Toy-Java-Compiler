#include "context.hpp"

JContext::JContext(Node* root){
    this->root = root;
    this->classFile = new JasminFile();
}

JContext::~JContext(){
    
}

Frame::Frame(MethodDeclNode* node){
    this->frameNode = node;
}