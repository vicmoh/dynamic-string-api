/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

#include "DynamicString.h"
#include "ArrayMap.h"
#include "math.h"

/**********************************************************
 * Array functions
 **********************************************************/

Array* new_Array(void (*deleteFunction)(void *)){
    Array* new = malloc(sizeof(Array));
    new->index = NULL;
    new->length = 0;
    new->deleteFunction = deleteFunction;
    // func
    new->add = array_add;
    new->getIndexOf = array_getIndexOf;
    new->removeIndexOf = array_getIndexOf;
    new->destroy = array_free;
    return new;
}//end constructor

void array_add(Array* object, void* toBeAdded){
    if(object == NULL){
        return;
    }//end if
    object->length++;
    if(object->index == NULL){
        int size = object->length;
        object->index = malloc(sizeof(ArrayIndex)*size);
        object->index[object->length-1].data = toBeAdded;
    }//end if
    if(object->index != NULL){
        int size = object->length;
        object->index = realloc(object->index, sizeof(ArrayIndex)*size);
        object->index[object->length-1].data = toBeAdded;
    }//end if
}//end func

void* array_getIndexOf(Array* object, int index){
    if(object == NULL){
        return NULL;
    }//end if
    if(index > object->length-1){
        index = object->length;
    }else if(index < 0){
        index = 0;
    }//end if
    return object->index[index].data;
}//end func

void array_removeIndexOf(Array* object, int indexToDelete){
    //error check
    if(indexToDelete > object->length-1 || object == NULL){
        return;
    }else if(indexToDelete < 0){
        return;
    }//end if

    // loop through and delete
    void* dataToBeDeleted = NULL;
    bool foundIndex = false;
    for(int x=indexToDelete; x<object->length; x++){
        if(indexToDelete == x){
            foundIndex = true;
            dataToBeDeleted = object->index[x].data;
        }//end if
        if(foundIndex == true){
            if(x != object->length-1){
                object->index[x].data = object->index[x+1].data;
            }else if(x == object->length-1){
                object->index[x].data = NULL;
            }//end if
        }//end if
    }//end for

    // delete and realloc size
    if(object->deleteFunction != NULL && dataToBeDeleted != NULL){
        object->deleteFunction(dataToBeDeleted);
    }//end if
    if(foundIndex == true){
        object->length--;
        object->index = realloc(object->index, sizeof(ArrayIndex)*object->length);
    }//end if
}//end func

void array_free(void* toBeFreed){
    Array* object = (Array*)toBeFreed;
    if(object == NULL){
        return;
    }//end if
    for(int x=0; x<object->length; x++){
        if(object->deleteFunction == NULL){
            break;
        }//end if
        if(object->index == NULL){
            continue;
        }//end if
        if(object->index[x].data != NULL){
            object->deleteFunction(object->index[x].data);
        }//end if
    }//end for
    if(object->index != NULL){
        free(object->index);
    }//end free
    free(object);
}//end func

/**********************************************************
 * map functions
 **********************************************************/

Map* new_Map(unsigned int tableSize, void(*deleteFunction)(void*)){
    Map* new = malloc(sizeof(Map));
    new->tableSize = map_nextPrime(tableSize);
    new->table = malloc(sizeof(MapData*)*new->tableSize);
    new->deleteFunction = deleteFunction;// for now its null
    for(int x=0; x<new->tableSize; x++){
        new->table[x] = NULL;
    }//end if
    
    // add list
    new->list = new_Array(NULL);
    // put list to keep track
    new->length = 0;
    // func
    new->add = map_add;
    new->get = map_get;
    new->destroy = map_free;
    //return 
    return new;
}//end constructor

MapData* map_initData(char* key, void* data){
    if(key == NULL || data == NULL){
        return NULL;
    }//end if
    if(strlen(key) > 255){
        return NULL;
    }//end if
    
    // init data
    MapData* new = malloc(sizeof(MapData));
    new->next = NULL;
    new->data = data;
    strcpy(new->key, key);
    return new;
}//end consrtuctor

