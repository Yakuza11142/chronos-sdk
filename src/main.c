#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "bytecode.h"

// Forward declarations
extern BytecodeChunk* compile_ast(ASTNode* ast_head);
extern void disassemble_bytecode(const Instruction* code, int count);
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

    printf("--- Compiling %s ---\n", argv[1]);

    // Step 1: Initialize Lexer
    init_lexer(buffer);

    // Step 2: Parse Tokens into AST
    ASTNode* ast_root = parse_program();

    // Step 3: Generate Bytecode from AST
    BytecodeChunk* chunk = compile_ast(ast_root);

    // Step 4: Display Output Assembly Instructions
    disassemble_bytecode(chunk->code, chunk->count);

    // Cleanup Native Memory
    free_ast(ast_root);
    free(chunk->code);
    free(chunk);
    free(buffer);

    printf("\nCompilation completed successfully with zero dependencies.\n");
    return 0;
}
