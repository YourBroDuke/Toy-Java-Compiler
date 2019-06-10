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

string JDescriptor::toString(){
    string result = "(";

    for (auto& s : *this->params){
        result += s + ';';
    }

    return result + this->ret;
}