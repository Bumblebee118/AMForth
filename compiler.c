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
        *user_code = entry;
        user_code++;
        return;
    }

    defs = &dict;
    char *endptr;
    cell_t num = (cell_t) strtol(word, &endptr, 10);

    if (strlen(endptr) == 0) {
        compile("dolit");
        *user_code = (Dict *) num;
        user_code++;
    } else {
        push(parameterStack, ERR_UNDEFINED_WORD);
        THROW();
        isCompileMode = 0;
        user_code = cw->data.definition;    //reset user_code pointer
        removeEntry(cw->word);              //delete word from dictionary
    }
}