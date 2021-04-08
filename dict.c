//
// Created by Stefan Walser on 29.03.21.
//

#include "global.h"

void createDict() {
    dict = (Dict *) malloc(sizeof(Dict));
    dict->firstElement = NULL;
    dict->lastElement = NULL;
}


int addEntry(char *word, int value, FUNCDEF codepointer, DictEntry **definitions, BASICFUNC basicfunc) {
    //check if entry already exists and if it is mutable or not
    DictEntry *oldEntry = getEntry(word);
    if (oldEntry != NULL && oldEntry->basicfunc != NULL) {
        return -2;
    }

    DictEntry *newEntry = (DictEntry *) malloc(sizeof(DictEntry));
    if (newEntry == NULL) {
        return -1;
    }
    memset(newEntry, 0, sizeof(DictEntry));
    newEntry->word = strdup(word);
    if ((newEntry->word) == NULL) {
        free(newEntry);
        return -1;
    }

//    if (strcmp(word, "addsub") == 0) {
//        for (int i = 0; i < 10; ++i) {
//            if (definitions[i] != NULL) printf("%s added\n", definitions[i]->word); fflush(stdout);
//        }
//    }
    strncpy(newEntry->word, word, strlen(word) + 1);
    newEntry->value = value;
    newEntry->codePointer = codepointer;
    if (definitions != NULL) {
        newEntry->definitions = *definitions;
    }
    newEntry->basicfunc = basicfunc;

    newEntry->link = dict->lastElement;     // link to previous element
    dict->lastElement = newEntry;           // update dict entry

    if (dict->firstElement == NULL) {
        dict->firstElement = newEntry;
    }

    return 0;
}


DictEntry *getEntry(const char *word) {
    DictEntry *currentNode = dict->lastElement;
    while (currentNode != NULL) {
        if (strcmp(currentNode->word, word) == 0) {
            return currentNode;
        }
        currentNode = currentNode->link;
    }
    return NULL;
}

int removeEntry(char *word) {
    DictEntry *currentNode = dict->lastElement;
    DictEntry *nextNode = NULL;

    while (currentNode != NULL) {
        if (strcmp(currentNode->word, word) == 0) {

            if (nextNode == NULL) {
                dict->lastElement = currentNode->link;  //if nextnode == NULL then currentnode is the last node in the dict
            } else {
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

void deleteDict() {
    if (dict != NULL) {
        DictEntry *currentNode = dict->lastElement;
        DictEntry *next;
        while (currentNode != NULL) {
            if (currentNode->word != NULL) free(currentNode->word);
            if (currentNode->definitions != NULL) free(currentNode->definitions);
            next = currentNode->link;
            free(currentNode);
            currentNode = next;
        }
        free(dict);
    }
}

