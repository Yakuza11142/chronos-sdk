#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"

static Token current_token;

static void advance_token() {
    current_token = scan_token();
}

ASTNode* create_node(ASTNodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->literal_val = 0;
    node->next = NULL;
    memset(node->target, 0, 64);
    memset(node->operand, 0, 64);
    return node;
}

ASTNode* parse_program() {
    advance_token();
    ASTNode* head = NULL;
    ASTNode* current = NULL;

    while (current_token.type != TOKEN_EOF) {
        ASTNode* new_node = NULL;

        if (current_token.type == TOKEN_REVERSIBLE) {
            advance_token(); // consume 'reversible'
            if (current_token.type == TOKEN_LEFT_BRACE) advance_token();
        }

        if (current_token.type == TOKEN_IDENTIFIER) {
            char target_var[64];
            strncpy(target_var, current_token.start, current_token.length);
            target_var[current_token.length] = '\0';
            advance_token();

            if (current_token.type == TOKEN_ADD_ASSIGN) {
                new_node = create_node(NODE_ASSIGN_ADD);
                strcpy(new_node->target, target_var);
                advance_token();
                if (current_token.type == TOKEN_NUMBER) {
                    new_node->literal_val = atoi(current_token.start);
                    advance_token();
                }
            } else if (current_token.type == TOKEN_SWAP) {
                new_node = create_node(NODE_SWAP_OP);
                strcpy(new_node->target, target_var);
                advance_token();
                if (current_token.type == TOKEN_IDENTIFIER) {
                    strncpy(new_node->operand, current_token.start, current_token.length);
                    new_node->operand[current_token.length] = '\0';
                    advance_token();
                }
            }
        }

        if (current_token.type == TOKEN_SEMICOLON || current_token.type == TOKEN_RIGHT_BRACE) {
            advance_token();
        }

        if (new_node != NULL) {
            if (head == NULL) {
                head = new_node;
                current = head;
            } else {
                current->next = new_node;
                current = current->next;
            }
        }
    }

    return head;
}
