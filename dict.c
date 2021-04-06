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


int addEntry(Dict *dict, char *word, int value, FUNCDEF codepointer, DictEntry* definitions, BASICFUNC basicfunc) {
    //check if entry already exists and if it is mutable or not
    DictEntry *oldEntry = getEntry(dict, word);
    if (oldEntry != NULL && oldEntry->mutable == 0) {
        return -2;
    }

    DictEntry *newEntry = (DictEntry *) malloc(sizeof(DictEntry));
    if (newEntry == NULL) {
        return -1;
    }
    newEntry->word = (char *) malloc(sizeof(char) * (strlen(word)+1));
    if ((newEntry->word) == NULL) {
        free(newEntry);
        return -1;
    }

    strncpy(newEntry->word, word, strlen(word)+1);
    newEntry->value = value;
    newEntry->codePointer = codepointer;
    newEntry->definitions = definitions;
    newEntry->basicfunc = basicfunc;

    if(basicfunc == NULL) newEntry->mutable = 1;
    else newEntry->mutable = 0;

    newEntry->link = dict->lastElement;     // link to previous element
    dict->lastElement = newEntry;           // update dict entry

    if (dict->firstElement == NULL) {
        dict->firstElement = newEntry;
    }

    return 0;
}


DictEntry *getEntry(Dict *dict, const char *word) {
    DictEntry *currentNode = dict->lastElement;
    while (currentNode != NULL) {
        if (strcmp(currentNode->word, word) == 0) {
            return currentNode;
        }
        currentNode = currentNode->link;
    }
    return NULL;
}

/*int removeEntry(Dict *dict, char *word) {
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
}*/

int removeEntry(Dict *dict, char *word) {
    DictEntry *currentNode = dict->lastElement;
    DictEntry *nextNode = NULL;

    while (currentNode != NULL){
        if (strcmp(currentNode->word, word) == 0) {

            if(nextNode == NULL){
                dict->lastElement = currentNode->link;  //if nextnode == NULL then currentnode is the last node in the dict
            }else{
                nextNode->link = currentNode->link;     //get rid of currentnode
            }

            free(currentNode->word);
            free(currentNode->definitions);
            free(currentNode);

            return 0;
        }

        nextNode = currentNode;
        currentNode = nextNode->link;
    }

    return -1;
}

void deleteDict(Dict *dict) {
    if(dict != NULL){
        DictEntry* currentNode = dict->lastElement;
        DictEntry* next;
        while (currentNode != NULL){
            if(currentNode->word != NULL) free(currentNode->word);
            if(currentNode->definitions != NULL) free(currentNode->definitions);
            next = currentNode->link;
            free(currentNode);
            currentNode = next;
        }
        free(dict);
    }
}
