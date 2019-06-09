#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <vector>
#include "Jasmin.hpp"
#include "context.hpp"
#include "../node.h"
using namespace std;

class JasminFileGenerator
{
private:
    JContext *context;
public:
    void WriteTo(ostream& out);
    bool Generate();
    JasminFileGenerator(JContext *context);
    ~JasminFileGenerator();
};
#endif