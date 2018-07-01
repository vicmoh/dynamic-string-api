/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

// guard
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

// include libraries
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

typedef struct listNode{
    void* data;
    struct listNode* previous;
    struct listNode* next;
} Node;

typedef struct ListIteratorClass{
	Node* current;
} ListIterator;

typedef struct ListClass{
    Node* head;
    Node* tail;
    int length;
    void (*deleteData)(void* toBeDeleted);
    int (*compare)(const void* first,const void* second);
    char* (*printData)(void* toBePrinted);
    // methods
    void (*insertFront)(struct ListClass* list, void* toBeAdded);
    void (*insertBack)(struct ListClass* list, void* toBeAdded);
    void (*insertSorted)(struct ListClass* list, void* toBeAdded);
    void (*destroy)(struct ListClass* list);
    void* (*deleteDataFromList)(struct ListClass* list, void* toBeDeleted);
    void* (*pop)(struct ListClass* list);
    void* (*getFromFront)(struct ListClass list);
    void* (*getFromBack)(struct ListClass list);
    void* (*findElement)(struct ListClass list, bool (*customCompare)(const void* first,const void* second), const void* searchRecord);
    int (*getLength)(struct ListClass list);
    char* (*$toString)(struct ListClass list);
    ListIterator (*createIterator)(struct ListClass list);
    ListIterator (*createBackIterator)(struct ListClass list);
    void* (*nextElement)(struct ListIteratorClass* iter);
    void* (*prevElement)(struct ListIteratorClass* iter);
} List;

/**********************************************************
 * List Function
 **********************************************************/

// list constructor
List* new_List(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second));
Node* list_newNode(void* data);
// insert function
void list_insertFront(List* list, void* toBeAdded);
void list_insertBack(List* list, void* toBeAdded);
void list_insertSorted(List* list, void* toBeAdded);
// delete function
void list_free(List* list);
void* list_deleteDataFromList(List* list, void* toBeDeleted);
// getter function
void* list_pop(List* list);
void* list_getFromFront(List list);
void* list_getFromBack(List list);
void* list_findElement(List list, bool (*customCompare)(const void* first,const void* second), const void* searchRecord);
int list_getLength(List list);
char* list_$toString(List list);
// iterator function
ListIterator list_createIterator(List list);
ListIterator list_createBackIterator(List list);
void* list_nextElement(ListIterator* iter);
void* list_prevElement(ListIterator* iter);

#endif