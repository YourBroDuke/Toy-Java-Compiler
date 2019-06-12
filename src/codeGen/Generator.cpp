#include "Generator.hpp"
#include <iostream>
using namespace std;

JasminFileGenerator::JasminFileGenerator(JContext *context)
{
    this->context = context;
}

JasminFileGenerator::~JasminFileGenerator()
{
}


bool JasminFileGenerator::Generate(){
    cout << this->context << endl;
    cout << this->context->root << endl;
    this->context->root->codeGen(this->context);
}

void JasminFileGenerator::WriteTo(ostream& out){
    out << this->context->classFile->toString() << endl;
}