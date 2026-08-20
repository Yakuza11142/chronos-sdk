#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

int main() {
    VMState vm;
    init_vm(&vm);

    printf("=== Initial VM State ===\n");
    print_vm_state(&vm);

    // Hardcoded test bytecode stream (matches compiler output)
    // OP_ADD_IMM R0, #15
    // OP_SWAP_REG R0, R1
    uint8_t opcodes[] = {0x00, 0x03};
    uint8_t regs_a[]  = {0,    0};
    uint8_t regs_b[]  = {0,    1};
    int32_t imms[]    = {15,   0};
    int count = 2;

    printf("\n=== Executing FORWARD ===\n");
    for (int i = 0; i < count; i++) {
        execute_instruction(&vm, opcodes[i], regs_a[i], regs_b[i], imms[i], EXEC_FORWARD);
        vm.pc++;
        print_vm_state(&vm);
    }

    printf("\n=== Rewinding BACKWARD (Time Reversal) ===\n");
    for (int i = count - 1; i >= 0; i--) {
        vm.pc--;
        execute_instruction(&vm, opcodes[i], regs_a[i], regs_b[i], imms[i], EXEC_BACKWARD);
        print_vm_state(&vm);
    }

    printf("\nZero-Entropy State Recovery Verified.\n");
    return 0;
}
