/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

// guard
#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

// include libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <stdarg.h>

/**********************************************************
 * Object Struct
 **********************************************************/

typedef struct TokenClass{
    char** list;
    unsigned int length;
    // methods
    char* (*combine)(struct TokenClass*, unsigned int tokenStart, unsigned int tokenEnd);
    int (*search)(struct TokenClass*, const char* stringToBeSearched, bool trueIfIndexSearch_falseIfCounting);
    void (*destroy)(void* tokenObjectToBeFreed);
}Token;

/**********************************************************
 * Function Definition
 **********************************************************/

#define split new_Token

/**********************************************************
 * Token Function
 **********************************************************/

// constructor
Token* new_Token(char* stringToBeSplit, const char* delimiter);
// getter functions
char* token_combine(Token* token, unsigned int tokenStart, int unsigned tokenEnd);
int token_search(Token* token, const char* stringToBeSearched, bool trueIfIndexSearch_falseIfCounting);
// void functions
void token_free(void* tokenObjectToBeFreed);

#endif