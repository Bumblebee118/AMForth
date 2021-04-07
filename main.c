#include "global.h"
#include "interpret.h"

void printSynopsis(void);

void tests();

int main(int argc, char **argv) {

    //initialize stacks and dictionary
    createDict();
    parameterStack = createStack(STANDARD_STACK_CAPACITY);
    Stack *returnStack = createStack(STANDARD_STACK_CAPACITY);

    //TODO automatically fill the dictionary with the basic functions

    tests(dict, parameterStack);

    if (argc > 2) {
        printSynopsis();
        exit(EXIT_FAILURE);
    }
    FILE *inputStream = stdin;

    if (argc > 1) {
        char *filename = argv[1];
        inputStream = fopen(filename, "r");

        if (inputStream == NULL) {
            printSynopsis();
            exit(EXIT_FAILURE);
        }
    }

    startInterpret(inputStream, returnStack);

    deleteDict(dict);
    deleteStack(parameterStack);
    deleteStack(returnStack);

    exit(EXIT_SUCCESS);
}

void printSynopsis(void) {
    fprintf(stdout, "Usage: ./forth [FILE]\n");
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
//    DictEntry **entries = (DictEntry **) malloc(3 * sizeof(DictEntry *));
//    entries[0] = getEntry(dict, "+");
//    entries[1] = getEntry(dict, "-");
//    entries[2] = getEntry(dict, ";");
//    addEntry(dict, "addsub", 0, NULL, entries, NULL);

    getEntry("+")->basicfunc(parameterStack);

    //printf("%d\n", peek(stack));

    getEntry("-")->basicfunc(parameterStack);

    //  printf("%d\n", peek(stack));


    /*removeEntry(dict, "add");

    if (getEntry(dict, "add")==NULL){
        printf("Yep this is Null!\n");
    }

    getEntry(dict, "sub")->basicfunc(stack);

    printf("%d\n", peek(stack));*/

//    addEntry(dict, "test1", 4);
//    addEntry(dict, "test2", 8);
//    addEntry(dict, "test3", 12);
//    addEntry(dict, "test1", 13);

//    DictEntry *d = searchEntry(dict, "test2");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    d = searchEntry(dict, "test1");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    d = searchEntry(dict, "test3");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//
//    int r = removeEntry(dict, "test1");
//    printf("%d was returned from the delete function\n", r);
//    r = removeEntry(dict, "test1");
//    printf("%d was returned from the delete function\n", r);
//
//    d = searchEntry(dict, "test1");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
//
//    d = searchEntry(dict, "test2");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
//    d = searchEntry(dict, "test3");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
}
