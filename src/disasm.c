#include <stdio.h>
#include "disasm.h"

void disassemble_bytecode(const Instruction* code, int count) {
    printf("\n=== Chronos Bytecode Assembly ===\n");
    for (int i = 0; i < count; i++) {
        Instruction instr = code[i];
        printf("[%04d] ", i);
        switch (instr.opcode) {
            case OP_ADD_IMM:
                printf("OP_ADD_IMM   R%d, #%d\n", instr.reg_a, instr.immediate);
                break;
            case OP_SUB_IMM:
                printf("OP_SUB_IMM   R%d, #%d\n", instr.reg_a, instr.immediate);
                break;
            case OP_XOR_IMM:
                printf("OP_XOR_IMM   R%d, #%d\n", instr.reg_a, instr.immediate);
                break;
            case OP_SWAP_REG:
                printf("OP_SWAP_REG  R%d, R%d\n", instr.reg_a, instr.reg_b);
                break;
            case OP_HALT:
                printf("OP_HALT\n");
                break;
            default:
                printf("UNKNOWN_OPCODE\n");
                break;
        }
    }
}
