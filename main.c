#include "global.h"

dict_t *wp = NULL;
dict_t **ip = NULL;
dict_t *cw = NULL;
dict_t **defs = &dict;
dict_t **user_code = user_code_base;
dict_t **start = NULL;

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

    //compile the interpreter
    compileInterpreter();

    virtualMachine();

    exit(EXIT_SUCCESS);
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
//    dict_t **entries = (dict_t **) malloc(3 * sizeof(dict_t *));
//    entries[0] = getEntry("+");
//    entries[1] = getEntry("-");
//    entries[2] = getEntry(";");
//    addEntry("addsub", 0, NULL, entries, NULL);

    getEntry("+")->basicfunc(parameterStack);

    //printf("%d\n", peek(stack));

    getEntry("-")->basicfunc(parameterStack);

    //  printf("%d\n", peek(stack));


    /*removeEntry(dict_t, "add");

    if (getEntry(dict_t, "add")==NULL){
        printf("Yep this is Null!\n");
    }

    getEntry(dict_t, "sub")->basicfunc(stack);

    printf("%d\n", peek(stack));*/

//    addEntry(dict_t, "test1", 4);
//    addEntry(dict_t, "test2", 8);
//    addEntry(dict_t, "test3", 12);
//    addEntry(dict_t, "test1", 13);

//    dict_t *d = searchEntry(dict_t, "test2");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    d = searchEntry(dict_t, "test1");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    d = searchEntry(dict_t, "test3");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//
//    int r = removeEntry(dict_t, "test1");
//    printf("%d was returned from the delete function\n", r);
//    r = removeEntry(dict_t, "test1");
//    printf("%d was returned from the delete function\n", r);
//
//    d = searchEntry(dict_t, "test1");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
//
//    d = searchEntry(dict_t, "test2");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
//    d = searchEntry(dict_t, "test3");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
}
