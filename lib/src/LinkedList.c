/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

#include "DynamicString.h"
#include "LinkedList.h"

/**********************************************************
 * list constructor
 **********************************************************/

List* new_List(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second)){
    //init all the instance vars of the list
    List* new = malloc(sizeof(List));
    new->head = NULL;
    new->tail = NULL;
    new->length = 0;
    //assign the pointer functions
    new->deleteData = deleteFunction;
    new->compare = compareFunction;
    new->printData = printFunction;
    // methods
    new->insertFront = list_insertFront;
    new->insertBack = list_insertBack;
    new->insertSorted = list_insertSorted;
    new->destroy = list_free;
    new->deleteDataFromList = list_deleteDataFromList;
    new->pop = list_pop;
    new->getFromBack = list_getFromBack;
    new->getFromFront = list_getFromFront;
    new->findElement = list_findElement;
    new->getLength = list_getLength;
    new->$toString = list_$toString;
    new->createIterator = list_createIterator;
    new->createBackIterator = list_createBackIterator;
    new->nextElement = list_nextElement;
    new->prevElement = list_prevElement;
    //return the new list
    return new;
}//end constructor

Node* list_newNode(void* data){
    //init all the struct node vars
    Node* newNode = malloc(sizeof(Node) /*+ sizeof(data)*/);
    newNode->data = data;
    newNode->next = NULL;
    newNode->previous = NULL;
    //return the new node
    return newNode;
}//end node

/**********************************************************
 * insert function
 **********************************************************/

void list_insertFront(List* list, void* toBeAdded){
    //check if list or the data is nil
    if(list == NULL || toBeAdded == NULL){
        return;
    }//end if
    //create the new node
    Node* newNode = list_newNode(toBeAdded);
    //insert the data at the front
    if(list->head == NULL){
        //init the head and tail
        list->head = newNode;
        list->tail = newNode;
    }else{
        list->head->previous = newNode;
        newNode->next = list->head;
        list->head = newNode;
    }//end else
    list->length++;
}//end func

void list_insertBack(List* list, void* toBeAdded){
    //check if the list or the data is nil
    if(list == NULL || toBeAdded == NULL){
        return;
    }//end if
    //create a new node
    Node* newNode = list_newNode(toBeAdded);
    //insert the data at the back
    if(list->tail == NULL){
        //init the head and tail
        list->head = newNode;
        list->tail = newNode;
    }else{
        list->tail->next = newNode;
        newNode->previous = list->tail;
        list->tail = newNode;
    }//end if
    list->length++;
}//end func

void list_insertSorted(List* list, void* toBeAdded){
    //check if the list and data is empty
    if(list == NULL || toBeAdded == NULL){
        return;
    }//end
    //dec vars
    Node* newNode = list_newNode(toBeAdded);
    Node* currentNode = currentNode = list->head;
    //check if the head and tail is empty
    if(list->head == NULL && list->tail == NULL){
        list->head = newNode;
        list->tail = newNode;
        list->length++;
        return;
    }//end if
    //iterate all the node and add to to proper spot
    while(currentNode != NULL){
        //case if node is inserted at the head
        if (list->compare != NULL){
            if (list->compare(newNode->data, currentNode->data) < 0) {
                list->head = newNode;
                newNode->next = currentNode;
                currentNode->previous = newNode;
                list->length++;
                return;
            }//end if
        }//end if
        //case if the node is inserted at the tail
        if (currentNode->next == NULL) {
            list->tail = newNode;
            newNode->previous = currentNode;
            currentNode->next = newNode;
            list->length++;
            return;
        }//end if
        //case if node is inserted in the middle
        if (list->compare != NULL){
            if (list->compare(newNode->data, currentNode->data) >= 0 && list->compare(newNode->data, currentNode->next->data) < 0) {
                newNode->previous = currentNode;
                newNode->next = currentNode->next;
                currentNode->next = currentNode->next->previous = newNode;
                list->length++;
                return;
            }//end if
        }//end if
        //iterate to the next node
        currentNode = currentNode->next;
    }//end while
}//end func

/**********************************************************
 * delete function
 **********************************************************/

void list_free(List* list){
    //check if the list is empty
    if(list == NULL){
        return;
    }//end if
    //dec vars
    Node* tempNode;
    Node* currentNode = list->head;
    //go through the list and delete all node
    while(currentNode != NULL){
        tempNode = currentNode;
        currentNode = currentNode->next;
        //free and remove the data
        if(list->deleteData != NULL){
            list->deleteData(tempNode->data);
        }//end if
        free(tempNode);
    }//end while
    //make the head and the tail null  after deleting all the nodes
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}//end func

