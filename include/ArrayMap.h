/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

// guard
#ifndef _ARRAY_MAP_H_
#define _ARRAY_MAP_H_

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
#include <math.h>

/**********************************************************
 * function definition
 **********************************************************/

// 20 param preprocessor
#define ARGS_SEQUENCE(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,N,...) N
#define ARGS(...) ARGS_SEQUENCE(\
__VA_ARGS__, 20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)\
// for in like javascript
#define for_in( x , object ) for(int x = 0; x < ( object->length ) ; x++)
// functions
#define array_addMultiple( obj, ...) array_addMultipleData(obj, ARGS(__VA_ARGS__), __VA_ARGS__)
// garbage collector 
#define MEM_START _GARBAGE_COLLECTOR_ = new_Array(free)
#define MEM( var ) array_add(_GARBAGE_COLLECTOR_, var)
#define MEM_ADD(...) array_addMultipleData( _GARBAGE_COLLECTOR_ , ARGS(__VA_ARGS__), __VA_ARGS__)
#define MEM_END array_free(_GARBAGE_COLLECTOR_)
#define M( var ) MEM_ADD( var )

/**********************************************************
 * struct data for array and map
 **********************************************************/

typedef struct{
    void* data;
    char key[256];
}ArrayMapData;

/**********************************************************
 * array class
 **********************************************************/

typedef struct ArrayClass{
    unsigned int length;
    ArrayMapData* index;
    void (*deleteFunction)();
}Array;

Array* _GARBAGE_COLLECTOR_;

// construtor
Array* new_Array(void (*deleteFunction)());
// getter and setter
void array_add(Array* object, void* toBeAdded);
void array_addMultipleData(Array* object, unsigned int numOfArg, ... );
void* array_get(Array* object, int index);
void array_remove(Array* object, int index);
// free
void array_free(void* ArrayObjectToBeFreed);

/**********************************************************
 * map class
 **********************************************************/

typedef struct MapClass{
    unsigned int tableSize;
    ArrayMapData** table;
    void (*deleteFunction)();
    Array* array;
    unsigned int length;
}Map;

// constructor
Map* new_Map(void (*deleteFunction)());
// getter and setter
void map_add(Map* object, char* key, void* dataToBeAdded);
void* map_get(Map* object, char* key);
void map_remove(Map* object, char* key);
void* map_iterator(Map* object, int index);
// funtions
int map_isPrime(const int toBeChecked);
int map_nextPrime(int number);
// free function
void map_free(void* toBeFreed);

#endif