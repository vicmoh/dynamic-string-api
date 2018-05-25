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
 * Object Struct
 **********************************************************/

typedef struct{
    void* data;
    char* tag;
}Array_Index;

typedef struct ArrayClass{
    unsigned int length;
    Array_Index* index;
    void (*deleteFunction)(void *);
    void (*add)(struct ArrayClass*, void* toBeAdded, char* tag_nullIfNoTag);
    void* (*getIndexOf)(struct ArrayClass* object, int theIndex);
    void* (*removeIndexOf)(struct ArrayClass* object, int theIndex);
    void (*free)(void* object);
}Array;

/**********************************************************
 * Array Function
 **********************************************************/

// construtor
Array* new_Array(void (*deleteFunction)(void *));
// functions
void Array_add(Array* object, void* toBeAdded, char* tag);
void* Array_getIndexOf(Array* object, int index);
void Array_removeIndexOf(Array* object, int index);
// free
void Array_free(void* ArrayObjectToBeFreed);

#endif