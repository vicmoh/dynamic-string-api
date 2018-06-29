/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

#include "DynamicString.h"

/**********************************************************
 * string constructor
 **********************************************************/

char* new_String(unsigned int numOfArg, ...) {
    // dec var
    va_list va;
    char* toBeReturned = string_setString("");

    // combine the strings
    va_start (va, numOfArg);
    // for(int x=0; x<numOfArg; x++){
    while(numOfArg--){
        char* curArg = va_arg(va, char*);
        bool isNull = false;
        if(curArg == NULL){
            isNull = true;
            curArg = string_setString("(NULL)");
        }//end if 

        // dynamic create more memory and combine the string
        size_t memSize = (strlen(toBeReturned)+strlen(curArg)+1);
        toBeReturned = realloc(toBeReturned, sizeof(char*)* memSize);
        char* buffer = string_setString(toBeReturned);
        sprintf(toBeReturned,"%s%s", buffer, curArg);

        // free
        free(buffer);
        if(string_isNumberFormat(curArg) || isNull == true){
            free(curArg);
        }//end if
    }//end if
    va_end (va);
    return toBeReturned;
}//end func

char* string_setString(char* newString){
    if(newString == NULL){
        char* stringIsNull = calloc(sizeof(char*), strlen("(NULL)")+1);
        strcpy(stringIsNull, "(NULL)");
        return stringIsNull;
    }//end if
    char* stringReturn = calloc(sizeof(char*), strlen(newString)+1);
    strcpy(stringReturn, newString);
    return(stringReturn);
}//end func

/**********************************************************
 * number to string
 **********************************************************/

char* string_numberToString(unsigned int numOfArg, ...){
    va_list va;
    char* toBeReturned = NULL;
    int counter = 0;
    int numOfDec = 0;
    long double value = 0;
    bool decArgIsExist = false;

    // with decimal if there is more than one
    va_start(va, numOfArg);
    while(numOfArg--){
        counter++;
        if(counter == 1){
            //when it is single arg
            value = va_arg(va, double);
            toBeReturned = string_numberToStringDecimal(value, 0);
        }else if(counter == 2){
            decArgIsExist = true;
            numOfDec = va_arg(va, int);
            break;
        }//end if
    }//end for

    // if there is decimal argument
    if(decArgIsExist == true){
        free(toBeReturned);
        toBeReturned = string_numberToStringDecimal(value, numOfDec);
    }//end if
    va_end(va);

    return toBeReturned;
}//end func

char* string_numberToStringInt(int number){
    int temp = number;
    char* toBeReturned = calloc(sizeof(char*), 99);
    sprintf(toBeReturned, "%d", temp);
    return toBeReturned;
}//end func

char* string_numberToStringDecimal(long double number, unsigned int numOfDecimal){
    char* toBeReturned = calloc(sizeof(char*), 99);
    char decimalFormat[99];
    sprintf(decimalFormat, "%%0.%dLf", numOfDecimal);
    sprintf(toBeReturned, decimalFormat, number);
    return toBeReturned;
}//end func

/**********************************************************
 * predicate functions
 **********************************************************/

int string_compareString(char* string1, char* string2, bool isIgnoreCase){
    // error check
    if(string1 == NULL && string2 == NULL){
        return false;
    }else if(string1 == NULL && string2 != NULL){
        return false;
    }else if(string1 == NULL && string2 != NULL){
        return false;
    }//end if
    //set temp string for the strings to not be manipulated
    char* tempString1 = string_setString(string1);
    char* tempString2 = string_setString(string2);
    int result;
    //compare with having both lower case
    if(isIgnoreCase == true){
        string_setLowerCase(tempString1);
        string_setLowerCase(tempString2);
        result = strcmp(tempString1, tempString2);
    }else{
        result = strcmp(tempString1, tempString2);
    }//end if
    //free and return
    free(tempString1);
    free(tempString2);
    return result;
}//end func

