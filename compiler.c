//
// Created by Stefan Walser on 07.04.21.
//

#include "global.h"

void compile(char *word) {
    Dict *entry;
    if ((entry = getEntry(word))) {
        *user_code = entry;
        user_code++;
        return;
    }

    defs = &macros;
    if ((entry = getEntry(word))) {
        defs = &dict;
        entry->basicfunc();
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
        ERROR("Undefined word");
        isCompileMode = 0;
        user_code = cw->definitions;
        removeEntry(cw->word);
    }
}