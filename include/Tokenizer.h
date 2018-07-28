/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

// guard
#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

// include libraries
#include <assert.h>
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
 * object struct
 **********************************************************/

typedef struct TokenClass{
    char** list;
    unsigned int length;
    // private variables
    void* _private_;
}Token;

/**********************************************************
 * other function definition
 **********************************************************/

#define split new_Token

/**********************************************************
 * token function
 **********************************************************/

// constructor
Token* new_Token(char* stringToBeSplit, const char* delimiter);
// functions returns a non dyanmic string,
// the returned string will be freed when token_free is invoked
// so you must copy the string when you want to edit using string tag
// example: String variable = $(tokenGetTokenAt(object, 2));
char* token_getTokenAt(Token* this, int position);
char* token_combine(Token* token, unsigned int tokenStart, int unsigned tokenEnd);
// function to search the index or total same value
int token_search(Token* token, const char* stringToBeSearched, bool trueIfIndexSearch_falseIfCounting);
// free function
void token_free(void* tokenObjectToBeFreed);

#endif