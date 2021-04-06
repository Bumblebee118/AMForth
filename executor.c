#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "executor.h"

int execute(char* token, Dict* dict, Stack* parameterStack, Stack* returnStack){
    DictEntry *entry = getEntry(dict, token);

    //if entry could not be found check if it can be converted to a number
    if(entry == NULL){
        char* endptr;
        int num = strtol(token, &endptr, 10);

        if (strlen(endptr)==0){
            push(parameterStack, num);
        }
        else{
            printf("\nUndefined word\n>>>%s<<<\n", token);
            clearStack(parameterStack);
            return -1;
        }

    //if the word exists in the dictionary, execute the definition
    }else{
        //TODO Execute function definition here
        return entry->basicfunc(parameterStack);
    }

}

