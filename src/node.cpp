#include "node.h"
#include <iostream>
using namespace std;
FileNode::FileNode(){

}

FileNode::~FileNode(){

}

void FileNode::Visit(){
    this->packageNode->Visit();
    for (auto node: *this->importNodes){
        node->Visit();
    }
    for (auto node: *this->typeDeclNodes){
        node->Visit();
    }
}

PackageNode::PackageNode(QualifiedNameNode *node){
    this->qNode = node;
}

void PackageNode::Visit(){
    this->qNode->Visit();
}

ImportNode::ImportNode(){

}

void ImportNode::Visit(){

}

IdentifierNode::IdentifierNode(const string& name){
    this->name = name;
}

void IdentifierNode::Visit(){
    cout << this->name << endl;
}

TypeDeclNode::TypeDeclNode(ClassOrInterface t, ClassDeclNode *node){
    this->type = t;
    this->classDecl = node;
}

void TypeDeclNode::Visit(){
    if (this->type == Class){
        cout << "class" << endl;
    }else{
        cout << "interface" << endl;
    }

    this->classDecl->Visit();
}

ClassDeclNode::ClassDeclNode(const string& name, vector<ClassBodyDeclNode*> *decls){
    this->classBodyDecls = decls;
    this->className = new IdentifierNode(name);
}

void ClassDeclNode::Visit(){
    this->className->Visit();

    for (auto node : *this->classBodyDecls){
        node->Visit();
    }
}

ClassBodyDeclNode::ClassBodyDeclNode(){

}

void ClassBodyDeclNode::Visit(){

}

QualifiedNameNode::QualifiedNameNode(){
    this->identifiers = new vector<IdentifierNode*>;
}

void QualifiedNameNode::Visit(){
    for (auto node : *this->identifiers){
        node->Visit();
    }
}