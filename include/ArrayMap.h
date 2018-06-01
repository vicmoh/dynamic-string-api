/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

// guard
#ifndef _ARRAYMAP_H_
#define _ARRAYMAP_H_

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

#define for_in( x , object ) for(int x = 0; x < ( object->length ) ; x++)

/**********************************************************
 * Array Class
 **********************************************************/

typedef struct{
    void* data;
    char* tag;
}ArrayIndex;

typedef struct ArrayClass{
    unsigned int length;
    ArrayIndex* index;
    void (*deleteFunction)(void *);
    void (*add)(struct ArrayClass*, void* toBeAdded);
    void* (*getIndexOf)(struct ArrayClass* object, int theIndex);
    void* (*removeIndexOf)(struct ArrayClass* object, int theIndex);
    void (*free)(void* object);
}Array;

// construtor
Array* new_Array(void (*deleteFunction)(void *));
// functions
void Array_add(Array* object, void* toBeAdded);
void* Array_getIndexOf(Array* object, int index);
void Array_removeIndexOf(Array* object, int index);
// free
void Array_free(void* ArrayObjectToBeFreed);

/**********************************************************
 * Map Class
 **********************************************************/

typedef struct{
    void* data;
    char key[256];
    unsigned int index;
}MapData;

typedef struct{
    unsigned int tableSize;
    MapData* table;
    void (*deleteFunction)(void*);
    Array* list;
    unsigned int length;
}Map;

// constructor
Map* new_Map(void (*deleteFunction)(void* deleteFunction));
void Map_add(Map* object, char* key, void* dataToBeAdded);
void* Map_get(Map* object, char* key);
unsigned int Map_hashDJB(char* string, unsigned int length);
int Map_isPrime(const int toBeChecked);
int Map_nextPrime(int number);
void Map_free(void* toBeFree);

#endif