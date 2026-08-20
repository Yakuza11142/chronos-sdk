#ifndef CHRONOS_BYTECODE_H
#define CHRONOS_BYTECODE_H

#include <stdint.h>

typedef enum {
    OP_ADD_IMM,   // Add immediate value to register (reversible via SUB_IMM)
    OP_SUB_IMM,   // Subtract immediate value
    OP_XOR_IMM,   // XOR immediate bitwise flip
    OP_SWAP_REG,  // Zero-RAM swap between two registers
    OP_HALT       // End execution
} Opcode;

typedef struct {
    uint8_t opcode;
    uint8_t reg_a;
    uint8_t reg_b;
    int32_t immediate;
} Instruction;

#endif // CHRONOS_BYTECODE_H
