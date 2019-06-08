#ifndef JASMIN_H
#define JASMIN_H

#include <string>
#include <vector>
using namespace std;

class JasminHeader{
    private:
        // optional
        string bytecodeVersion;
        // optinal 
        string sourceFile;
        string classSpec;
        string superSpec;
        string implements;
        // optinal 
        string signature;
        //optional
        string enclosing;
        // todo:innner class or interface
    public:
        JasminHeader();
        ~JasminHeader();
};

class JField{
    
};


class JMethod{

};

class JClassSpec{
    private:
        string accessSpec;
        string className;
    public:
        JClassSpec();
        ~JClassSpec();
};

class JasminFile{
    private:
        JasminHeader *jasminHeader;
        // optional 
        vector<JField> *JFields;
        vector<JMethod> *JMethods;
    
    public:
        JasminFile();
        ~JasminFile();
};

#endif