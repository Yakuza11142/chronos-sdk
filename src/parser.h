#ifndef CHRONOS_PARSER_H
#define CHRONOS_PARSER_H

#include "token.h"

// Types of bijective AST statements
typedef enum {
    NODE_ASSIGN_ADD,   // x += y
    NODE_ASSIGN_SUB,   // x -= y
    NODE_ASSIGN_XOR,   // x ^= y
    NODE_SWAP_OP,      // x <=> y
    NODE_GATE_DECL     // gate H(q0)
} ASTNodeType;

// Abstract Syntax Tree Node struct
typedef struct ASTNode {
    ASTNodeType type;
    char target[64];
    char operand[64];
    int literal_val;
    struct ASTNode* next; // Next node in execution sequence
} ASTNode;

// Parser function prototypes
ASTNode* parse_program();

#endif // CHRONOS_PARSER_H