bool string_isEqual(char* string1, char* string2, bool isIgnoreCase){
    // error check
    if(string1 == NULL && string2 == NULL){
        return false;
    }else if(string1 == NULL && string2 != NULL){
        return false;
    }else if(string1 == NULL && string2 != NULL){
        return false;
    }//end if
    //set temp string for the strings to not be manipulated
    char* tempString1 = string_setString(string1);
    char* tempString2 = string_setString(string2);
    int result;
    //compare with having both lower case
    if(isIgnoreCase == true){
        string_setLowerCase(tempString1);
        string_setLowerCase(tempString2);
        result = strcmp(tempString1, tempString2);
    }else{
        result = strcmp(tempString1, tempString2);
    }//end if
    //free and return
    free(tempString1);
    free(tempString2);
    if(result == 0){
        return true;
    }//end if
    return false;
}//end func

bool string_isNumberFormat(const char* toBeChecked){
    if(toBeChecked == NULL){
        return false;
    }//end if
    bool isNumberOrPeriod = false;
    for(int x=0; x<strlen(toBeChecked); x++){
        // check if char is num
        if(NUMBER_RANGE(toBeChecked[x]) || toBeChecked[x] == '-' || toBeChecked[x] == '.'){
            isNumberOrPeriod = true;
        }else{
            return false;
        }//end if
    }//end if
    return isNumberOrPeriod;
}//end func

bool string_isEmailFormat(char* toBeChecked){
    //dec vars
    int foundAtSign = 0;
    int foundPeriod = 0;

    //error check
    if(toBeChecked == NULL){
        return false;
    }//end if

    //if toBeChecked size is greater than 5 it is impossible to be an email
    int stringLength = strlen(toBeChecked);
    if(stringLength < 5){
        return false;
    }//end if

    //go through the toBeChecked and check
    for(int x=1; x<strlen(toBeChecked)-1;x++){
        if (toBeChecked[x-1] != '@' && toBeChecked[x] == '@' && toBeChecked[x+1] != '@'){
            foundAtSign++;
        }//end if
        if( (toBeChecked[x-1] != '@' && toBeChecked[x-1] != '.') && toBeChecked[x] == '.' && ALPHABET_RANGE(toBeChecked[x+1]) && foundAtSign == 1 ){
            foundPeriod++;
        }//end if
    }//end for loop

    //return
    if (foundAtSign == 1 && foundPeriod >= 1){
        return true;
    }//end if
    return false;
}//end func

/**********************************************************
 * setter functions
 **********************************************************/

void string_setLowerCase(char* string){
    if(string == NULL){
        return;
    }//end if
    //loop through the char change to lower case
    for(int x=0; x <strlen(string)+1;x++){
        if(UPPERCASE_RANGE(string[x]) || LOWERCASE_RANGE(string[x])){
            string[x] = tolower(string[x]);
        }//end if
    }//end if
}//end func

void string_setUpperCase(char* string){
    if(string == NULL){
        return;
    }//end if
    //loop through the char change to upper case
    for(int x=0; x <strlen(string)+1;x++){
        if(UPPERCASE_RANGE(string[x]) || LOWERCASE_RANGE(string[x])){
            string[x] = toupper(string[x]);
        }//end if
    }//end if
}//end func

void string_setSlice(char* string, unsigned int startIndexToKeep, unsigned int endIndexToKeep){
    if(string == NULL){
        return;
    }//end if

    //dec var
    int memSize = 1;
    char* slicedString = calloc(sizeof(char*), memSize);

    //error check
    if(strlen(string) < startIndexToKeep){
        return;
    }//end if
    if(strlen(string) < endIndexToKeep){
        endIndexToKeep = strlen(string);
    }//end if

    // slice the string
    int indexToCopy = 0;
    for(int x=startIndexToKeep; x<=endIndexToKeep; x++){
        char charBuffer = string[x];
        slicedString[indexToCopy] = charBuffer;
        indexToCopy++;
        memSize++;
        slicedString = realloc(slicedString, sizeof(char*)*memSize);
    }//end 
    strcpy(string, slicedString);
    free(slicedString);
}//end func

