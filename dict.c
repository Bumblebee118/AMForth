//
// Created by Stefan Walser on 29.03.21.
//

#include "global.h"

int addEntry(char *word, int value, CODEPOINTER codepointer, Dict *code[], BASICFUNC basicfunc) {
    //check if entry already exists and if it is mutable or not
    Dict * oldEntry = getEntry(word);
    if (oldEntry != NULL && oldEntry->basicfunc != NULL) {
        return -2;
    }

    Dict * newEntry = (Dict *) malloc(sizeof(Dict));
    if (newEntry == NULL) {
        return -1;
    }
    memset(newEntry, 0, sizeof(Dict));

    newEntry->word = strdup(word);
    if ((newEntry->word) == NULL) {
        free(newEntry);
        return -1;
    }
    newEntry->value = value;
    newEntry->codePointer = codepointer;
    newEntry->definitions = code;
    /*if (def != NULL) {
        int size = 0;
        int index = 0;
        Dict *entry = def[0];
        while (entry != NULL) {
            size++;
            index++;
            entry = def[index];
        }
        newEntry->def = (Dict **) malloc(size * sizeof(Dict *));
        for (int i = 0; i < size; ++i) {
            newEntry->def[i] = def[i];
        }
    }*/
    newEntry->basicfunc = basicfunc;

    newEntry->link = *defs;     // link to previous element
    *defs = newEntry;           // update Dict entry

    return 0;
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
    Dict * currentNode = *defs;
    Dict * next;
    while (currentNode != NULL) {
        if (currentNode->word != NULL) free(currentNode->word);
        if (currentNode->definitions != NULL) free(currentNode->definitions);
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
    addEntry("interpret", 0, NULL, NULL, &INTERPRET);
    addEntry("execute", 0, NULL, NULL, &EXECUTE);
    addEntry("branch0", 0, NULL, NULL, &BRANCH0);

    defs = &macros;
    addEntry(";", 0, NULL, NULL, &SEMI);
    defs = &dict;


}

