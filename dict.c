//
// Created by Stefan Walser on 29.03.21.
//

#include "dict.h"
#include <stdlib.h>
#include <string.h>

Dict *createDict() {
    Dict *dict = (Dict *) malloc(sizeof(Dict));
    dict->firstElement = NULL;
    dict->lastElement = NULL;
    return dict;
}

FunctionPool *createFunctionPool(int capacity) {
    FunctionPool *functionPool = (FunctionPool *) malloc(sizeof(FunctionPool));
    functionPool->capacity = capacity;
    functionPool->freeIndex = 0;
    functionPool->wordArray = (BASICFUNC *) malloc(capacity * sizeof(BASICFUNC));
    return functionPool;
}

int addEntry(Dict *dict, char *word, int functionAddress) {
    DictEntry *dictEntry = searchEntry(dict, word);
    if (dictEntry != NULL && dictEntry->mutable == 0) {
        return -2;
    }
    DictEntry *entry = (DictEntry *) malloc(sizeof(DictEntry));
    if (entry == NULL) {
        return -1;
    }
    entry->word = (char *) malloc(sizeof(char) * (strlen(word)+1));
    if ((entry->word) == NULL) {
        free(entry);
        return -1;
    }

    strncpy(entry->word, word, strlen(word)+1);
    entry->functionAddress = functionAddress;
    entry->link = dict->lastElement;    // link to previous element
    entry->mutable = 1; // TODO: if the basic dictionary is filled at startup with this method, this assignment has to be adapted

    dict->lastElement = entry;  // update dict entry

    if (dict->firstElement == NULL) {
        dict->firstElement = entry;
    }

    return 0;
}

int addWordToPool(Dict *dict, char *word, FunctionPool *functionPool, BASICFUNC functionPtr) {
    if (functionPool->freeIndex < functionPool->capacity) {
        functionPool->wordArray[functionPool->freeIndex] = functionPtr;
        addEntry(dict, word, functionPool->freeIndex);
        functionPool->freeIndex++;
        return 0;
    } else {
        return -1;
    }

}

BASICFUNC getWordFromPool(Dict *dict, FunctionPool *functionPool, char *word) {
    DictEntry *dictEntry = searchEntry(dict, word);
    if (dictEntry != NULL) {
        return functionPool->wordArray[dictEntry->functionAddress];
    } else {
        return NULL;
    }
}

DictEntry *searchEntry(Dict *dict, const char *word) {
    DictEntry *currentNode = dict->lastElement;
    while (currentNode != NULL) {
        if (strcmp(currentNode->word, word) == 0) {
            return currentNode;
        }
        currentNode = currentNode->link;
    }
    return NULL;
}

int removeEntry(Dict *dict, char *word) {
    DictEntry *currentNode = dict->lastElement;

    if (currentNode != NULL) {
        if (strcmp(currentNode->word, word) == 0) {
            dict->lastElement = currentNode->link;
            free(currentNode->word);
            free(currentNode);
            return 0;
        } else {
            while (currentNode->link != NULL) {
                if (strcmp(currentNode->link->word, word) == 0) {
                    currentNode->link = currentNode->link->link;
                    free(currentNode->word);
                    free(currentNode);
                    return 0;
                }
                currentNode = currentNode->link;
            }
        }
    }
    return -1;
}

void deleteDict(Dict *dict) {
    if(dict != NULL){
        DictEntry* currentNode = dict->lastElement;
        while (currentNode != NULL){
            free(currentNode->word);
            currentNode = currentNode->link;
            free(currentNode);
        }
        free(dict);
    }
}

void deleteFunctionPool(FunctionPool* functionPool) {
    if(functionPool != NULL){
        free(functionPool->wordArray);
        free(functionPool);
    }

}
