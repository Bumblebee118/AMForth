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
    Dict* word = getEntry("begin");
    defs=&dict;
    compile(word);
    push(parameterStack, 1);
    word = getEntry("dolit");
    compile(word);
    defs=&macros;
    word = getEntry("while");
    defs=&dict;
    compile(word);
    word = getEntry("'");
    compile(word);
    word = getEntry("compilemode");
    compile(word);
    word = getEntry("@");
    compile(word);
    defs=&macros;
    word = getEntry("if");
    defs=&dict;
    compile(word);
    word = getEntry("compile");
    compile(word);
    defs=&macros;
    word = getEntry("else");
    defs=&dict;
    compile(word);
    word = getEntry("execute");
    compile(word);
    defs=&macros;
    word = getEntry("then");
    defs=&dict;
    compile(word);
    defs=&macros;
    word = getEntry("repeat");
    defs=&dict;
    compile(word);

    word = getEntry("dosemi");
    compile(word);
}
