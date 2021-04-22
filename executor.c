#include "global.h"

void execute(char* word) {
    if (isCompileMode) {
        compile(word);
    } else {
        //if the word exists in the dictionary, execute the definition
        if ((wp = getEntry(word))) {
            wp->basicfunc();
        //if entry could not be found check if it can be converted to a number
        } else {
            char *endptr;
            cell_t num = (cell_t) strtol(word, &endptr, 10);

            if (strlen(endptr) == 0) {
                push(parameterStack, num);
            } else {
                ERROR("Undefined word", word);
            }
        }
    }
}

