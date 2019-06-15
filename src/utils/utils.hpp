#ifndef UTILS_H
#define UTILS_H

#include "../codeGen/Jasmin.hpp"
JInstructionStmt* NewSimpleBinInstruction(string opcode, string arg);
JInstructionStmt* NewSimpleNoParamsInstruction(string opcode);
#endif