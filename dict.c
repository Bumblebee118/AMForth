//
// Created by Stefan Walser on 29.03.21.
//

#include "dict.h"
#include <stdlib.h>
#include <stdio.h>
#include <mem.h>

Dict* createDict() {
    Dict* dict = (Dict*) malloc(sizeof(Dict));
    dict->firstElement = NULL;
    dict->lastElement = NULL;
    return dict;
}

int addEntry(Dict* dict, char* functionName, int functionAddress) {
    DictEntry* entry = (DictEntry*) malloc(sizeof(DictEntry));
    if (entry == NULL) {
        return -1;
    }
    entry->functionName = (char*) malloc(sizeof(char)*strlen(functionName));
    if((entry->functionName) == NULL){
        return -1;
    }

    strncpy(entry->functionName, functionName, strlen(functionName));
    entry->functionAddress = functionAddress;
    entry->link = dict->lastElement;    //link to previous element

    dict->lastElement = entry;  //update dict entry

    if (dict->firstElement == NULL) {
        dict->firstElement = entry;
    }

    return 0;
}

DictEntry* searchEntry(Dict* dict, const char* functionName) {
    DictEntry* currentNode = dict->lastElement;
    while (currentNode != NULL) {
        if (strcmp(currentNode->functionName, functionName) == 0) {
            return currentNode;
        }
        currentNode = currentNode->link;
    }
    return NULL;
}
