#include "utils.hpp"
#include "../codeGen/Jasmin.hpp"

JInstructionStmt* NewSimpleBinInstruction(string opcode, string arg){
    JInstructionStmt *s = new JInstructionStmt;
    s->opcode = new string(opcode);
    s->args->push_back(arg);
    return s;
}

JInstructionStmt* NewSimpleNoParamsInstruction(string opcode){
    JInstructionStmt *s = new JInstructionStmt;
    s->opcode = new string(opcode);
    return s;
}
