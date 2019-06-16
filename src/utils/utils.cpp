#include "utils.hpp"
#include "../codeGen/Jasmin.hpp"
#include "../codeGen/predefined.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

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

void split(const std::string& s,
    std::vector<std::string>& sv,
                   const char delim) {
    sv.clear();
    std::istringstream iss(s);
    std::string temp;

    while (std::getline(iss, temp, delim)) {
        sv.emplace_back(std::move(temp));
    }

    return;
}

vector<JInstructionStmt*>* CheckAndReplacePredefined(JContext* context, ExprNode *node){
    string id = "";
    for (auto s: *node->ids){
        id += s->name+".";
    }
    for (auto it: predefStatic){
        if (id.rfind(it.first, 0) == 0){
            vector<string> tokens;
            vector<string> tmp;
            split(it.second, tokens, '.');
            split(it.first, tmp, '.');
            vector<IdentifierNode*> *ids = new vector<IdentifierNode*>;
            for (auto token: tokens){
                ids->push_back(new IdentifierNode(token));
            }
            node->ids->erase(node->ids->begin(), node->ids->begin()+tmp.size());
            node->ids->insert(node->ids->begin(), ids->begin(), ids->end());
            JInstructionStmt *s = new JInstructionStmt;
            s->opcode = new string("getstatic");
            string key = it.first;
            string value = it.second;
            replace(key.begin(), key.end(), '.', '/');
            replace(value.begin(), value.end(), '.', '/');
            s->args->push_back("java/lang/" + key);
            s->args->push_back("L" + value + ";");
            context->currentFrame.top()->frameNode->method->stackLimit++;
            return new vector<JInstructionStmt*>{s};
        }
    }
    return nullptr;
}

string IDVecToString(vector<IdentifierNode*> *vec, const char ch){
    string ret;
    for (auto &s: *vec){
        ret += s->name + ch;
    }
    return ret.substr(0, ret.size()-1);
}

string IDVecToStringDot(vector<IdentifierNode*> *vec){
    return IDVecToString(vec, '.');
}

string IDVecToStringSlash(vector<IdentifierNode*> *vec){
    return IDVecToString(vec, '/');
}

string MakeDescriptor(vector<TypeTypeNode*> *params, TypeTypeNode* ret){
    string desc = "(";
    for (auto p : *params){
        p->codeGen(nullptr);
        desc += p->typeStr;
    }
    desc += ")";
    ret->codeGen(nullptr);
    desc += ret->typeStr;
    return desc;
}

string IfOpcodeByExprType(ExprNode* node){
    switch (node->type)
    {
    case OP_LT:
        return "ifgt";
        break;
    case OP_GT:
        return "iflt";
    case OP_LTOE:
        return "ifge";
    case OP_GTOE:
        return "ifle";
    case OP_EQ:
        return "ifeq";
    case OP_NEQ:
        return "ifneq";
    default:
        return "ifeq";
    }
}

string GenLabel(JContext *context){
    string Label = "L";
    Label += to_string(context->currentFrame.top()->labelCounter++);
    return Label;
}