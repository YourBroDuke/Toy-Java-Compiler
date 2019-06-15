#ifndef UTILS_H
#define UTILS_H

#include "../codeGen/Jasmin.hpp"
#include "../node.h"
#include <vector>
using namespace std;
JInstructionStmt* NewSimpleBinInstruction(string opcode, string arg);
JInstructionStmt* NewSimpleNoParamsInstruction(string opcode);
vector<JInstructionStmt*>* CheckAndReplacePredefined(ExprNode *node);
void split(const std::string& s,std::vector<std::string>& sv,const char delim = ' ');
string IDVecToStringDot(vector<IdentifierNode*> *vec);
string IDVecToStringSlash(vector<IdentifierNode*> *vec);
#endif