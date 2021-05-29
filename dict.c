//
// Created by Stefan Walser on 29.03.21.
//

#include "global.h"

Dict *addEntry(char *word, Data data, CODEPOINTER code) {
    toLowerCase(&word);
    //check if entry already exists and write redefined
    Dict *oldEntry = getEntry(word);
    if (oldEntry != NULL && oldEntry->code != NULL) {
        redefined = 1;
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
    newEntry->data = data;
    newEntry->code = code;

    newEntry->link = *defs;     // link to previous element
    *defs = newEntry;           // update Dict entry

    return newEntry;
}


Dict *getEntry(char *word) {
    toLowerCase(&word);
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
    toLowerCase(&word);
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
        if (currentNode->code == &DOVAR) free((int*) currentNode->data.value);
        next = currentNode->link;
        free(currentNode);
        currentNode = next;
    }
}

void toLowerCase(char** word){
    size_t len = strlen(*word);
    char currentChar;
    int offset = 'a'-'A';
    for(int i  = 0; i< len; i++){
        currentChar = (*word)[i];
        if((currentChar >= 'A') && (currentChar<='Z')){
            currentChar = currentChar+offset;
            (*word)[i] = currentChar;
        }
    }
}

void addBasicWordsToDict() {
    Data data;
    data.value = 0;

    addEntry("throw", data, &THROW);
    //######## Arithmetic ##########
    addEntry("+", data, &ADD);
    addEntry("-", data, &SUBTRACT);
    addEntry("*", data, &MULTIPLY);
    addEntry("/", data, &DIVIDE);
    //######## Conditional ##########
    addEntry("<", data, &LESS);
    addEntry(">", data, &GREATER);
    addEntry("=", data, &EQUAL);
    addEntry("<>", data, &NOTEQUAL);
    addEntry("<=", data, &LESSEQ);
    addEntry(">=", data, &GREATEREQ);
    addEntry("0<", data, &ZEROLESS);
    addEntry("0>", data, &ZEROGREATER);
    addEntry("0=", data, &ZEROEQ);
    addEntry("0<>", data, &ZERONOTEQ);
    addEntry("0<=", data, &ZEROLESSEQ);
    addEntry("0>=", data, &ZEROGREATEREQ);
    //#########  Logical Operators #############
    addEntry("and", data, &AND);
    addEntry("or", data, &OR);
    addEntry("xor", data, &XOR);
    //#########  Flow Control #############
    addEntry("branch", data, &BRANCH);
    addEntry("?branch", data, &CHECKBRANCH);
    //######## Stack ##########
    addEntry("swap", data, &SWAP);
    addEntry("dup", data, &DUP);
    addEntry(".", data, &PRINTPOPSTACK);
    addEntry(".s", data, &PRINTSTACK);
    //######## Compile ##########
    addEntry(":", data, &COLON);
    addEntry("docol", data, &DOCOLON);
    addEntry("dosemi", data, &DOSEMI);
    addEntry("dolit", data, &DOLIT);
    addEntry("dostorestring", data, &DOSTORESTRING);
    addEntry("doprintstring", data, &DOPRINTSTRING);
    addEntry("'", data, &INTERPRET);
    addEntry("execute", data, &EXECUTE);
    addEntry("branch0", data, &BRANCH0);
    addEntry("words", data, &LISTWORDS);
    addEntry("s\"", data, &STORESTRING);
    addEntry(".\"", data, &PRINTSTRING);
    addEntry("type", data, &TYPE);
    //######## Constant or Variable ##########
    addEntry("constant", data, &CONST);
    addEntry("variable", data, &VAR);
    addEntry("!", data, &ASSIGNVAR);
    addEntry("@", data, &FETCHVAR);
    addEntry("cr", data, &CR);
    addEntry("forget", data, &FORGET);
    addEntry("emit", data, &EMIT);
    addEntry("pick", data, &PICK);

    addEntry("pushonreturn", data, &PUSHONRETURN);
    addEntry("peekfromreturn", data, &PEEKFROMRETURN);
    addEntry("popfromreturn", data, &POPFROMRETURN);

    //######## Macros ##########
    defs = &macros;
    addEntry(";", data, &SEMI);
    addEntry("s\"", data, &STORESTRING);
    addEntry(".\"", data, &PRINTSTRING);
    //#########  Flow Control #############;
    addEntry("if", data, &IF);
    addEntry("then", data, &THEN);
    addEntry("else", data, &ELSE);
    addEntry("do", data, &DO);
    addEntry("loop", data, &LOOP);
    addEntry("begin", data, &BEGIN);
    addEntry("until", data, &UNTIL);
    addEntry("again", data, &AGAIN);
    addEntry("while", data, &WHILE);
    addEntry("repeat", data, &REPEAT);
    defs = &dict;

    //######## Global Variables ##########
    Data d;
    d.value = (cell_t) malloc(sizeof(cell_t)); // this simply has to work :P
    addEntry("i", d, &DOVAR);
    d.value = (cell_t) malloc(sizeof(cell_t)); // this simply has to work :P
    addEntry("j", d, &DOVAR);
    d.value = (cell_t) malloc(sizeof(cell_t)); // this simply has to work :P
    addEntry("k", d, &DOVAR);
}

