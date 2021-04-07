//
// Created by Stefan Walser on 07.04.21.
//

#include "global.h"

int compiler(char *word) {
    static char *name;
    static DictEntry **definitions;
    static int numberOfWords = 0;

    if (name == NULL) { // the first word is the name of the new function
        name = (char *) malloc(sizeof(word));
        strcpy(name, word);
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
        numberOfWords++;
        if (strcmp(word, ";") == 0) {
            addEntry(name, 0, NULL, definitions, NULL);
            free(name);
            free(definitions);
            numberOfWords = 0;
        }
    }
    return 0;
}