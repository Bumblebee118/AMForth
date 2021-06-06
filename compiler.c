//
// Created by Stefan Walser on 07.04.21.
//

#include "global.h"

void compile(Dict* word) {
    wp = word;

    if((wp >= macros_begin) && (wp <= macros)){
        //is macro
        wp->code();
    }else if ((wp >= dict_begin) && (wp <= dict)){
        //is defs
        *userCode = wp;
        userCode++;

        if(wp == dolit_wp){
            cell_t num = pop(parameterStack);
            if (num == nil) {
                push(parameterStack, ERR_STACK_UNDERFLOW);
                THROW();
                return;
            }
            *(userCode++) = (Dict *) num;
        }
    }else{
        push(parameterStack, ERR_INVALID_ADDR);
        THROW();
    }

    /*
    defs = &macros;
    if ((entry = getEntry(word))) {
        defs = &dict;
        entry->code();
        return;
    }

    defs = &dict;
    if ((entry = getEntry(word))) {
        *userCode = entry;
        userCode++;
        return;
    }

    defs = &dict;
    char *endptr;
    cell_t num = (cell_t) strtol(word, &endptr, 10);

    if (strlen(endptr) == 0) {
        compile("dolit");
        *(userCode++) = (Dict *) num;
    } else {
        push(parameterStack, ERR_UNDEFINED_WORD);
        THROW();
        //stopCompile();
    }

     */
}

void stopCompile(){
    redefined = 0;
    isCompileMode = 0;
    if(cw != NULL){
        userCode = cw->data.definition;    //reset userCode pointer
        removeEntry(cw->word);             //delete word from dictionary
        cw = NULL;
    }

}