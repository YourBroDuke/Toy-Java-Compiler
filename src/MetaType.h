#ifndef METATYPE_H
#define METATYPE_H

#include <unordered_map>
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

const unordered_map<ModifierType, string> ModifierMap = {
    {PUBLIC_TYPE, "public"},
    {PROTECTED_TYPE, "protect"},
    {PRIVATE_TYPE, "private"},
    {ABSTRACT_TYPE, "abstract"},
    {DEFAULT_TYPE, "default"},
    {STATIC_TYPE, "static"},
    {STRICTFP_TYPE, "strictfp"},
    {FINAL_TYPE, "final"},
};

enum PrimitiveTypeOrNot {
    BOOLEAN_TYPE,
    CHAR_TYPE,
    BYTE_TYPE,
    SHORT_TYPE,
    INT_TYPE,
    LONG_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    VOID_TYPE,
    NONPR_TYPE
};

enum StatementType {
    BLOCK_TYPE,
    IF_ELSE_TYPE,
    IF_STAT_TYPE,
    FOR_STAT_TYPE,
    RETURN_TYPE,
    RETURN_NONE_TYPE,
    EXPR_TYPE
};

enum ExprType {
    PRIMARY_TYPE,
    IDEN_DOT,
    IDEN_METHOD,
    IDEN_DOT_METHOD,
    ID_ARRAY,
    ID_DOT_ARRAY,
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

enum LiteralType {
    INTEGER_LIT,
    FLOAT_LIT,
    CHAR_LIT,
    STRING_LIT,
    BOOL_LIT,
    NULL_LIT
};
#endif