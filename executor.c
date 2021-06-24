#include "global.h"

void execute(Dict* word) {
    wp = word; //set current word pointer

    if ((wp >= dict_begin) && (wp <= dict)) {
        //valid address
        //ignore if word is dolit
        if(word != dolit_wp) wp->code(); //execute code
    }else  if((wp >= macros_begin) && (wp <= macros)){
        push(parameterStack, ERR_INTERPRET_COMPILE_ONLY);
        THROW();
    }else{
        push(parameterStack, ERR_INVALID_ADDR);
        THROW();
    }

    /*
    //if the word exists in the dictionary, execute the definition
    if ((wp = getEntry(word))) {
        wp->code();
        return;
    }

    //check if it is a macro
    defs = &macros;
    if ((wp = getEntry(word))) {
        defs = &dict;
        push(parameterStack, ERR_INTERPRET_COMPILE_ONLY);
        THROW();
        return;
    }
    defs = &dict;

    //check if it is a number
    char *endptr;
    cell_t num = (cell_t) strtol(word, &endptr, 10);

    if (strlen(endptr) == 0) {
        push(parameterStack, num);
    } else {
        push(parameterStack, ERR_UNDEFINED_WORD);
        THROW();
    }
*/
}
