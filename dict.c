//
// Created by Stefan Walser on 29.03.21.
//

#include "dict.h"
#include <stdlib.h>

Dict* createDict() {
    Dict* dict = (Dict*) malloc(sizeof(Dict));
    return dict;
}

int addEntry(Dict* dict, char* functionName, int functionAddress) {
    DictEntry* entry = (struct DictEntry*) malloc(sizeof(DictEntry));
    if (entry == NULL) {
        return -1;
    }
    entry->functionName = functionName;
    entry->functionAddress = functionAddress;
    if (dict->firstElement == NULL) {
        dict->firstElement = entry;
        dict->lastElement = entry;
    } else {
        dict->lastElement->next = entry;
        dict->lastElement = entry;
    }
    return 0;
}

DictEntry* searchEntry(Dict* dict, const char* functionName) {
    DictEntry* currentNode = dict->firstElement;
    while (currentNode != NULL) {
        if (currentNode->functionName == functionName) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }
    return NULL;
}
