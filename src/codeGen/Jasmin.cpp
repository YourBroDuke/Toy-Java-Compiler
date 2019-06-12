#include "Jasmin.hpp"

JasminFile::JasminFile(){
    this->jasminHeader = new JasminHeader();
    this->JFields = nullptr;
    this->JMethods = nullptr;
}

JasminFile::~JasminFile(){
    delete jasminHeader;
    if (this->JFields){
        delete this->JFields;
    }
    if (this->JMethods){
        delete this->JMethods;
    }
}

/*
 ---------------TEMPORARY--------------
 */

JasminHeader::JasminHeader() {
    bytecodeVersion = nullptr;
    sourceFile = nullptr;
    classSpec = nullptr;
    superSpec = nullptr;
    implements = nullptr;
    signature = nullptr;
    enclosing = nullptr;
}

JasminHeader::~JasminHeader() {
    // TODO:
}

JMethod::JMethod() {
    accessSpec = nullptr;
    methodName = nullptr;
    descriptor = nullptr;
    JStmts = nullptr;
}

JMethod::~JMethod() {

}
/*
 -----------------END-------------------
 */

string JDescriptor::toString(){
    string result = "(";

    for (auto& s : *this->params){
        result += s + ';';
    }

    return result + ')' + this->ret;
}

string JClassSpec::toString(){
    return ".class " + accessSpec + " " + className + "\n";
}

string JasminHeader::toString(){
    string ret;
    if (bytecodeVersion != nullptr){
        ret += ".bytecode " + *bytecodeVersion + "\n";
    }
    if (sourceFile != nullptr){
        ret += ".source " + *sourceFile + "\n";
    }
    ret += classSpec->toString();
    // TODO: super specification
    ret += ".super java/lang/Object\n";
    if (implements != nullptr){
        ret += *implements;
    }
    if (signature != nullptr){
        ret += ".signature " + *signature + "\n";
    }
    if (enclosing != nullptr){
        ret += ".enclosing " + *enclosing + "\n";
    }
    return ret;
}

string JMethod::toString(){
    string ret = ".method ";
    ret += *accessSpec + " ";
    ret += *methodName;
    ret += descriptor->toString() + "\n";
    for (auto stmt : *JStmts){
        ret += stmt->toString();
    }
    return ret + "return\n" + ".end method\n";
}

JInstructionStmt::JInstructionStmt(){
    this->args = new vector<string>;
}

string JInstructionStmt::toString(){
    string ret = "";
    // TODO: PC support
    ret += *opcode;
    for (auto arg : *args){
        ret += " " + arg;
    }
    return ret + "\n";
}

string JasminFile::toString(){
    string ret = "";
    ret += jasminHeader->toString();
    if (JFields != nullptr){
        // TODO:
    }
    if (JMethods != nullptr){
        for (auto method : *JMethods){
            ret += method->toString();
        }
    }
    return ret;
}