//
// Created by Stefan Walser on 29.03.21.
//

#ifndef AMFORTH_DICT_H
#define AMFORTH_DICT_H

#include <string.h>
#include "stack.h"
#include "basicFunctions.h"

/**
 *
 */
typedef struct Dict {
    char *word;                     //name of the definition
    struct dict_t *link;              //link reference to previous Dict
    int value;                      // value of constant or address of variable
    CODEPOINTER codePointer;        // TODO: new function pointer definition codepointer(Dict-Entry)
    struct dict_t **definitions;      //array of other function def, which build up this function definition
    BASICFUNC basicfunc;            //pointer to a basic function, if no basic function, then this pointer is NULL
} Dict;

/**
 * Adds an entry to the list.
 * @param dict The dictionary, the element should be added to
 * @param word the name of the new function
 * @param functionAddress the address of the first function to be called in this function
 * @return NULL on failure, otherwise the new entry
 */
Dict* addEntry(char *word, int value, CODEPOINTER codepointer, Dict **definitions, BASICFUNC basicfunc);

/**
 * searches the dictionary for the function name given as a parameter
 * @param dict the dictionary to search through
 * @param word the name of the function to search for
 * @return a pointer to the element or NULL if no element was found with the given name
 */
Dict *getEntry(const char *word);

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

#endif //AMFORTH_DICT_H
