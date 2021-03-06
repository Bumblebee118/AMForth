#include "global.h"

void THROW() {
    static int error_cnt = 0;

    cell_t errno = pop(parameterStack);
    if (errno == 0) return;

    error_cnt++;
    char *str;
    switch (errno) {
        case ERR_UNDEFINED_WORD:
            str = "Undefined word";
            break;
        case ERR_STACK_UNDERFLOW:
            str = "Stack underflow";
            break;
        case ERR_STACK_OVERFLOW:
            str = "Stack overflow";
            break;
        case ERR_PARSING_ERROR:
            str = "Parsing error";
            break;
        case ERR_TOKEN_SIZE_LIMIT:
            str = "Token exceeds number of chars";
            break;
        case ERR_INTERPRET_COMPILE_ONLY:
            str = "Interpreting a compile-only word";
            break;
        case ERR_EXPECTED_CTRL_STRUCTURE:
            str = "Control structure was expected";
            break;
        case ERR_UNSTRUCTURED:
            str = "Unstructured";
            break;
        case ERR_NO_MEMORY:
            str = "No memory";
            break;
        case ERR_LOOP_TOO_DEEP:
            str = "Loops deeper than 3 levels are not supported";
            break;
        case ERR_INVALID_ADDR:
            str = "Invalid memory address";
            break;
        case ERR_NULL_POINTER:
            str = "NULL pointer";
            break;
        default:
            str = "Undefined error";
            break;
    }

    fprintf(stdout, ":%d: %s (errno %ld)\n>>>%s<<<\n", error_cnt, str, errno, token);

    //#### just an idea ####
   /*if (!isEmpty(returnStack)) fprintf(stdout, "Backtrace:\n");
    Dict* trace;
    while (!isEmpty(returnStack)){
        trace = (Dict*) pop(returnStack);   //pop last executed word
        pop(returnStack);                   //pop return address
        fprintf(stdout, "$%ld %s\n", (cell_t) trace, trace->word);
    }*/
    //#### just an idea ####

    clearStack(parameterStack);
    fprintf(stdout, "Stack cleared\n");

    //skip back to start of shell
    skipLine();
    ip = start;

    if (*isCompileMode) stopCompile();
}

