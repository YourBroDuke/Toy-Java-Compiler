#include "Generator.hpp"

JasminFileGenerator::JasminFileGenerator(JContext *context)
{
    this->context = context;
}

JasminFileGenerator::~JasminFileGenerator()
{
}


bool JasminFileGenerator::Generate(){
    this->context->root->codeGen(this->context);
}

void JasminFileGenerator::WriteTo(ostream& out){
    out << this->context->classFile->toString() << endl;
}