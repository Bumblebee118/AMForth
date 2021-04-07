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
        printf("%d", numberOfWords);
        if (strcmp(word, ";") == 0) {
            printf("%s added", definitions[2]->word); // TODO: the last entry in definitions is lost from here
            addEntry(name, 0, NULL, definitions, NULL);
            printf("%s added", definitions[2]->word); // TODO: to here
            free(name);
            free(definitions);
            numberOfWords = 0;
            return 0;
        }
        numberOfWords++;
    }
    return 0;
}