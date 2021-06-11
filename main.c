#include "global.h"

//init extern variable
Dict *dict;
Dict *dict_begin;
Dict *macros;
Dict *macros_begin;
Dict *wp ;
Dict **ip;
Dict *cw;
Dict **defs = &dict;
Dict **userCode = user_code_base;
Dict **start;
Stack* parameterStack;
Stack* returnStack;
List* ptrList;
FILE* stream;
char *token;
cell_t * isCompileMode = variable_space;
int loopDepth = 0;
Dict *user_code_base[CODE_SIZE];
cell_t variable_space[HEAP_SIZE];
cell_t* heapptr = variable_space+2;
cell_t* heap = variable_space+1;
Dict* dolit_wp;
Dict* checkbranch_wp;
Dict* branch_wp;
Dict* assignvar_wp;
Dict* pushonreturn_wp;
Dict* popfromreturn_wp;
Dict* peekfromreturn_wp;
Dict* fetchvar_wp;
Dict* gt_wp;
Dict* add_wp;
Dict* dosemi_wp;
Dict* dostorestring_wp;
Dict* doprintstring_wp;
Dict* i_wp;
Dict* k_wp;
Dict* j_wp;

void printSynopsis(void);

_Noreturn void virtualMachine(void);

void compileInterpreter(void);

int main(int argc, char **argv) {

    // bisschen tricky
    *heap = (cell_t) heapptr;

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
