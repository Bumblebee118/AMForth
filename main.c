#include "global.h"

Dict *wp = NULL;
Dict **ip = NULL;
Dict *cw = NULL;
Dict **defs = &dict;
Dict **user_code = user_code_base;
Dict **start = NULL;

void printSynopsis(void);

_Noreturn void virtualMachine(void);

void compileInterpreter(void);

void tests();

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
    fprintf(stdout, "Usage: ./forth [FILE]\n");
}

_Noreturn void virtualMachine(void) {
    for (;;) {
        wp = *ip++;
        wp->basicfunc();
    }
}

void compileInterpreter(void) {
    // word - execute - branch //

    compile("interpret");
    compile("execute");
    compile("branch0");
}


void tests() {
    push(parameterStack, 10);
    push(parameterStack, 2100);
    push(parameterStack, -1);
    push(parameterStack, 13);
    // printf("%d\n", peek(stack));

//    printf("%d popped from stack\n", pop(stack));
//    printf("%d popped from stack\n", pop(stack));
//    printf("%d popped from stack\n", pop(stack));

    addEntry("+", 0, NULL, NULL, &ADD);
    addEntry("-", 0, NULL, NULL, &SUBTRACT);
    addEntry("*", 0, NULL, NULL, &MULTIPLY);
    addEntry("/", 0, NULL, NULL, &DIVIDE);
    addEntry(".", 0, NULL, NULL, &PRINTPOPSTACK);
    addEntry(".s", 0, NULL, NULL, &PRINTSTACK);
    addEntry(":", 0, NULL, NULL, &DOCOLON);
    addEntry(";", 0, NULL, NULL, NULL);
//    Dict **entries = (Dict **) malloc(3 * sizeof(Dict *));
//    entries[0] = getEntry("+");
//    entries[1] = getEntry("-");
//    entries[2] = getEntry(";");
//    addEntry("addsub", 0, NULL, entries, NULL);

    getEntry("+")->basicfunc(parameterStack);

    //printf("%d\n", peek(stack));

    getEntry("-")->basicfunc(parameterStack);

    //  printf("%d\n", peek(stack));


    /*removeEntry(Dict, "add");

    if (getEntry(Dict, "add")==NULL){
        printf("Yep this is Null!\n");
    }

    getEntry(Dict, "sub")->basicfunc(stack);

    printf("%d\n", peek(stack));*/

//    addEntry(Dict, "test1", 4);
//    addEntry(Dict, "test2", 8);
//    addEntry(Dict, "test3", 12);
//    addEntry(Dict, "test1", 13);

//    Dict *d = searchEntry(Dict, "test2");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    d = searchEntry(Dict, "test1");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    d = searchEntry(Dict, "test3");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//
//    int r = removeEntry(Dict, "test1");
//    printf("%d was returned from the delete function\n", r);
//    r = removeEntry(Dict, "test1");
//    printf("%d was returned from the delete function\n", r);
//
//    d = searchEntry(Dict, "test1");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
//
//    d = searchEntry(Dict, "test2");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
//    d = searchEntry(Dict, "test3");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
}
