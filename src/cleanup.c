#include <stdlib.h>
#include "parser.h"

void free_ast(ASTNode* head) {
    ASTNode* current = head;
    while (current != NULL) {
        ASTNode* next = current->next;
        free(current);
        current = next;
    }
}
