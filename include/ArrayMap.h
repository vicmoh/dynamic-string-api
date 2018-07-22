/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

// guard
#ifndef _ARRAY_MAP_H_
#define _ARRAY_MAP_H_

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
 * Function Definition
 **********************************************************/

// for in like javascript
#define for_in( x , object ) for(int x = 0; x < ( object->length ) ; x++)
// garbage collector 
#define MEM_START _GARBAGE_COLLECTOR_ = new_Array(garabage_freeFunction)
#define MEM_ADD( var ) array_add(_GARBAGE_COLLECTOR_, var)
#define MEM_END array_free(_GARBAGE_COLLECTOR_)
#define M( var ) MEM_ADD( var )

/**********************************************************
 * Array Class
 **********************************************************/

typedef struct{
    void* data;
    char tag[256];
}ArrayIndex;

typedef struct ArrayClass{
    unsigned int length;
    ArrayIndex* index;
    void (*deleteFunction)(void *);
    // methods
    void (*add)(struct ArrayClass*, void* toBeAdded);
    void* (*getIndexOf)(struct ArrayClass* object, int theIndex);
    void* (*removeIndexOf)(struct ArrayClass* object, int theIndex);
    void (*destroy)(void* object);
}Array;

Array* _GARBAGE_COLLECTOR_;

// construtor
Array* new_Array(void (*deleteFunction)(void *));
// functions
void array_add(Array* object, void* toBeAdded);
void* array_getIndexOf(Array* object, int index);
void array_removeIndexOf(Array* object, int index);
// free
void array_free(void* ArrayObjectToBeFreed);

/**********************************************************
 * Map Class
 **********************************************************/

typedef struct MapDataClass{
    void* data;
    char key[256];
    struct MapDataClass* next;
}MapData;

typedef struct MapClass{
    unsigned int tableSize;
    MapData** table;
    void (*deleteFunction)(void*);
    Array* list;
    unsigned int length;
    // func
    void (*add)(struct MapClass* object, char* key, void* dataToBeAdded);
    void* (*get)(struct MapClass* object, char* key);
    void (*destroy)(void* mapToBeFreed);
}Map;

// constructor
Map* new_Map(unsigned int tableSize, void (*deleteFunction)(void* deleteFunction));
MapData* map_initData(char* key, void* data);
void map_add(Map* object, char* key, void* dataToBeAdded);
void* map_get(Map* object, char* key);
unsigned long map_hashDJB(const char* string, unsigned int tableSize);
int map_isPrime(const int toBeChecked);
int map_nextPrime(int number);
void map_free(void* toBeFreed);
void map_freeMapData(void* toBeFreed);
void garabage_freeFunction(void* toBeDeleted);

#endif