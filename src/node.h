#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

#include "MetaType.h"
using namespace std;
class Node
{
public:
    virtual void Visit() = 0;
};

class PackageNode;
class ImportNode;
class TypeDeclNode;
class FileNode : public Node
{
public:
    PackageNode *packageNode;
    vector<ImportNode*> *importNodes;
    vector<TypeDeclNode*>  *typeDeclNodes;
    FileNode();
    ~FileNode();
    void Visit();
};

class QualifiedNameNode;
class PackageNode: public Node
{
public:
    QualifiedNameNode *qNode;
    PackageNode(QualifiedNameNode *node);
    ~PackageNode();
    void Visit();
};


class ImportNode: public Node
{
public:
    void Visit();
    ImportNode();
    ~ImportNode();
};

class ClassDeclNode;
class TypeDeclNode : public Node
{
public:
    ClassOrInterface type;
    ClassDeclNode *classDecl;
public:
    void Visit();
    TypeDeclNode(ClassOrInterface t, ClassDeclNode *node);
    ~TypeDeclNode();
};

class IdentifierNode;
class QualifiedNameNode : public Node{
    public:
        vector<IdentifierNode*> *identifiers;
    public:
        void Visit();
        QualifiedNameNode();
        ~QualifiedNameNode();
};

class IdentifierNode: public Node
{
public:
    string name;
public:
    void Visit();
    IdentifierNode(const string& name);
    ~IdentifierNode();
};

class ClassBodyDeclNode;
class ClassDeclNode: public Node
{
public:
    IdentifierNode *className;
    vector<ClassBodyDeclNode*> *classBodyDecls;
public:
    void Visit();
    ClassDeclNode(const string& className, vector<ClassBodyDeclNode*> *decls);
    ~ClassDeclNode();
};

class ClassBodyDeclNode
{
    
public:
    void Visit();
    ClassBodyDeclNode();
    ~ClassBodyDeclNode();
};



#endif