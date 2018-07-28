/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

// guard
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

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

/**********************************************************
 * object struct
 **********************************************************/

typedef struct listNode{
    void* data;
    struct listNode* previous;
    struct listNode* next;
} ListNode;

typedef struct ListIteratorClass{
	ListNode* current;
} ListIterator;

typedef struct ListClass{
    ListNode* head;
    ListNode* tail;
    int length;
    void (*deleteData)();
    int (*compare)();
    char* (*printData)();
} List;

/**********************************************************
 * list function
 **********************************************************/

// list constructor
List* new_List(char* (*printFunction)(),void (*deleteFunction)(),int (*compareFunction)());
ListNode* list_newNode(void* data);
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
char* list_toString(List list);
// iterator function
ListIterator list_createIterator(List list);
ListIterator list_createBackIterator(List list);
void* list_nextElement(ListIterator* iter);
void* list_prevElement(ListIterator* iter);

#endif