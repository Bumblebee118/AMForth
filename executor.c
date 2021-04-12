#include "global.h"
#include "compiler.h"
#include "executor.h"

DictEntry *wordPointer = NULL;
DictEntry *instrPointer = NULL;
DictEntry *progPointer = NULL;

int execute(char* word) {
    DictEntry *entry = getEntry(word);
    if (inCompileMode == 1) {
        compiler(word);
        if (strcmp(word, ";") == 0) inCompileMode = 0;
    } else {
        //if entry could not be found check if it can be converted to a number
        if (entry == NULL) {
            char *endptr;
            int num = (int) strtol(word, &endptr, 10);

            if (strlen(endptr) == 0) {
                push(parameterStack, num);
            } else {
                PRINT_ERROR_MSG("Undefined word");
                return -1;
            }

        //if the word exists in the dictionary, execute the definition
        } else {
            //TODO: Execute function definition here
            if (entry->basicfunc == NULL && entry->definitions != NULL) {
                int index = 0;
                DictEntry *nextSubEntry = entry->definitions[index];
                while (strcmp(nextSubEntry->word, ";") != 0) {
                    if (execute(nextSubEntry->word) < 0) {
                        return -1;
                    }
                    index++;
                    nextSubEntry = entry->definitions[index];
                }
            } else if (entry->basicfunc != NULL && entry->definitions == NULL) {
                return entry->basicfunc();
            }
        }
    }
    return 0;
}