void map_add(Map* object, char* key, void* dataToBeAdded){
    //error check
    if(object == NULL || key == NULL){
        return;
    }//end if
    if(strlen(key) > 255){
        printf("Max key length is 255 string");
        return;
    }//end if

    unsigned int index = map_hashDJB(key, object->tableSize);
    bool isDataExist = false;
    if(object->table[index] != NULL){
        isDataExist = true;
    }//end if

    // added the hash (bug here)
    if(isDataExist == true){
        while(true){
            // times 2 size the table
            unsigned int nextPrimeNum = map_nextPrime(object->tableSize*2);
            object->tableSize = nextPrimeNum;
            // printf("next prime num is %d\n", nextPrimeNum);

            // create more mem
            object->table = realloc(object->table, sizeof(MapData*)*nextPrimeNum);

            // clear the map
            for(int x=0; x<object->tableSize; x++){
                object->table[x] = NULL;
            }//end if

            // get data from array
            bool isCollision = false;
            for(int x=0; x<object->list->length; x++){
                MapData* oldData = array_getIndexOf(object->list, x);

                unsigned int newIndex = map_hashDJB(oldData->key, object->tableSize);
                if(object->table[newIndex] != NULL){
                    // printf("collision!!!");
                    isCollision = true;
                }//end func
                // printf("old data is %s, length = %d\n", (char*)oldData->data, object->list->length);
                object->table[newIndex] = oldData;
            }//end for

            if(isCollision == true){
                continue;
            }//end if
                
            // if empty add the data, else keeping looping
            unsigned int indexToBeAdded = map_hashDJB(key, object->tableSize);
            if(object->table[indexToBeAdded] == NULL){
                // add the data
                MapData* newData = map_initData(key, dataToBeAdded);
                object->table[indexToBeAdded] = newData;
                object->length++;

                // adding to a data to array
                array_add(object->list, newData);

                // // debug
                // for(int x=0; x<object->tableSize; x++){
                //     char tempStr[256];
                //     if(object->table[x] != NULL){
                //         MapData* tempData = object->table[x];
                //         strcpy(tempStr, (char*)tempData->data);
                //         printf("data = %s\n", tempStr);
                //     }//end if
                // }//end for

                break;
            }//end if
        }//end while
    }else{
        // add the data
        MapData* newData = map_initData(key, dataToBeAdded);
        object->table[index] = newData;
        object->length++;

        // adding to a data to array
        array_add(object->list, newData);
    }//end if
}//end func

void* map_get(Map* object, char* key){
    //error check
    if(object == NULL || key == NULL){
        return NULL;
    }//end if
    if(strlen(key) > 255){
        return NULL;
    }//end if
    unsigned int index = map_hashDJB(key, object->tableSize);

    if(object->table[index] == NULL){
        return NULL;
    }else{
        MapData* dataToBeReturn = object->table[index];
        return dataToBeReturn->data;
    }//end if
}//end func

unsigned long map_hashDJB(const char* string, unsigned int tableSize) {
    // hash aka K&R, credit from
    // https://stackoverflow.com/questions/7666509/hash-function-for-string
    unsigned long hashval;
    for (hashval = 0; *string != '\0'; string++){
        hashval = *string + 31*hashval;
    }//end for
    return hashval % tableSize;
}//end func

int map_isPrime(const int number) {
    if (number < 2) { 
        return -1; 
    }//end if
    if (number < 4) { 
        return 1; 
    }//end if
    if ((number % 2) == 0) { 
        return 0; 
    }//end if
    for (int i = 3; i <= floor(sqrt((double) number)); i += 2) {
        if ((number % i) == 0) {
            return 0;
        }//end if
    }//end for
    return 1;
}//end func

int map_nextPrime(int number) {
    while (map_isPrime(number) != 1) {
        number++;
    }//end while
    return number;
}//end func

void map_free(void* mapObjectToBeFreed){
    if(mapObjectToBeFreed == NULL){
        return;
    }//end if
    
    Map* delete = mapObjectToBeFreed;
    
    //delete the list
    for(int x=0; x<delete->tableSize; x++){
        if(delete->table[x] != NULL){
            MapData* node = delete->table[x];
            if(delete->deleteFunction != NULL){
                delete->deleteFunction(node->data);
            }//end if
            free(node);
        }//end if
    }//end for

    array_free(delete->list);
    free(delete->table);
    free(delete);
}//end func

void map_freeMapData(void* delete){
    MapData* data = delete;
    free(data);
}//end func