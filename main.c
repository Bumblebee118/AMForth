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
int isStringMode = 0; // DO NOT DELETE !!!!
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
    // : inner-interpreter begin 1 while ' compilemode @ if compile else execute then repeat ;
    Data data;
    data.definition = userCode;
    cw = addEntry("inner-interpreter", data, &DOCOLON);

    defs=&macros;
    compile(getEntry("begin"));
    defs=&dict;
    push(parameterStack, 1);
    compile(getEntry("dolit"));
    defs=&macros;
    compile(getEntry("while"));
    defs=&dict;
    compile(getEntry("'"));
    compile(getEntry("compilemode"));
    compile(getEntry("@"));
    defs=&macros;
    compile(getEntry("if"));
    defs=&dict;
    compile(getEntry("compile"));
    defs=&macros;
    compile(getEntry("else"));
    defs=&dict;
    compile(getEntry("execute"));
    defs=&macros;
    compile(getEntry("then"));
    defs=&macros;
    compile(getEntry("repeat"));
    defs=&dict;

    compile(getEntry("dosemi"));
}
