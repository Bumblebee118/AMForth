//
// Created by Stefan Walser on 07.04.21.
//

#include "global.h"

void compile(char *word) {
    Dict *entry;

    defs = &macros;
    if ((entry = getEntry(word))) {
        defs = &dict;
        entry->code();
        return;
    }

    defs = &dict;
    if ((entry = getEntry(word))) {
        *userCode = entry;
        userCode++;
        return;
    }

    defs = &dict;
    char *endptr;
    cell_t num = (cell_t) strtol(word, &endptr, 10);

    if (strlen(endptr) == 0) {
        compile("dolit");
        *(userCode++) = (Dict *) num;
    } else {
        push(parameterStack, ERR_UNDEFINED_WORD);
        THROW();
        //stopCompile();
    }
}

void stopCompile(){
    redefined = 0;
    isCompileMode = 0;
    userCode = cw->data.definition;    //reset userCode pointer
    removeEntry(cw->word);             //delete word from dictionary
}