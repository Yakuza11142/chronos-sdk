#ifndef CHRONOS_VM_H
#define CHRONOS_VM_H

#include <stdint.h>

#define NUM_REGISTERS 8

typedef enum {
    EXEC_FORWARD,
    EXEC_BACKWARD
} ExecutionDirection;

typedef struct {
    int32_t registers[NUM_REGISTERS];
    uint32_t pc; // Program Counter
} VMState;

// VM Interface
void init_vm(VMState* vm);
void execute_instruction(VMState* vm, uint8_t opcode, uint8_t reg_a, uint8_t reg_b, int32_t imm, ExecutionDirection dir);
void print_vm_state(const VMState* vm);

#endif // CHRONOS_VM_H
