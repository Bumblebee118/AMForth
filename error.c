#include "global.h"

void PRINT_ERROR_MSG(char* msg){
    error_cnt++;
    fprintf(stdout, "\n:%d: %s\n>>>%s<<<\n", error_cnt, msg, token);
}