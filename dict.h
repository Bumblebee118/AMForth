//
// Created by Stefan Walser on 29.03.21.
//

#ifndef AMFORTH_DICT_H
#define AMFORTH_DICT_H

#include <string.h>
#include "stack.h"
#include "basic.h"


struct Dict;

typedef union Data{
    cell_t value;
    struct Dict** definition;
} Data;

/**
 *
 */
typedef struct Dict {
    char *word;             //name of the word
    struct Dict *link;      //link reference to previous dictionary entry
    Data data;              //data field of dictionary entry
    CODEPOINTER code;       //pointer to a code that shall be executed
} Dict;

/**
 * Adds an entry to the list.
 * @param dict The dictionary, the element should be added to
 * @param word the name of the new function
 * @param functionAddress the address of the first function to be called in this function
 * @return NULL on failure, otherwise the new entry
 */
Dict* addEntry(char *word, Data data, CODEPOINTER code);

/**
 * add a new variable to the dictionary
 * @param name
 * @return
 */
Dict *addLoopVariable(char* name);

/**
 * searches the dictionary for the function name given as a parameter
 * @param dict the dictionary to search through
 * @param word the name of the function to search for
 * @return a pointer to the element or NULL if no element was found with the given name
 */
Dict *getEntry(char *word);

/**
 * deletes an entry from the dictionary
 * @param dict the dictionary to delete the item from
 * @param word the name of the function to delete
 * @return 0 for success, -1 for failure (the function wasn't found in the dictionary)
 */
int removeEntry(char *word);

/**
 * deletes the dictionary
 */
void deleteDict();

/**
 * adds all basic words from basicFunctions.h to the specified Dict
 * @param dict
 */
void addBasicWordsToDict();

/**
 * convert the input string to all lowercase letters
 */
void toLowerCase(char** word);

#endif //AMFORTH_DICT_H
