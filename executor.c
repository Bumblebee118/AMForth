#include "global.h"
#include "compiler.h"
#include "executor.h"

int execute(char* word) {
    if (isCompileMode) {
        compile(word);
    } else {
        //if the word exists in the dictionary, execute the definition
        if ((wp = getEntry(word))) {
            wp->basicfunc();
            return 0;
        //if entry could not be found check if it can be converted to a number
        } else {
            char *endptr;
            int num = (int) strtol(word, &endptr, 10);

            if (strlen(endptr) == 0) {
                push(parameterStack, num);
                return 0;
            } else {
                ERROR("Undefined word");
                return -1;
            }
        }
    }
    return 0;
}

