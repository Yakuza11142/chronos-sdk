#ifndef CHRONOS_LEXER_H
#define CHRONOS_LEXER_H

#include "token.h"

// Initializes the scanner with raw source code memory
void init_lexer(const char* source);

// Scans and returns the next Token directly from source memory
Token scan_token();

#endif // CHRONOS_LEXER_H
