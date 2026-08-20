#include <stdio.h>
#include "vm.h"

// Opcode constants (matches compiler opcodes)
#define OP_ADD_IMM  0x00
#define OP_SUB_IMM  0x01
#define OP_XOR_IMM  0x02
#define OP_SWAP_REG 0x03
#define OP_HALT     0xFF

void init_vm(VMState* vm) {
    vm->pc = 0;
    for (int i = 0; i < NUM_REGISTERS; i++) {
        vm->registers[i] = 0;
    }
}

void execute_instruction(VMState* vm, uint8_t opcode, uint8_t reg_a, uint8_t reg_b, int32_t imm, ExecutionDirection dir) {
    switch (opcode) {
        case OP_ADD_IMM:
            // Reversible Addition: Forward = ADD, Backward = SUB
            if (dir == EXEC_FORWARD) {
                vm->registers[reg_a] += imm;
            } else {
                vm->registers[reg_a] -= imm;
            }
            break;

        case OP_SUB_IMM:
            // Reversible Subtraction: Forward = SUB, Backward = ADD
            if (dir == EXEC_FORWARD) {
                vm->registers[reg_a] -= imm;
            } else {
                vm->registers[reg_a] += imm;
            }
            break;

        case OP_XOR_IMM:
            // Bitwise XOR is its own inverse (Bijective)
            vm->registers[reg_a] ^= imm;
            break;

        case OP_SWAP_REG:
            // Zero-memory register swap is fully reversible
            {
                int32_t temp = vm->registers[reg_a];
                vm->registers[reg_a] = vm->registers[reg_b];
                vm->registers[reg_b] = temp;
            }
            break;

        default:
            break;
    }
}

void print_vm_state(const VMState* vm) {
    printf("[PC: %04d] ", vm->pc);
    for (int i = 0; i < 4; i++) {
        printf("R%d: %d | ", i, vm->registers[i]);
    }
    printf("\n");
}
