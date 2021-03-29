//
// Created by Stefan Walser on 29.03.21.
//

#ifndef AMFORTH_DICT_H
#define AMFORTH_DICT_H
typedef struct DictEntry {
    struct DictEntry* next;
    char* functionName;
    int functionAddress;
} DictEntry;

typedef struct Dict {
    struct DictEntry* firstElement;
    struct DictEntry* lastElement;
} Dict;

/**
 * Creates a new Dictionary. Implemented as a linked list
 * @return a pointer to the dictionary
 */
Dict* createDict();

/**
 * Adds an entry to the list.
 * @param dict The dictionary, the element should be added to
 * @param functionName the name of the new function
 * @param functionAddress the address of the first function to be called in this function
 * @return -1 for failure, 0 for success
 */
int addEntry(Dict* dict, char* functionName, int functionAddress);

/**
 * searches the dictionary for the function name given as a parameter
 * @param dict the dictionary to search through
 * @param functionName the name of the function to search for
 * @return a pointer to the element or NULL if no element was found with the given name
 */
DictEntry* searchEntry(Dict* dict, const char* functionName);

#endif //AMFORTH_DICT_H
