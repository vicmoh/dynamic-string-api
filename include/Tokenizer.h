/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

//guard
#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

//include libraries
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
 * struct
 **********************************************************/

typedef struct TokenClass{
    char** list;
    unsigned int length;
}Token;

/**********************************************************
 * functions definition
 **********************************************************/

#define split Token_split

/**********************************************************
 * string api functions
 **********************************************************/

Token* Token_newToken();
Token* Token_split(char* stringToBeSplit, const char* delimiter);
char* Token_combinedToken(Token* token, unsigned int tokenStart, int unsigned tokenEnd);
int Token_searchToken(Token* token, const char* stringToBeSearched, char* getIndexOrCount);
void Token_freeToken(Token* toBeFreed);

#endif