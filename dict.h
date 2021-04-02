//
// Created by Stefan Walser on 29.03.21.
//

#ifndef AMFORTH_DICT_H
#define AMFORTH_DICT_H

#include "stack.h"
#include "basicFunctions.h"

typedef struct DictEntry {
    struct DictEntry *link; //link reference to previous DictEntry
    char *word;
    int mutable; // 0 for basic words that can't be redefined
    struct DictEntry* definitions;
    BASICFUNC basicfunc;
    int value; // value of constant or value of variable
    // BASICFUNC codePointer(dictEntry) // TODO: new function pointer definition
} DictEntry;

typedef struct ReturnDef {
    int index;
    DictEntry *dictEntry;
} ReturnDef;

typedef struct Dict {
    struct DictEntry *firstElement;
    struct DictEntry *lastElement;
} Dict;


typedef struct FunctionPool {
    BASICFUNC *wordArray;
    int capacity;
    int freeIndex;
} FunctionPool;

/**
 * Creates a new Dictionary. Implemented as a linked list
 * @return a pointer to the dictionary
 */
Dict *createDict();

/**
 * creates a function pool, which is an array of functions
 * @param capacity the number of elements in the array
 * @return a pointer to the function pool
 */
FunctionPool *createFunctionPool(int capacity);

/**
 * Adds an entry to the list.
 * @param dict The dictionary, the element should be added to
 * @param word the name of the new function
 * @param functionAddress the address of the first function to be called in this function
 * @return -1 for failure, 0 for success, -2 when trying to redefine an immutable function
 */
int addEntry(Dict *dict, char *word, int functionAddress);

/**
 * adds a function to the function pool
 * @param functionPool the function pool to add the method to
 * @param functionPtr a pointer to the function that should be added
 * @return 0 if the function was added, -1 if there was no space left
 */
int addWordToPool(Dict *dict, char *word, FunctionPool *functionPool, BASICFUNC functionPtr);

/**
 * returns the requested function from the pool
 * @param dict the dict to search the function in
 * @param functionPool the function pool to search the function in
 * @param word the word to search
 * @return the requested function
 */
BASICFUNC getWordFromPool(Dict *dict, FunctionPool *functionPool, char *word);

/**
 * searches the dictionary for the function name given as a parameter
 * @param dict the dictionary to search through
 * @param word the name of the function to search for
 * @return a pointer to the element or NULL if no element was found with the given name
 */
DictEntry *searchEntry(Dict *dict, const char *word);

/**
 * deletes an entry from the dictionary
 * @param dict the dictionary to delete the item from
 * @param word the name of the function to delete
 * @return 0 for success, -1 for failure (the function wasn't found in the dictionary)
 */
int removeEntry(Dict *dict, char *word);

/**
 * deletes the function pool
 * @param functionPool
 */
void deleteFunctionPool(FunctionPool* functionPool);

/**
 * deletes the dictionary
 * @param dict
 */
void deleteDict(Dict *dict);

#endif //AMFORTH_DICT_H
