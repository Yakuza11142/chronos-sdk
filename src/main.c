#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "bytecode.h"
#include "disasm.h"
#include "vm.h"

extern BytecodeChunk* compile_ast(ASTNode* ast_head);
extern void free_ast(ASTNode* head);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: chronos <file.chronos>\n");
        return 64;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        printf("Error: Could not open source file %s\n", argv[1]);
        return 66;
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize + 1);
    fread(buffer, sizeof(char), fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);

    printf("=== [1/3] Scanning & Parsing %s ===\n", argv[1]);
    init_lexer(buffer);
    ASTNode* ast_root = parse_program();

    printf("=== [2/3] Generating Bytecode ===\n");
    BytecodeChunk* chunk = compile_ast(ast_root);
    disassemble_bytecode(chunk->code, chunk->count);

    printf("\n=== [3/3] Executing in Chronos Reversible VM ===\n");
    VMState vm;
    init_vm(&vm);

    printf("\n--- FORWARD EXECUTION ---\n");
    for (int i = 0; i < chunk->count; i++) {
        Instruction instr = chunk->code[i];
        if (instr.opcode == OP_HALT) break;
        execute_instruction(&vm, instr.opcode, instr.reg_a, instr.reg_b, instr.immediate, EXEC_FORWARD);
        vm.pc++;
        print_vm_state(&vm);
    }

    printf("\n--- TIME REVERSAL (BACKWARD EXECUTION) ---\n");
    for (int i = chunk->count - 1; i >= 0; i--) {
        Instruction instr = chunk->code[i];
        if (instr.opcode == OP_HALT) continue;
        vm.pc--;
        execute_instruction(&vm, instr.opcode, instr.reg_a, instr.reg_b, instr.immediate, EXEC_BACKWARD);
        print_vm_state(&vm);
    }

    // Free memory
    free_ast(ast_root);
    free(chunk->code);
    free(chunk);
    free(buffer);

    printf("\nZero-Entropy Execution & State Recovery Complete.\n");
    return 0;
}
