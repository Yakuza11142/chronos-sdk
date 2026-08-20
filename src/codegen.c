#include <stdio.h>
#include <stdlib.h>
#include "bytecode.h"
#include "parser.h"

typedef struct {
    Instruction* code;
    int count;
    int capacity;
} BytecodeChunk;

void init_chunk(BytecodeChunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 8;
    chunk->code = (Instruction*)malloc(sizeof(Instruction) * chunk->capacity);
}

void write_instruction(BytecodeChunk* chunk, Instruction instr) {
    if (chunk->capacity < chunk->count + 1) {
        chunk->capacity *= 2;
        chunk->code = (Instruction*)realloc(chunk->code, sizeof(Instruction) * chunk->capacity);
    }
    chunk->code[chunk->count++] = instr;
}

BytecodeChunk* compile_ast(ASTNode* ast_head) {
    BytecodeChunk* chunk = (BytecodeChunk*)malloc(sizeof(BytecodeChunk));
    init_chunk(chunk);

    ASTNode* current = ast_head;
    while (current != NULL) {
        Instruction instr;
        if (current->type == NODE_ASSIGN_ADD) {
            instr.opcode = OP_ADD_IMM;
            instr.reg_a = 0; // Target Register R0
            instr.immediate = current->literal_val;
            write_instruction(chunk, instr);
        } else if (current->type == NODE_SWAP_OP) {
            instr.opcode = OP_SWAP_REG;
            instr.reg_a = 0; // R0
            instr.reg_b = 1; // R1
            instr.immediate = 0;
            write_instruction(chunk, instr);
        }
        current = current->next;
    }

    Instruction halt = {OP_HALT, 0, 0, 0};
    write_instruction(chunk, halt);
    return chunk;
}
