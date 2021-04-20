#include "global.h"

int error_cnt = 0;

void ERROR(char* msg){
    error_cnt++;
    fprintf(stdout, ":%d: %s\n>>>%s<<<\n", error_cnt, msg, token);
    clearStack(parameterStack);
    fprintf(stdout, "Stack cleared\n");

    //skip back to start of shell
    skipLine();
    ip = start;
}

void ZERO_LEN(){
    ERROR("Attempt to use zero-length string as a name");
}