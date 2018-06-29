/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

#include "DynamicString.h"
#include "Tokenizer.h"

Token* new_Token(char* stringToBeSplit, const char* delimiter){
    // init
    Token* toBeReturned = malloc(sizeof(Token));
    toBeReturned->list = NULL;
    toBeReturned->length = 0; 
    toBeReturned->combine = token_combine;
    toBeReturned->search = token_search;
    toBeReturned->destroy = token_free;

    //error check
    if(stringToBeSplit == NULL || delimiter == NULL){
        return toBeReturned;
    }//end if

    //create string array
    int numOfSplits = 0;
    char** stringArray = calloc(sizeof(stringArray),(numOfSplits+1));

    //tokenize through thw code
    char *token;
    char* stringBuffer = calloc(sizeof(char*), strlen(stringToBeSplit)+1 );
    strcpy(stringBuffer, stringToBeSplit);
    token = strtok(stringBuffer, delimiter);

    //iterate through the tokem
    while(token != NULL) {
        //copy the split token
        char* newToken = calloc(sizeof(char*), strlen(token)+1);
        strcpy(newToken, token);
        stringArray[numOfSplits] = newToken;
        //keep going
        token = strtok(NULL, delimiter);
        //realloc more memory
        numOfSplits++;
        stringArray = realloc(stringArray, sizeof(stringArray)*(numOfSplits+1));
    }//end if 

    //return
    toBeReturned->length = numOfSplits;
    toBeReturned->list = stringArray;
    free(stringBuffer);
    return toBeReturned;
}//end func

char* token_combine(Token* token, unsigned int tokenStart, int unsigned tokenEnd){
    //prevent memory leaked
    tokenEnd++;
    if(tokenStart > tokenEnd || token == NULL){
        return NULL;
    }//end if
    //error check make its out of bound
    if(tokenEnd > token->length){
        tokenEnd = token->length;
    }//end

    //dec vars
    int memSize = 0;
    if(token->list[tokenStart] != NULL){
       memSize = strlen(token->list[tokenStart]) + 1;
    }//end if
    char* combinedString = calloc(sizeof(char*), (memSize)+1);
    
    //loop through and combined the string to one
    for(int x=tokenStart; x<tokenEnd; x++){
        //start to combined the string
        if(token->list[x] == NULL){
            char* newString = calloc(sizeof(char*), strlen("(NULL)")+1);
            strcpy(newString, "(NULL)");
            continue;
        }//end if
        char* newString = calloc(sizeof(char*), strlen(token->list[x])+1);
        strcpy(newString, token->list[x]);
        strcat(combinedString, newString);
        free(newString);
        // exit if its last one
        if(x == tokenEnd){
            strcat(combinedString, "\0");
            break;
        }//end if
        strcat(combinedString, " ");
        memSize += strlen(token->list[x]) + 1;
        combinedString = realloc(combinedString, sizeof(char*)*memSize);
    }//end if

    //return
    combinedString[strlen(combinedString)-1] = '\0';
    return combinedString;
}//end func

int token_search(Token* token, const char* stringToBeSearched, bool isItIndex){
    //dec vars
    int index = -1;
    int foundString = 0;

    //error check
    if(stringToBeSearched == NULL){
        return -1;
    }//end if

    //loop through to find the string
    for (int x = 0; x < token->length; x++){
        //if the string to be searched is found returned the size
        if (strcmp(token->list[x], stringToBeSearched) == 0){
            index = x; 
            foundString++;
        }//end if
    }//for loop

    //return based on the searched type
    if(isItIndex == true){
        return index;
    }else{
        return foundString;
    }//end if
}//end func

void token_free(void* toBeFreed){
    Token* delete = (Token*)toBeFreed;
    if(delete == NULL){
        return;
    }//end if
    for(int x=0; x<delete->length; x++){
        free(delete->list[x]);
    }//end for
    free(delete->list);
    delete->list = NULL;
    free(delete);
    delete = NULL;
    return;
}//end if