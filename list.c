//
// Created by Alexander on 07.05.2021.
//

#include "global.h"

List* add(List** list, void* ptr){
    List* newEntry = (List*) malloc(sizeof(List));
    if (newEntry == NULL) return NULL;

    newEntry->ptr = ptr;
    newEntry->link = *list;
    *list = newEntry;

    return newEntry;
}

void deleteList(List* list){
    List* current = list;
    List* next;
    while (current != NULL){
        if(current->ptr != NULL) free(current->ptr);
        next = current->link;
        free(current);
        current = next;
    }
}