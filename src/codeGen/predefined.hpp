#ifndef PREDEFINED_H
#define PREDEFINED_H

#include <map>

using namespace std;

const map<string, string> predefStatic = {
    {"System.out", "java.io.PrintStream"}
};

const map<string, vector<string>> predefSymbolTable = {
    {"java/io/PrintStream/println", {
            // TODO: add more types
            "(Ljava/lang/String;)V",
            "(I;)V"
        }
    }
};

const map<string, string> predefinedType = {
    {"String", "Ljava/lang/String;"},
};
#endif