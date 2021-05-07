//
// Created by Alexander on 07.05.2021.
//

#ifndef AMFORTH_LIST_H
#define AMFORTH_LIST_H

typedef struct List{
    void* ptr;
    struct List* link;
}List;

List* add(List* list, void* ptr);

void deleteList(List* list);

#endif //AMFORTH_LIST_H
