#include "global.h"

//init extern variable
Dict *wp = NULL;
Dict **ip = NULL;
Dict *cw = NULL;
Dict **defs = &dict;
Dict **user_code = user_code_base;
Dict **start = NULL;
char* token = NULL;
int isCompileMode = 0;
int isStringMode = 0;

void printSynopsis(void);

void virtualMachine(void);

void compileInterpreter(void);

int main(int argc, char **argv) {

    //initialize stacks
    parameterStack = createStack(STANDARD_STACK_CAPACITY);
    returnStack = createStack(STANDARD_STACK_CAPACITY);

    addBasicWordsToDict();

    if (argc > 2) {
        printSynopsis();
        exit(EXIT_FAILURE);
    }
    stream = stdin;

    if (argc > 1) {
        char *filename = argv[1];
        stream = fopen(filename, "r");

        if (stream == NULL) {
            printSynopsis();
            exit(EXIT_FAILURE);
        }
    }

    //welcome text on startup
    fprintf(stdout, "Type 'bye' to exit\n");

    //set instr pointer
    ip = user_code;
    start = ip;

    compileInterpreter();

    virtualMachine();
}

void printSynopsis(void) {
    fprintf(stdout, "Usage: ./AMForth [FILE]\n");
}

void virtualMachine(void) {
    for (;;) {
        wp = *ip++;
        wp->code();
    }
}

void compileInterpreter(void) {
    // word - execute - branch //

    compile("'");
    compile("execute");
    compile("branch0");
}

