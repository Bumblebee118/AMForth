//
// Created by Stefan Walser on 29.03.21.
//

#include "dict.h"
#include <stdlib.h>
#include <string.h>

Dict* createDict() {
    Dict* dict = (Dict*) malloc(sizeof(Dict));
    dict->firstElement = NULL;
    dict->lastElement = NULL;
    return dict;
}

int addEntry(Dict* dict, char* functionName, int functionAddress) {
    DictEntry* dictEntry = searchEntry(dict, functionName);
    if (dictEntry != NULL && dictEntry->mutable == 0) {
        return -2;
    }
    DictEntry* entry = (DictEntry*) malloc(sizeof(DictEntry));
    if (entry == NULL) {
        return -1;
    }
    entry->functionName = (char*) malloc(sizeof(char) * strlen(functionName));
    if((entry->functionName) == NULL){
        return -1;
    }

    strncpy(entry->functionName, functionName, strlen(functionName));
    entry->functionAddress = functionAddress;
    entry->link = dict->lastElement;    // link to previous element
    entry->mutable = 1; // TODO: if the basic dictionary is filled at startup with this method, this assignment has to be adapted

    dict->lastElement = entry;  // update dict entry

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

int deleteEntry(Dict* dict, char* functionName) {
    DictEntry* currentNode = dict->lastElement;
    if (currentNode != NULL) {
        if (strcmp(currentNode->functionName, functionName) == 0) {
            dict->lastElement = currentNode->link;
            free(currentNode);
            return 0;
        } else {
            while (currentNode->link != NULL) {
                if (strcmp(currentNode->link->functionName, functionName) == 0) {
                    currentNode->link = currentNode->link->link;
                    free(currentNode);
                    return 0;
                }
                currentNode = currentNode->link;
            }
        }
    }
    return -1;
}
