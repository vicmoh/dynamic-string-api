/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

//guard
#ifndef _DYNAMICSTRING_H_
#define _DYNAMICSTRING_H_

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

//macros
#define GET_ARRAY_SIZE( array ) ( sizeof( array ) / sizeof( *array )) //or array[0] instead of *array
#define UPPERCASE_RANGE( var ) (var >= 65 && var <= 90) 
#define LOWERCASE_RANGE( var ) (var >= 97 && var <= 122)
#define ALPHABET_RANGE( var ) ( (var >= 97 && var <= 122) || (var >= 65 && var <= 90) )
#define NUMBER_RANGE( var ) (var >= 48 && var <= 57)
#define VISIBLE_RANGE( var ) (var >= 33 && var <= 126)

// debuger
#define DEBUG_SETTING true
#define debug if(DEBUG_SETTING)printf
#define CHECK if(DEBUG_SETTING)printf("CHECK\n")

/**********************************************************
 * functions definition
 **********************************************************/

// any number param preprocessor
#define NARGS_SEQ(_1,_2,_3,_4,_5,_6,_7,_8,_9,N,...) N
#define NARGS(...) NARGS_SEQ(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1)
// short cut
#define String char* 
#define $(...) String_newCombineString(NARGS(__VA_ARGS__), __VA_ARGS__)
#define $$ String_newCombineString
#define _ String_numberToString
#define _dec String_numberToDecimalString
#define _num(...) String_numberToStringArg(NARGS(__VA_ARGS__), __VA_ARGS__)
#define _isEqual String_checkIfStringIsEqual
#define print(...) String_print(NARGS(__VA_ARGS__), __VA_ARGS__)

/**********************************************************
 * string api functions
 **********************************************************/

// main api
char* String_newString(char* newString);
char* String_newCombineString(unsigned int numOfArg, ...);
bool String_isNumberFormat(const char* toBeChecked);
char* String_numberToDecimalString(long double number, unsigned int numOfDecimal);
char* String_numberToString(int number);
char* String_numberToStringArg(unsigned int numOfArg, ...);
void String_print(unsigned int numOfArg, ...);
// other api
char* String_setLowerCase(char* string);
char* String_setUpperCase(char* string);
int String_compareString(char* string1, char* string2, char* type);
bool String_isEqual(char* string1, char* string2, char* type);
char** String_readFileByChar(char* fileName, int* arraySize);
void String_freeStringArray(char** array, int arraySize);
bool String_checkifEmailFormat(char* string);
void String_removeWhiteSpace(char* string);

#endif
