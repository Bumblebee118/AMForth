//
// Created by Stefan Walser on 07.04.21.
//

#include "global.h"

int compiler(char *word) {
    static char *name;
    static DictEntry **definitions;
    static int numberOfWords = 0;
    fflush(stdout);
    if (name == NULL) { // the first word is the name of the new function
        name = strdup(word);
    } else { // the following words are the names of the contained functions
        if (definitions == NULL) {
            definitions = (DictEntry **) malloc(sizeof(DictEntry *));
        } else if (definitions[numberOfWords] == NULL) {
            definitions = realloc(definitions, sizeof(definitions) + sizeof(DictEntry *));
        }
        DictEntry *dictEntry = getEntry(word);
        if (dictEntry == NULL) {
            return -1;
        }
        definitions[numberOfWords] = dictEntry;
        if (strcmp(word, ";") == 0) {
//            for (int i = 0; i < 10; ++i) {
//                if (definitions[i] != NULL) printf("%s added\n", definitions[i]->word); fflush(stdout);
//            }
            // TODO: the last entry in definitions is lost from here
            addEntry(name, 0, NULL, definitions, NULL);
            // TODO: to here
            fflush(stdout);
            free(name);
            free(definitions);
            numberOfWords = 0;
            return 0;
        }
        numberOfWords++;
    }
    return 0;
}