void* list_deleteDataFromList(List* list, void* toBeDeleted){
    //check if the list and data is empty
    if(list == NULL || toBeDeleted == NULL){
        return NULL;
    }//end
    //dec vars
    void* nodeToBeReturned;
    Node* nodeToBeDeleted;
    Node* currentNode = list->head;
    //iterate through the list and find the data to be deleted
    while(currentNode != NULL){
        //if the data to be deleted is found
        if ( list->compare != NULL){
            if(list->compare(currentNode->data, toBeDeleted) == 0 || currentNode->data == toBeDeleted){
                //case if the node is at the head
                if(currentNode->previous == NULL){
                    nodeToBeDeleted = currentNode;
                    list->head = currentNode->next;
                    list->head->previous = NULL;
                    //free the node and returned
                    nodeToBeReturned = currentNode->data;
                    free(nodeToBeDeleted);
                    list->length--;
                    return nodeToBeReturned;
                }//end if
                //case if the node is at the tail
                if(currentNode->next == NULL){
                    nodeToBeDeleted = currentNode;
                    list->tail = currentNode->previous;
                    list->tail->next = NULL;
                    //free the node and returned
                    nodeToBeReturned = currentNode->data;
                    free(nodeToBeDeleted);
                    list->length--;
                    return nodeToBeReturned;
                }//end if
                //case if the node is at the middle
                if(currentNode->next != NULL && currentNode->previous != NULL){
                    nodeToBeDeleted = currentNode;
                    currentNode->previous->next = currentNode->next;
                    currentNode->next->previous = currentNode->previous;
                    //free the node and returned
                    nodeToBeReturned = currentNode->data;
                    free(nodeToBeDeleted);
                    list->length--;
                    return nodeToBeReturned;
                }//end if
            }//end if
        }//end if
        //iterate through the list
        currentNode = currentNode->next;
    }//end while
    return NULL;
}//end func

/**********************************************************
 * getter function
 **********************************************************/

void* list_pop(List* list){
    //check if the list and data is empty
    if(list == NULL){
        return NULL;
    }//end
    //dec vars
    void* dataToBeReturned;
    Node* nodeToBeDeleted = list->head;
    Node* currentNode = list->head;
    if(list->length == 0 || currentNode == NULL){
        return NULL;
    }//end if
    //case if the node is at the head
    if(currentNode->next != NULL){
        nodeToBeDeleted = currentNode;
        list->head = currentNode->next;
        list->head->previous = NULL;
        //free the node and returned
        dataToBeReturned = currentNode->data;
        free(nodeToBeDeleted);
        list->length--;
        //printf("list->length = %d\n", list->length);
        return dataToBeReturned;
    }else{
        nodeToBeDeleted = currentNode;
        //free the node and returned
        dataToBeReturned = currentNode->data;
        free(nodeToBeDeleted);
        //its done
        list->tail = NULL;
        list->head = NULL;
        list->length--;
        return dataToBeReturned;
    }//end if
    return NULL;
}//end func

void* list_getFromFront(List list){
    //if head exist get the head, else return null
    if(list.head != NULL){
        return list.head->data;
    }else{
        return NULL;
    }//end if
}//end func

void* list_getFromBack(List list){
    //if tail exist get the head, else return null
    if(list.tail != NULL){
        return list.tail->data;
    }else{
        return NULL;
    }//end if
}//end func

void* list_findElement(List list, bool (*customCompare)(const void* first,const void* second), const void* searchRecord){
    //check if the list and data is empty
    if(list.head == NULL){
        return NULL;
    }//end
    //dec vars
    Node* currentNode = list.head;
    //go through the list and find the searchRecord
    while(currentNode != NULL){
        if(customCompare(currentNode->data, searchRecord) == true){
            return currentNode->data;
        }//end if
        currentNode = currentNode->next;
    }//end while
    return NULL;
}//end func

int list_getLength(List list){
    //check if the list and data is empty
    if(list.head == NULL || list.tail == NULL){
        list.length = 0;
        return 0;
    }//end
    //dec vars
    int countNodes = 0;
    Node* currentNode = list.head;
    //go through the list and count the nodes in the list
    while(currentNode != NULL){
        countNodes++;
        list.length = countNodes;
        currentNode = currentNode->next;
    }//end while
    list.length = countNodes;
    return countNodes;
}//end func

char* list_$toString(List list){
    //check if there is somehing in the list
    if(list.head == NULL || list.tail == NULL){
        char* feedback = calloc(1, sizeof(char) + strlen("No List\n")+9);
        strcpy(feedback, "No list\n"); 
        return feedback;
    }//end if
    
    //declare var
    char *string = calloc(1, sizeof(string)+9);
    //char *tempString = malloc(sizeof(tempString));
    int total = 0;
    Node* currentNode;
    //init current node at the start of the list
    currentNode = list.head;
    //iterate through the list
    if (list.printData != NULL) {
        while (currentNode != NULL) {
            char* stringDataSize = list.printData(currentNode->data);
            total = total + strlen(stringDataSize) + 99;
            string = realloc(string, sizeof(char) + total);
            strcat(string, stringDataSize);
            free(stringDataSize);
            /*if(currentNode->next != NULL){
                strcat(string, "\n");
            }//end if*/
            currentNode = currentNode->next;
        }//end while
    }//end if
    strcat(string, "\0");
    return string;
}//end func

/**********************************************************
 * iterator function
 **********************************************************/

ListIterator list_createIterator(List list){
    ListIterator iterator;
    iterator.current = list.head;
    return iterator;
}//end func

ListIterator list_createBackIterator(List list){
    ListIterator iterator;
    iterator.current = list.tail;
    return iterator;
}//end func

void* list_nextElement(ListIterator* iter){
    //dec vars
    void* dataToBeReturned;
    //if the current is not null, iterate
    if(iter->current != NULL){
        dataToBeReturned = iter->current->data;
        iter->current = iter->current->next;
        return dataToBeReturned;
    }else{
        return NULL;
    }//end if
}//end func

void* list_prevElement(ListIterator* iter){
    //dec vars
    void* dataToBeReturned;
    //if the current is not null, iterate
    if(iter->current != NULL){
        dataToBeReturned = iter->current->data;
        iter->current = iter->current->previous;
        return dataToBeReturned;
    }else{
        return NULL;
    }//end if
}//end func
