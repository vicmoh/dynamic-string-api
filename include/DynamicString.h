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
#include <setjmp.h>

// macro
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
// system preprocessor
#define String char* 
#define _try do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define _catch } else {
#define _endtry } }while(0)
#define _throw longjmp(ex_buf__, 1)
// function shortcuts
#define $(...) new_String(NARGS(__VA_ARGS__), __VA_ARGS__)
#define $$ new_String
#define _ String_$numberToStringInt
#define _dec String_$numberToStringDecimal
#define _num(...) String_$numberToString(NARGS(__VA_ARGS__), __VA_ARGS__)
#define _isEqual String_isEqual
#define print(...) String_print(NARGS(__VA_ARGS__), __VA_ARGS__)

/**********************************************************
 * String Function
 **********************************************************/

// string constructor, which returns dynamic strings
String new_String(unsigned int numOfArg, ...);
// number to string functions
String String_$numberToString(unsigned int numOfArg, ...);
String String_$numberToStringInt(int number);
String String_$numberToStringDecimal(long double number, unsigned int numOfDecimal);
// string predicate functions
int String_compareString(String string1, String string2, bool isIgnoreCase);
bool String_isEqual(String string1, String string2, bool isIgnoreCase);
bool String_isNumberFormat(const String toBeChecked);
bool String_isEmailFormat(String toBeChecked);
// setter function
String String_$setString(String toBeSet);
void String_setLowerCase(String toBeSet);
void String_setUpperCase(String toBeSet);
void String_setNoWhiteSpace(String toBeSet); 
void String_setSlice(String toBeSliced, unsigned int startIndexToKeep, unsigned int endIndexToKeep);
// void funtions
void String_print(unsigned int numOfArg, ...);
void String_freeStringArray(String* array, int arraySize);
void String_free(void* stringToBeFreed);
// other functions
String* String_readFileByChar$(String fileName, int* arraySize);
// dummy function for constructor
String Dummy_print(void* toBePrinted);
void Dummy_delete(void* toBeDeleted);
int Dumm_compare(const void* first, const void* second);

#endif
