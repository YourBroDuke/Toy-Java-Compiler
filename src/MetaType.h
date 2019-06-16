#ifndef METATYPE_H
#define METATYPE_H

#include <map>
using namespace std;

enum ClassOrInterface {
    CLASS_TYPE,
    INTERFACE_TYPE
};

enum ModifierType {
    PUBLIC_TYPE,
	PROTECTED_TYPE,
	PRIVATE_TYPE,
	ABSTRACT_TYPE,
	DEFAULT_TYPE,
	STATIC_TYPE,
	STRICTFP_TYPE,
    FINAL_TYPE
};

enum MemberDeclType {
    METHOD_DECL_TYPE,
    FIELD_DECL_TYPE,
    CONSTRUCTOR_DECL_TYPE,
    INTERFACE_DECL_TYPE
};

const map<ModifierType, string> ModifierMap = {
    {PUBLIC_TYPE, "public"},
    {PROTECTED_TYPE, "protect"},
    {PRIVATE_TYPE, "private"},
    {ABSTRACT_TYPE, "abstract"},
    {DEFAULT_TYPE, "default"},
    {STATIC_TYPE, "static"},
    {STRICTFP_TYPE, "strictfp"},
    {FINAL_TYPE, "final"}
};

enum PrimitiveTypeOrNot {
    BOOLEAN_PTYPE,
    CHAR_PTYPE,
    BYTE_PTYPE,
    SHORT_PTYPE,
    INT_PTYPE,
    LONG_PTYPE,
    FLOAT_PTYPE,
    DOUBLE_PTYPE,
    VOID_PTYPE,
    NONPR_TYPE
};

enum LiteralType {
    INTEGER_LIT,
    FLOAT_LIT,
    CHAR_LIT,
    STRING_LIT,
    BOOL_LIT,
    NULL_LIT
};

const map<LiteralType, PrimitiveTypeOrNot> LtoP_map = {
    {INTEGER_LIT, LONG_PTYPE},
    {FLOAT_LIT, DOUBLE_PTYPE},
    {CHAR_LIT, LONG_PTYPE},
    {STRING_LIT, NONPR_TYPE},
    {BOOL_LIT, BOOLEAN_PTYPE},
    {NULL_LIT, NONPR_TYPE}
}

const map<PrimitiveTypeOrNot, string> PrimitiveTypeOrNotMap = {
    {BOOLEAN_PTYPE, "Z"},
    {CHAR_PTYPE, "C"},
    {BYTE_PTYPE, "B"},
    {SHORT_PTYPE, "S"},
    {INT_PTYPE, "I"},
    {LONG_PTYPE, "J"},
    {FLOAT_PTYPE, "F"},
    {DOUBLE_PTYPE, "D"},
    {VOID_PTYPE, "V"}
};

enum StatementType {
    BLOCK_TYPE,
    IF_ELSE_TYPE,
    IF_STAT_TYPE,
    FOR_STAT_TYPE,
    WHILE_STAT_TYPE,
    DO_WHILE_STAT_TYPE,
    RETURN_TYPE,
    RETURN_NONE_TYPE,
    EXPR_TYPE,
    NOTHING_TYPE
};

const map<StatementType, string> StatementTypeMap_forVisit = {
    {BLOCK_TYPE, "BLOCK"},
    {IF_ELSE_TYPE, "IF_ELSE"},
    {IF_STAT_TYPE, "ONLY_IF"},
    {FOR_STAT_TYPE, "FOR_STAT"},
    {WHILE_STAT_TYPE, "WHILE_STAT"},
    {DO_WHILE_STAT_TYPE, "DO_WHILE_STAT"},
    {RETURN_TYPE, "RETURN_TYPE"},
    {RETURN_NONE_TYPE, "RETURN_NONE"},
    {EXPR_TYPE, "EXPR_TYPE"},
    {NOTHING_TYPE, "NOTHING_TYPE"}
};

enum ExprStatType {
    PRIMARY_TYPE,
    IDEN_DOT,
    IDEN_METHOD,
    IDEN_DOT_METHOD,
    IDEN_ARRAY,
    IDEN_DOT_ARRAY,
    PRE_INCRE,
    POST_INCRE,
    PRE_DECRE,
    POST_DECRE,
    TILDE_EXPR,
    BANG_EXPR,
    POS_EXPR,
    NEG_EXPR,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_ADD,
    OP_SUB,
    OP_LSHIFT,
    OP_RSHIFT,
    OP_URSHIFT,
    OP_LT,
    OP_GT,
    OP_LTOE,
    OP_GTOE,
    OP_EQ,
    OP_NEQ,
    OP_BAND,
    OP_CARET,
    OP_BOR,
    OP_AND,
    OP_OR,
    OP_ASN,
    OP_ADD_ASN,
    OP_SUB_ASN,
    OP_MUL_ASN,
    OP_DIV_ASN,
    OP_MOD_ASN,
    OP_AND_ASN,
    OP_OR_ASN,
    OP_XOR_ASN,
    OP_LSHIFT_ASN,
    OP_RSHIFT_ASN,
    OP_URSHIFT_ASN
};

enum PrimaryNodeType {
    PRIMARY_EXPR,
    PRIMARY_THIS,
    PRIMARY_SUPER,
    PRIMARY_LITERAL,
    PRIMARY_IDEN
};

enum LocalVarType {
    FINAL_TYPE_L,
    NOT_FINAL_TYPE
};

enum InitializerType {
    EXPR_INIT,
    ARRAY_INIT
};

enum ExprValType{
    INT_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    LONG_TYPE,
    STRING_TYPE,
    REFERENCE_TYPE
};
#endif