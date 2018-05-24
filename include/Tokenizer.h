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
#include <math.h>
#include <stdarg.h>

/**********************************************************
 * Struct Object
 **********************************************************/

typedef struct TokenClass{
    char** list;
    unsigned int length;
    struct TokenClass* (*splitter)(char* string, const char* delim);
    struct TokenClass* (*combine)(struct TokenClass token, char* string, const char* delim);
}Token;

/**********************************************************
 * Function Definition
 **********************************************************/

#define split Token_split

/**********************************************************
 * Token Function
 **********************************************************/

// constructor
Token* Token_newToken();
Token* Token_split(char* stringToBeSplit, const char* delimiter);
// getter functions
char* Token_combinedToken(Token* token, unsigned int tokenStart, int unsigned tokenEnd);
int Token_searchToken(Token* token, const char* stringToBeSearched, bool trueIfIndex_falseIfCount);
// void functions
void Token_freeToken(Token* toBeFreed);

#endif