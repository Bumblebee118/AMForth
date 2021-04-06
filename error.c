#include <stdio.h>
#include "error.h"

void PRINT_ERROR_MSG(char* msg, char* word){
    error_cnt++;
    fprintf(stdout, "\n:%d: %s\n>>>%s<<<\n", error_cnt, msg, word);
}