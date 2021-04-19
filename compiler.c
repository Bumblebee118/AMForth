//
// Created by Stefan Walser on 07.04.21.
//

#include "global.h"

/*int compile(char *word) {
    static char name[MAX_WORD_NAME_SIZE] = "";
    static Dict **definitions;
    static int numberOfWords = 0;
    if (strcmp(name, "") == 0) { // the first word is the name of the new function
        strcpy(name, word);
    } else { // the following words are the names of the contained functions
        if (definitions == NULL) {
            definitions = (Dict **) malloc(sizeof(Dict *));
        } else if (definitions[numberOfWords] == NULL) {
            definitions = realloc(definitions, sizeof(definitions) + sizeof(Dict *));
        }
        Dict *dictEntry = getEntry(word);
        if (dictEntry == NULL) {
            return -1;
        }
        definitions[numberOfWords] = dictEntry;
        if (strcmp(dictEntry->word, ";") == 0) {
            Dict *entries[numberOfWords];
            for (int i = 0; i < (numberOfWords + 1); i++) {
                entries[i] = definitions[i];
            }
            addEntry(name, 0, NULL, entries, NULL);
            definitions = NULL;
            strcpy(name, "");
            numberOfWords = 0;
            return 0;
        }
        numberOfWords++;
    }
    return 0;
}*/

void compile(char* word){
    Dict* entry;
    if ((entry = getEntry(word))) {
        *user_code = entry;
        user_code++;
        return;
    }

    defs = &macros;
    if((entry = getEntry(word))){
        defs = &dict;
        entry->basicfunc();
        return;
    }

    defs = &dict;
    char *endptr;
    int num = (int) strtol(word, &endptr, 10);

    if (strlen(endptr) == 0) {
        push(parameterStack, num);
    } else {
        ERROR("Undefined word");
    }
}