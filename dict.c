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
    entry->before = NULL;
    if (entry->link != NULL) {
        entry->link->before = entry;
    }


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

void deleteEntry(Dict* dict, char* functionName) {
    DictEntry* elementToDelete = searchEntry(dict, functionName);
    if (elementToDelete->link != NULL) {
        elementToDelete->link->before = elementToDelete->before;
    } else {
        dict->firstElement = elementToDelete->before;
    }
    if (elementToDelete->before != NULL) {
        elementToDelete->before->link = elementToDelete->link;
    } else {
        dict->lastElement = elementToDelete->link;
    }
    free(elementToDelete);
}
