/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

// guard
#ifndef _DYNAMICSTRING_H_
#define _DYNAMICSTRING_H_

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

// macros
#define String char* 
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
 * Function Definition
 **********************************************************/

// 9 param preprocessor
#define NARGS_SEQ(_1,_2,_3,_4,_5,_6,_7,_8,_9,N,...) N
#define NARGS(...) NARGS_SEQ(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1)
// function shortcuts
#define $(...) String_newCombineString(NARGS(__VA_ARGS__), __VA_ARGS__)
#define $$ String_newCombineString
#define _ String_numberToStringInt
#define _dec String_numberToStringDecimal
#define _num(...) String_numberToString(NARGS(__VA_ARGS__), __VA_ARGS__)
#define _isEqual String_checkIfStringIsEqual
#define print(...) String_print(NARGS(__VA_ARGS__), __VA_ARGS__)

/**********************************************************
 * String Function
 **********************************************************/

// string constructor, which returns dynamic strings
String String_newString(String newString);
String String_newCombineString(unsigned int numOfArg, ...);
// number to string functions
String String_numberToString(unsigned int numOfArg, ...);
String String_numberToStringInt(int number);
String String_numberToStringDecimal(long double number, unsigned int numOfDecimal);
// string predicate functions
int String_compareString(String string1, String string2, bool isIgnoreCase);
bool String_isEqual(String string1, String string2, bool isIgnoreCase);
bool String_isNumberFormat(const String toBeChecked);
bool String_isEmailFormat(String toBeChecked);
// string setter functions
String String_setLowerCase(String stringToBeSet);
String String_setUpperCase(String stringToBeSet);
String String_removeWhiteSpace(String stringToBeSet); 
// void funtions
void String_print(unsigned int numOfArg, ...);
void String_freeStringArray(String* array, int arraySize);
// other functions
String* String_readFileByChar(String fileName, int* arraySize);

#endif
