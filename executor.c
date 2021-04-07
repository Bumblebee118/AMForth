#include <stdlib.h>
#include <string.h>
#include "executor.h"
#include "error.h"

int execute(char* word, Dict *dict, Stack *parameterStack, Stack *returnStack) {
    DictEntry *entry = getEntry(dict, word);

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
                if (execute(nextSubEntry->word, dict, parameterStack, returnStack) < 0) {
                    return -1;
                }
                index++;
                nextSubEntry = entry->definitions[index];
            }
        } else if (entry->basicfunc != NULL && entry->definitions == NULL) {
            return entry->basicfunc(parameterStack);
        }
    }
}

