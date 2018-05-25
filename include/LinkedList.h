/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

// guard
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

// include libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**********************************************************
 * Object Struct
 **********************************************************/

typedef struct listNode{
    void* data;
    struct listNode* previous;
    struct listNode* next;
} Node;

typedef struct listHead{
    Node* head;
    Node* tail;
    int length;
    void (*deleteData)(void* toBeDeleted);
    int (*compare)(const void* first,const void* second);
    char* (*printData)(void* toBePrinted);
} List;

typedef struct iter{
	Node* current;
} ListIterator;

/**********************************************************
 * List Function
 **********************************************************/

// list constructor
List* new_List(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second));
Node* List_newNode(void* data);
// insert function
void List_insertFront(List* list, void* toBeAdded);
void List_insertBack(List* list, void* toBeAdded);
void List_insertSorted(List* list, void* toBeAdded);
// delete function
void List_clearList(List* list);
void* List_deleteDataFromList(List* list, void* toBeDeleted);
// getter function
void* List_pop(List* list);
void* List_getFromFront(List list);
void* List_getFromBack(List list);
void* List_findElement(List list, bool (*customCompare)(const void* first,const void* second), const void* searchRecord);
int List_getLength(List list);
char* List_$toString(List list);
// iterator function
ListIterator List_createIterator(List list);
ListIterator List_createBackIterator(List list);
void* List_nextElement(ListIterator* iter);
void* List_prevElement(ListIterator* iter);

#endif