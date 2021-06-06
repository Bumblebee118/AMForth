#include "global.h"

//init extern variable
Dict *wp = NULL;
Dict **ip = NULL;
Dict *cw = NULL;
Dict **defs = &dict;
Dict **userCode = userCodeBase;
Dict **start = NULL;
char *token = NULL;
int isCompileMode = 0;
int isStringMode = 0;
int loopDepth = 0;

void printSynopsis(void);

_Noreturn void virtualMachine(void);

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
    ip = userCode;
    start = ip;

    compileInterpreter();

    virtualMachine();
}

void printSynopsis(void) {
    fprintf(stdout, "Usage: ./AMForth [FILE]\n");
}

_Noreturn void virtualMachine(void) {
    for (;;) {
        wp = *ip++;
        wp->code();
    }
}

void compileInterpreter(void) {
    // word - execute - branch //
    Dict* word = getEntry("'");
    compile(word);
    //compile("execute");
    word = getEntry("branch0");
    compile(word);
}
