//
// Created by Stefan Walser on 07.04.21.
//

#include "global.h"

int compiler(char *word) {
    static char name[MAX_WORD_NAME_SIZE] = "";
    static DictEntry **definitions;
    static int numberOfWords = 0;
    if (strcmp(name, "") == 0) { // the first word is the name of the new function
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
        if (strcmp(dictEntry->word, ";") == 0) {
            DictEntry *entries[numberOfWords];
            for (int i = 0; i < (numberOfWords + 1); i++) {
                entries[i] = definitions[i];
            }
            addEntry(name, 0, NULL, entries, NULL);
            free(definitions);
            strcpy(name, "");
            numberOfWords = 0;
            return 0;
        }
        numberOfWords++;
    }
    return 0;
}