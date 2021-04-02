//
// Created by Stefan Walser on 29.03.21.
//

#ifndef AMFORTH_DICT_H
#define AMFORTH_DICT_H

#include "stack.h"
#include "basicFunctions.h"

/**
 *
 */
typedef struct Dict {
    struct DictEntry *firstElement;
    struct DictEntry *lastElement;
} Dict;

/**
 *
 */
typedef struct DictEntry {
    char *word;                     //name of the definition
    struct DictEntry *link;         //link reference to previous DictEntry
    int value;                      // value of constant or address of variable
    FUNCDEF codePointer;            // TODO: new function pointer definition codepointer(Dict-Entry)
    struct DictEntry* definitions;  //array of other function definitions, which build up this function definition
    BASICFUNC basicfunc;            //pointer to a basic function, if no basic function, then this pointer is NULL
    int mutable;                    // 0 for basic words that can't be redefined
} DictEntry;

/**
 *
 */
typedef struct ReturnDef {
    int index;
    DictEntry *dictEntry;
} ReturnDef;

/**
 * Creates a new Dictionary. Implemented as a linked list
 * @return a pointer to the dictionary
 */
Dict *createDict();

/**
 * Adds an entry to the list.
 * @param dict The dictionary, the element should be added to
 * @param word the name of the new function
 * @param functionAddress the address of the first function to be called in this function
 * @return -1 for failure, 0 for success, -2 when trying to redefine an immutable function
 */
int addEntry(Dict *dict, char *word, int value, FUNCDEF codepointer, DictEntry* definitions, BASICFUNC basicfunc);

/**
 * searches the dictionary for the function name given as a parameter
 * @param dict the dictionary to search through
 * @param word the name of the function to search for
 * @return a pointer to the element or NULL if no element was found with the given name
 */
DictEntry *getEntry(Dict *dict, const char *word);

/**
 * deletes an entry from the dictionary
 * @param dict the dictionary to delete the item from
 * @param word the name of the function to delete
 * @return 0 for success, -1 for failure (the function wasn't found in the dictionary)
 */
int removeEntry(Dict *dict, char *word);

/**
 * deletes the dictionary
 * @param dict
 */
void deleteDict(Dict *dict);

#endif //AMFORTH_DICT_H
