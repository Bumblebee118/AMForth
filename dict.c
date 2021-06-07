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

Dict *addVariable(char* name){
    Data d;
    void* ptr = malloc(sizeof(cell_t));
    add(&ptrList, ptr);
    d.value = (cell_t) ptr;
    return addEntry(name, d, &DOVAR);
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
        //if (currentNode->code == &DOVAR) free((int*) currentNode->data.value);
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

    dict_begin = addEntry("throw", data, &THROW);
    //######## Arithmetic ##########
    add_wp = addEntry("+", data, &ADD);
    addEntry("-", data, &SUBTRACT);
    addEntry("*", data, &MULTIPLY);
    addEntry("/", data, &DIVIDE);
    //######## Conditional ##########
    addEntry("<", data, &LESS);
    gt_wp = addEntry(">", data, &GREATER);
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
    branch_wp = addEntry("branch", data, &BRANCH);
    checkbranch_wp = addEntry("?branch", data, &CHECKBRANCH);
    //######## Stack ##########
    addEntry("swap", data, &SWAP);
    addEntry("dup", data, &DUP);
    addEntry(".", data, &PRINTPOPSTACK);
    addEntry(".s", data, &PRINTSTACK);
    //######## Compile ##########
    addEntry(":", data, &COLON);
    addEntry("docol", data, &DOCOLON);
    dosemi_wp = addEntry("dosemi", data, &DOSEMI);
    dolit_wp = addEntry("dolit", data, &DOLIT);
    dostorestring_wp = addEntry("dostorestring", data, &DOSTORESTRING);
    doprintstring_wp = addEntry("doprintstring", data, &DOPRINTSTRING);
    addEntry("'", data, &INTERPRET);
    addEntry("execute", data, &EXECUTE);
    addEntry("compile", data, &COMPILE);
    addEntry("branch0", data, &BRANCH0);
    addEntry("words", data, &LISTWORDS);
    addEntry("s\"", data, &STORESTRING);
    addEntry(".\"", data, &PRINTSTRING);
    addEntry("type", data, &TYPE);
    //######## Constant or Variable ##########
    addEntry("constant", data, &CONST);
    addEntry("variable", data, &VAR);
    addEntry("dovar", data, &DOVAR);

    assignvar_wp = addEntry("!", data, &ASSIGNVAR);
    fetchvar_wp = addEntry("@", data, &FETCHVAR);
    addEntry("cr", data, &CR);
    addEntry("forget", data, &FORGET);
    addEntry("emit", data, &EMIT);
    addEntry("pick", data, &PICK);
    addEntry("drop", data, &DROP);
    addEntry("over", data, &OVER);
    addEntry("rot", data, &ROT);

    pushonreturn_wp = addEntry("pushonreturn", data, &PUSHONRETURN);
    peekfromreturn_wp = addEntry("peekfromreturn", data, &PEEKFROMRETURN);
    popfromreturn_wp = addEntry("popfromreturn", data, &POPFROMRETURN);

    //######## Macros ##########
    defs = &macros;
    macros_begin = addEntry(";", data, &SEMI);
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
    i_wp = addVariable("i");
    j_wp = addVariable("j");
    k_wp = addVariable("k");

    Data d;
    d.value = (cell_t) &isCompileMode;
    addEntry("compilemode", d, &DOVAR);
    d.value = (cell_t) dict;
    addEntry("here", d, &DOVAR);
}