void string_setNoWhiteSpace(char* string){
    //remove the space of the white spaces of the string
    if(string == NULL){
        return;
    }//end if
    if(strlen(string) < 3){
        return;
    }//end if
    //right to left
    for(int x = strlen(string)-1; x > 0; x--){
        if(string[x] == ' '){
            string[x] = '\0';
        }else if(string[x] != ' '){
            break;
        }//end
    }//end if
    //left to right
    for(int x = 0; x < strlen(string)-1; x++){
        if(string[x] == ' '){
            string[x] = '\0';
        }else if(string[x] != ' '){
            break;
        }//end
    }//end if
}//end func

/**********************************************************
 * void functions
 **********************************************************/

void string_print(unsigned int numOfArg, ...) {
    // dec var
    va_list va;
    char* toBePrinted = string_setString("");
    // combine the strings
    va_start (va, numOfArg);
    // for(int x=0; x<numOfArg; x++){
    while(numOfArg--){
        char* curArg = va_arg(va, char*);
        bool isNull = false;
        if(curArg == NULL){
            isNull = true;
            curArg = string_setString("(NULL)");
        }//end if
        size_t memSize = (strlen(toBePrinted)+strlen(curArg)+1);
        toBePrinted = realloc(toBePrinted, sizeof(char*)* memSize);
        char* buffer = string_setString(toBePrinted);
        sprintf(toBePrinted,"%s%s", buffer, curArg);
        //free
        free(buffer);
        if(string_isNumberFormat(curArg) || isNull == true){
            free(curArg);
        }//end if
    }//end if
    va_end (va);
    printf("%s\n", toBePrinted);
    free(toBePrinted);
}//end func

void string_freeStringArray(char** array, int arraySize){
    for(int x = 0; x < arraySize; x++) {
        free(array[x]);
    }//end if
    free(array);
}//end func

void string_advanceFree(void** toBeDeleted){
    if(toBeDeleted == NULL){
        return;
    }//end if
    char* delete = (char*)*toBeDeleted;
    free(delete);
    *toBeDeleted = NULL;
}//end func


void string_free(void* toBeDeleted){
    if(toBeDeleted == NULL){
        return;
    }//end func
    free(toBeDeleted);
}//end func

/**********************************************************
 * other functions
 **********************************************************/

char** string_readFileByChar$(char* fileName, int* arraySize){
    //dec vars
    FILE* filePointer = fopen(fileName, "r");
    char** stringArray = calloc(1, sizeof(stringArray));
    char* stringBuffer = calloc(1, sizeof(stringBuffer));
    int charBuffer;
    int stringSize = 0;
    int lineSize = 0;

    //read the entire file to the string
    while(true){
        charBuffer = getc(filePointer);
        if(charBuffer == EOF){
            break;
        }//end if
        stringBuffer[stringSize] = (char)charBuffer;
        stringSize++;
        stringBuffer = realloc(stringBuffer, sizeof(stringBuffer)*(stringSize+1));
        stringBuffer[stringSize] = '\0';
    }//end if*/
    
    //remove the \r\n by tokenizing and adding to array
    char* token = strtok(stringBuffer, "\r\n");
    while(token != NULL){
        stringArray[lineSize] = string_setString(token);
        strcpy(stringArray[lineSize], token);
        lineSize++;
        stringArray = realloc(stringArray, sizeof(stringArray)*(lineSize+1));
        token = strtok(NULL, "\r\n");
    }//end while

    //set the size and return
    *arraySize = lineSize;
    free(stringBuffer);
    fclose(filePointer);
    return stringArray;
}//end func

/**********************************************************
 * dummy function for constructors
 **********************************************************/

void free_function(void* toBeDeleted){
    if(toBeDeleted == NULL){
        return;
    }//end if
    free(toBeDeleted);
}//end func

char* dummy_print(void* toBePrinted){
    char* newString = calloc(sizeof(char), 2);
    strcpy(newString, "\0");
    return newString;
}//end func

void dummy_delete(void* toBeDeleted){
    return;
}//end func

int dummy_compare(const void* first, const void* second){
    return 0;
}//end func

#undef free
void dummy_safeFree(void** toBeFreed){
    if(*toBeFreed == NULL){
        return;
    }//end func
    void* delete = *toBeFreed;
    free(delete);
    *toBeFreed = NULL;
}//end func