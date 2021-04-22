//
// Created by Stefan Walser on 29.03.21.
//

#include "global.h"

Dict *addEntry(char *word, cell_t value, Dict *code[], BASICFUNC basicfunc) {
    //check if entry already exists and if it is mutable or not
    Dict *oldEntry = getEntry(word);
    if (oldEntry != NULL && oldEntry->basicfunc != NULL) {
        return NULL;
    }

    Dict *newEntry = (Dict *) malloc(sizeof(Dict));
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
    newEntry->definitions = code;
    newEntry->basicfunc = basicfunc;

    newEntry->link = *defs;     // link to previous element
    *defs = newEntry;           // update Dict entry

    return newEntry;
}


Dict *getEntry(const char *word) {
    Dict *currentNode = *defs;
    while (currentNode != NULL) {
        if (strcmp(currentNode->word, word) == 0) {
            return currentNode;
        }
        currentNode = currentNode->link;
    }
    return NULL;
}


int removeEntry(char *word) {
    Dict *currentNode = *defs;
    Dict *nextNode = NULL;

    while (currentNode != NULL) {
        if (strcmp(currentNode->word, word) == 0) {

            if (nextNode == NULL) {
                *defs = currentNode->link;  //if nextnode == NULL then currentnode is the here node in the Dict
            } else {
                nextNode->link = currentNode->link;     //get rid of currentnode
            }

            free(currentNode->word);
            free(currentNode);

            return 0;
        }

        nextNode = currentNode;
        currentNode = nextNode->link;
    }

    return -1;
}

void deleteDict() {
    Dict *currentNode = *defs;
    Dict *next;
    while (currentNode != NULL) {
        if (currentNode->word != NULL) free(currentNode->word);
        next = currentNode->link;
        free(currentNode);
        currentNode = next;
    }

}

void addBasicWordsToDict() {
    //TODO add definitions pointer
    addEntry("+", 0, NULL, &ADD);
    addEntry("-", 0, NULL, &SUBTRACT);
    addEntry("*", 0, NULL, &MULTIPLY);
    addEntry("/", 0, NULL, &DIVIDE);
    addEntry(".", 0, NULL, &PRINTPOPSTACK);
    addEntry(".s", 0, NULL, &PRINTSTACK);
    addEntry(":", 0, NULL, &COLON);
    addEntry("docol", 0, NULL, &DOCOLON);
    addEntry("dosemi", 0, NULL, &DOSEMI);
    addEntry("dolit", 0, NULL, &DOLIT);
    addEntry("interpret", 0, NULL, &INTERPRET);
    addEntry("execute", 0, NULL, &EXECUTE);
    addEntry("branch0", 0, NULL, &BRANCH0);
    addEntry("words", 0, NULL, &LISTWORDS);
    addEntry("s\"", 0, NULL, &STARTSTORESTRING);
    addEntry(".\"", 0, NULL, &STARTPRINTSTRING);
    addEntry("\"", 0, NULL, &ENDSTRING);
    addEntry("type", 0, NULL, &TYPE);
    addEntry("constant", 0, NULL, &CONST);
    addEntry("variable", 0, NULL, &VAR);
    addEntry("!", 0, NULL, &ASSIGNVAR);
    addEntry("@", 0, NULL, &FETCHVAR);

    defs = &macros;
    addEntry(";", 0, NULL, &SEMI);
    defs = &dict;
}

