//
// Created by Stefan Walser on 29.03.21.
//

#include "global.h"

Dict* addEntry(char *word, int value, CODEPOINTER codepointer, Dict *code[], BASICFUNC basicfunc) {
    //check if entry already exists and if it is mutable or not
    Dict * oldEntry = getEntry(word);
    if (oldEntry != NULL && oldEntry->basicfunc != NULL) {
        return NULL;
    }

    Dict * newEntry = (Dict *) malloc(sizeof(Dict));
    if (newEntry == NULL) {
        return NULL;
    }
    memset(newEntry, 0, sizeof(Dict));

    newEntry->word = strdup(word);
    if ((newEntry->word) == NULL) {
        free(newEntry);
        return NULL;
    }
    newEntry->value = value;
    newEntry->codePointer = codepointer;
    newEntry->definitions = code;
    newEntry->basicfunc = basicfunc;

    newEntry->link = *defs;     // link to previous element
    *defs = newEntry;           // update Dict entry

    return newEntry;
}


Dict *getEntry(const char *word) {
    Dict * currentNode = *defs;
    while (currentNode != NULL) {
        if (strcmp(currentNode->word, word) == 0) {
            return currentNode;
        }
        currentNode = currentNode->link;
    }
    return NULL;
}


int removeEntry(char *word) {
    Dict * currentNode = *defs;
    Dict * nextNode = NULL;

    while (currentNode != NULL) {
        if (strcmp(currentNode->word, word) == 0) {

            if (nextNode == NULL) {
                *defs = currentNode->link;  //if nextnode == NULL then currentnode is the here node in the Dict
            } else {
                nextNode->link = currentNode->link;     //get rid of currentnode
            }

            free(currentNode->word);
            //free(currentNode->definitions);
            free(currentNode);

            return 0;
        }

        nextNode = currentNode;
        currentNode = nextNode->link;
    }

    return -1;
}

void deleteDict() {
    Dict * currentNode = *defs;
    Dict * next;
    while (currentNode != NULL) {
        if (currentNode->word != NULL) free(currentNode->word);
        //if (currentNode->definitions != NULL) free(currentNode->definitions);
        next = currentNode->link;
        free(currentNode);
        currentNode = next;
    }

}

void addBasicWordsToDict(){
    //TODO add definitions pointer
    addEntry("+", 0, NULL, NULL, &ADD);
    addEntry("-", 0, NULL, NULL, &SUBTRACT);
    addEntry("*", 0, NULL, NULL, &MULTIPLY);
    addEntry("/", 0, NULL, NULL, &DIVIDE);
    addEntry(".", 0, NULL, NULL, &PRINTPOPSTACK);
    addEntry(".s", 0, NULL, NULL, &PRINTSTACK);
    addEntry(":", 0, NULL, NULL, &COLON);
    addEntry("docol", 0, NULL, NULL, &DOCOLON);
    addEntry("dosemi", 0, NULL, NULL, &DOSEMI);
    addEntry("dolit", 0, NULL, NULL, &DOLIT);
    addEntry("interpret", 0, NULL, NULL, &INTERPRET);
    addEntry("execute", 0, NULL, NULL, &EXECUTE);
    addEntry("branch0", 0, NULL, NULL, &BRANCH0);

    defs = &macros;
    addEntry(";", 0, NULL, NULL, &SEMI);
    defs = &dict;


}

