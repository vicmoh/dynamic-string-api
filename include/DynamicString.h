/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

// guard
#ifndef _DYNAMIC_STRING_H_
#define _DYNAMIC_STRING_H_

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
 * Preprocessor
 **********************************************************/

// 20 param preprocessor
#define ARGS_SEQUENCE(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,N,...) N
#define ARGS(...) ARGS_SEQUENCE(\
__VA_ARGS__, 20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)\
// try catch
#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ENDTRY } }while(0)
#define THROW longjmp(ex_buf__, 1)
// string preprocessor
#define String char* 
#define $(...) new_String(ARGS(__VA_ARGS__), __VA_ARGS__)
#define $$( var ) string_advanceFree( (void*) &var ); var
#define $isEqual string_isEqual
#define _ string_numberToStringInt
#define _dec string_numberToStringDecimal
#define _num(...) string_numberToString(ARGS(__VA_ARGS__), __VA_ARGS__)
// other quick preproccessor
#define print(...) string_print(ARGS(__VA_ARGS__), __VA_ARGS__)
#define loop(x, num) for(int x=0; x<num; x++)
#define free( var ) dummy_safeFree( (void*) &var ); var = NULL
// credit for lambda https://blog.noctua-software.com/c-lambda.html
#define LAMBDA(varfunction) ({ varfunction function;})
// class preprocessor
#define FUNCTION( name, param ) name
#define CONSTRUCTOR_MALLOC(className) className* this = malloc(sizeof(className));
#define CONSTRUCTOR( code ) code
#define CLASS_( className, param, constructor, function) \
className* new_##className param{\
    CONSTRUCTOR_MALLOC(className)\
    constructor\
    return this;\
} function
#define CLASS( className, param, instance, constructor, function) \
typedef struct{\
    instance;\
} className;\
className* new_##className param{\
    CONSTRUCTOR_MALLOC(className)\
    constructor\
    return this;\
} function

/**********************************************************
 * String Function
 **********************************************************/

// string constructor, which returns dynamic strings
String new_String(unsigned int numOfArg, ...);
// number to string functions
String string_numberToString(unsigned int numOfArg, ...);
String string_numberToStringInt(int number);
String string_numberToStringDecimal(long double number, unsigned int numOfDecimal);
// string predicate functions
int string_compareString(String string1, String string2, bool isIgnoreCase);
bool string_isEqual(String string1, String string2, bool isIgnoreCase);
bool string_isNumberFormat(const String toBeChecked);
bool string_isEmailFormat(String toBeChecked);
// setter function
String string_setString(String toBeSet);
void string_setLowerCase(String toBeSet);
void string_setUpperCase(String toBeSet);
void string_setNoWhiteSpace(String toBeSet); 
void string_setSlice(String toBeSliced, unsigned int startIndexToKeep, unsigned int endIndexToKeep);
// void funtions
void string_print(unsigned int numOfArg, ...);
void string_freeStringArray(String* array, int arraySize);
void string_advanceFree(void** stringToBeFreed);
void string_free(void* stringToBeFreed);
// other functions
String* string_readFileByChar(String fileName, int* arraySize);
// dummy function for constructor
String dummy_print(void* toBePrinted);
void dummy_delete(void* toBeDeleted);
int dummy_compare(const void* first, const void* second);
void dummy_safeFree(void** toBeFreed);
void free_function(void* toBefreed);

#endif
