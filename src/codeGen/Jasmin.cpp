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
    localLimit = 0;
    stackLimit = 0;
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
        result += s;
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
    ret += "\t.limit stack " + to_string(this->stackLimit) + "\n";
    if (this->localLimit != 0)
        ret += "\t.limit locals " + to_string(this->localLimit) + "\n";
    for (auto stmt : *JStmts){
        ret += '\t' + stmt->toString();
    }
    return ret + ".end method\n";
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
        for (auto field : *JFields){
            ret += field->toString() + "\n";
        }
    }
    if (JMethods != nullptr){
        for (auto method : *JMethods){
            ret += method->toString();
        }
    }
    return ret;
}

JLabel::JLabel(string name){
    this->labelName = new string(name);
}

string JLabel::toString(){
    return *this->labelName + ":" + "\n";
}

string JField::toString(){
    return ".field " + *modifier + " " + *id + " " + *descriptor;
}