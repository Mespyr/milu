#ifndef ILU_OPS_H
#define ILU_OPS_H

#include "token.h"

enum OpType 
{
    OP_PUSH,
    OP_POP,
    OP_PRINT,
    OP_DUP,
    OP_SWP,
    OP_FLP,

    OP_WHILE,
    OP_DO,
    OP_IF,
    OP_ELSE,
    OP_END,

    OP_PLUS, 
    OP_MINUS,
    OP_MUL,
    OP_DIV,

    OP_EQUAL,
    OP_GREATER,
    OP_LESS
};
    
class Op
{
public:
    Op(OpType type, Token token) :
        type(type), token(token) {}

    Op(OpType type, int push_val, Token token) :
        type(type), push_val(push_val), token(token) {}

    OpType type;
    Token token;
    int push_val;
    int reference_ip;
};

#endif
