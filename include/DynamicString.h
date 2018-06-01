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
 * Preprocessor
 **********************************************************/

// 20 param preprocessor
#define ARGS_SEQUENCE(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,N,...) N
#define ARGS(...) ARGS_SEQUENCE(\
__VA_ARGS__, 20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)\

// system preprocessor
#define String char* 
#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ENDTRY } }while(0)
#define THROW longjmp(ex_buf__, 1))
// string preprocessor
#define $(...) new_String(ARGS(__VA_ARGS__), __VA_ARGS__)
#define $$( var ) String_free( (void*) &var ); var
#define _ String_$numberToStringInt
#define _dec String_$numberToStringDecimal
#define _num(...) String_$numberToString(ARGS(__VA_ARGS__), __VA_ARGS__)
#define _isEqual String_isEqual
#define print(...) String_print(ARGS(__VA_ARGS__), __VA_ARGS__)
//credit for lambda https://blog.noctua-software.com/c-lambda.html
#define LAMBDA(varfunction) ({ varfunction function;})
// class preprocessor
#define FUNCTION(className, funcName, returnType, param, code)
#define CONSTRUCTOR_MALLOC(className) className* this = malloc(sizeof(className));
#define CONSTRUCTOR( code ) code
#define VAR( code ) code
#define CLASS( className, constructor, function) \
className* new_##className(){\
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
void String_free(void** stringToBeFreed);
// other functions
String* String_readFileByChar$(String fileName, int* arraySize);
// dummy function for constructor
String Dummy_print(void* toBePrinted);
void Dummy_delete(void* toBeDeleted);
int Dumm_compare(const void* first, const void* second);

#endif
