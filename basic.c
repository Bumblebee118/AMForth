//
// Created by Stefan Walser on 30.03.21.
//

#include "global.h"

//#########  ARITHMETIC #############

void ADD() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t sum = a + b;
    push(parameterStack, sum);
}

void SUBTRACT() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t diff = a - b;
    push(parameterStack, diff);
}

void MULTIPLY() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t sum = a * b;
    push(parameterStack, sum);
}

void DIVIDE() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t diff = a / b;
    push(parameterStack, diff);
}

//#########  CONDITIONAL #############

void LESS() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a < b));
}

void GREATER() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a > b));
}

void EQUAL() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a == b));
}

void NOTEQUAL() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a != b));
}

void LESSEQ() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a <= b));
}

void GREATEREQ() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a >= b));
}

void ZEROLESS() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a < 0));
}

void ZEROGREATER() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a > 0));
}

void ZEROEQ() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a == 0));
}

void ZERONOTEQ() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a != 0));
}

void ZEROLESSEQ() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a <= 0));
}

void ZEROGREATEREQ() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, -(a >= 0));
}

//#########  Logical Operators #############

void AND() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, a & b);
}

void OR() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, a | b);
}

void XOR() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, a ^ b);
}

//#########  Flow Control #############

void BRANCH() {
    ip = (Dict **) *ip;
}

void CHECKBRANCH() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    b == FALSE ? (ip = (Dict **) *ip) : ip++;
}

void PREPFORWARDREF() {
    *userCode = 0;
    push(parameterStack, (cell_t) userCode);
    userCode++;
}

void PREPBACKWARDREF() {
    push(parameterStack, (cell_t) userCode);
}

void RESOLVEFORWARDREF() {
    Dict **ptr = (Dict **) pop(parameterStack);
    *ptr = (Dict *) userCode;
}

void RESOLVEBACKWARDREF() {
    Dict **ptr = (Dict **) pop(parameterStack);
    *userCode = (Dict *) ptr;
    userCode++;
}

void IF() {
    compile(checkbranch_wp);
    PREPFORWARDREF();
    push(parameterStack, COMP_IF);
}

void ELSE() {
    compile(branch_wp);

    cell_t ite = pop(parameterStack);
    if (ite != COMP_IF) {
        push(parameterStack, ERR_EXPECTED_CTRL_STRUCTURE);
        THROW();
        return;
    }
    PREPFORWARDREF();
    SWAP();
    RESOLVEFORWARDREF();
    push(parameterStack, COMP_ELSE);
}

void THEN() {
    cell_t ite = pop(parameterStack);
    if ((ite != COMP_IF) && (ite != COMP_ELSE)) {
        push(parameterStack, ERR_EXPECTED_CTRL_STRUCTURE);
        THROW();
        return;
    }
    RESOLVEFORWARDREF();
}

//#########  LOOP  #############

void DO() {
    loopDepth++;
    chooseCorrectLoopVar();
    compile(assignvar_wp);
    compile(por_wp);
    PREPBACKWARDREF();
    compile(pfr_wp);
    chooseCorrectLoopVar();
    compile(fetchvar_wp);
    compile(gt_wp);
    compile(checkbranch_wp);
    PREPFORWARDREF();
    push(parameterStack, COMP_DO);
}

void LOOP() {
    cell_t doLabel = pop(parameterStack);
    if (doLabel != COMP_DO) {
        push(parameterStack, ERR_EXPECTED_CTRL_STRUCTURE);
        THROW();
        return;
    }
    push(parameterStack, 1);
    compile(dolit_wp);
    chooseCorrectLoopVar();
    compile(fetchvar_wp);
    compile(add_wp);
    chooseCorrectLoopVar();
    compile(assignvar_wp);
    compile(branch_wp);
    SWAP();
    RESOLVEBACKWARDREF();
    RESOLVEFORWARDREF();
    push(parameterStack, 0);
    compile(dolit_wp);
    chooseCorrectLoopVar();
    compile(assignvar_wp);
    compile(pfr_wp);
    loopDepth--;
}

void BEGIN() {
    PREPBACKWARDREF();
    push(parameterStack, COMP_BEGIN);
}

void UNTIL() {
    cell_t beginLabel = pop(parameterStack);
    if (beginLabel != COMP_BEGIN) {
        push(parameterStack, ERR_EXPECTED_CTRL_STRUCTURE);
        THROW();
        return;
    }
    compile(checkbranch_wp);
    RESOLVEBACKWARDREF();
}

void AGAIN() {
    cell_t beginLabel = pop(parameterStack);
    if (beginLabel != COMP_BEGIN) {
        push(parameterStack, ERR_EXPECTED_CTRL_STRUCTURE);
        THROW();
        return;
    }
    compile(branch_wp);
    RESOLVEBACKWARDREF();
}

void WHILE() {
    cell_t beginLabel = pop(parameterStack);
    if (beginLabel != COMP_BEGIN) {
        push(parameterStack, ERR_EXPECTED_CTRL_STRUCTURE);
        THROW();
        return;
    }
    compile(checkbranch_wp);
    PREPFORWARDREF();
    push(parameterStack, COMP_WHILE);
}

void REPEAT() {
    cell_t beginLabel = pop(parameterStack);
    if (beginLabel != COMP_WHILE) {
        push(parameterStack, ERR_EXPECTED_CTRL_STRUCTURE);
        THROW();
        return;
    }
    compile(branch_wp);
    SWAP();
    RESOLVEBACKWARDREF();
    RESOLVEFORWARDREF();
}

void chooseCorrectLoopVar() {
    switch (loopDepth) {
        case 1:
            compile(i_wp);
            break;
        case 2:
            compile(j_wp);
            break;
        case 3:
            compile(k_wp);
            break;
        default:
            push(parameterStack, ERR_LOOP_TOO_DEEP);
            THROW();
    }
}

void PUSHONRETURN() {
    push(returnStack, pop(parameterStack));
}

void PEEKFROMRETURN() {
    push(parameterStack, peek(returnStack));
}

void POPFROMRETURN() {
    pop(returnStack);
}

//#########  STACK #############

void SWAP() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, b);
    push(parameterStack, a);
}

void DUP() {
    cell_t a = peek(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, a);

}

void PRINTPOPSTACK() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    fprintf(stdout, "%ld ", a);
    fflush(stdout);
}

void PRINTSTACK() {
    fprintf(stdout, "<%d> ", (parameterStack->top) + 1);

    int i = 0;
    while (i <= parameterStack->top) {
        fprintf(stdout, "%ld ", parameterStack->array[i]);
        i++;
    }
    fflush(stdout);
}


//#########  COMPILE #############

void DOCOLON() {
    push(returnStack, (cell_t) ip);
    ip = wp->data.definition;
}

void COLON() {
    int len = nextToken();

    if (len >= MAX_WORD_NAME_SIZE) {
        push(parameterStack, ERR_TOKEN_SIZE_LIMIT);
        THROW();
        return;
    }

    Data data;
    data.definition = userCode;
    cw = addEntry(token, data, &DOCOLON);

    isCompileMode = 1;
}

void DOSEMI() {
    ip = (Dict **) pop(returnStack);
}

void SEMI() {
    cell_t fcc = peek(parameterStack);
    if ((fcc == COMP_IF) || (fcc == COMP_ELSE) || (fcc == COMP_DO) || (fcc == COMP_BEGIN)){
        push(parameterStack, ERR_UNSTRUCTURED);
        THROW();
        return;
    }
    compile(dosemi_wp);
    isCompileMode = 0;

    if(redefined){
        char msg [MAX_WORD_NAME_SIZE + 12];
        sprintf(msg, "redefined %s", cw->word);
        print_msg(msg);
        redefined = 0;
    }
}

void DOLIT() {
    push(parameterStack, (cell_t) *(ip++));
}

__attribute__((unused)) void NEXT() {
}

void INTERPRET() {
    interpret();
}

void EXECUTE() {
    Dict* word = (Dict *) pop(parameterStack);
    if ((cell_t) word == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }
    execute(word);
}

void COMPILE() {
    Dict* word = (Dict *) pop(parameterStack);
    if ((cell_t) word == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }
    compile(word);
}

void BRANCH0() {
    //cell_t val = pop(parameterStack);
    //if(val == 0){
    ip = ip - 2;
    //}
}

void LISTWORDS() {
    Dict *pointer = dict;
    while (pointer != NULL) {
        if(((*pointer).code != &DOVAR) && ((*pointer).code != &DOCONST)){
            fprintf(stdout, "%s ", (*pointer).word);
        }
        pointer = (*pointer).link;
    }

    pointer = macros;
    while (pointer != NULL) {
        if(((*pointer).code != &DOVAR) && ((*pointer).code != &DOCONST)){
            fprintf(stdout, "%s ", (*pointer).word);
        }
        pointer = (*pointer).link;
    }
    fflush(stdout);
}

void CR() {
    fprintf(stdout, "\n");
    fflush(stdout);
}

void DOSTORESTRING() {
    push(parameterStack, (cell_t) *(ip++));
    push(parameterStack, (cell_t) *(ip++));
}

void DOPRINTSTRING() {
    char *string = (char *) (cell_t) *(ip++);
    fprintf(stdout, "%s ", string);
    fflush(stdout);
}

void STORESTRING() {
    char* str =(char*) malloc(sizeof(char )*BASE_STRING_SIZE);
    if(str == NULL){
        push(parameterStack, ERR_NO_MEMORY);
        THROW();
        exit(EXIT_FAILURE);
    }
    cell_t len = nextString(&str);

    if (isCompileMode){
       compile(dostorestring_wp);
        *(userCode++) = (Dict*) str;
        *(userCode++) = (Dict*) len;
    }else{
        push(parameterStack, (cell_t)str);
        push(parameterStack, len); //TODO check push len
    }

}

void PRINTSTRING() {
    if (isCompileMode){
        char* str =(char*) malloc(sizeof(char )*BASE_STRING_SIZE);
        if(str == NULL){
            push(parameterStack, ERR_NO_MEMORY);
            THROW();
            exit(EXIT_FAILURE);
        }
        cell_t len = nextString(&str);
        compile(doprintstring_wp);
        *(userCode++) = (Dict*) str;

    }else{
        char current = getNextChar();
        while((current != '\"') && (current != '\n')){
            fprintf(stdout, "%c", current);
            current = getNextChar();
        }

        fprintf(stdout, " ");
    }
    fflush(stdout);
}

void TYPE() {
    //TODO check if lenght is necessary
    cell_t len = pop(parameterStack);
    if (len == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    char *a = (char *) pop(parameterStack);

    if ((cell_t) a == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }
    fprintf(stdout, "%s ", a);
    fflush(stdout);
}

//#########  VARIABLE AND CONST #############

void CONST() {
    int len = nextToken();

    if (len >= MAX_WORD_NAME_SIZE) {
        push(parameterStack, ERR_TOKEN_SIZE_LIMIT);
        THROW();
        return;
    }

    Data data;
    data.value = pop(parameterStack);
    if (data.value == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    addEntry(token, data, &DOCONST);
}

void DOCONST() {
    push(parameterStack, wp->data.value);
}

void VAR() {
    int len = nextToken();

    if (len >= MAX_WORD_NAME_SIZE) {
        push(parameterStack, ERR_TOKEN_SIZE_LIMIT);
        THROW();
        return;
    }

    void* ptr = malloc(sizeof(cell_t));
    if(ptr == NULL){
        push(parameterStack, ERR_NO_MEMORY);
        THROW();
        exit(EXIT_FAILURE);
    }

    Data data;
    data.value = (cell_t) ptr;

    addEntry(token, data, &DOVAR);
}

void DOVAR() {
    push(parameterStack, wp->data.value);
}

void ASSIGNVAR() {
    cell_t *ptr = (cell_t *) pop(parameterStack);
    if ((cell_t) ptr == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }
    cell_t val = pop(parameterStack);
    if (val == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    *ptr = val;
}

void FETCHVAR() {
    cell_t *ptr = (cell_t *) pop(parameterStack);
    if (*ptr == nil) {
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }
    push(parameterStack, *ptr);
}

void FORGET(){
    int len = nextToken();

    if (len >= MAX_WORD_NAME_SIZE) {
        push(parameterStack, ERR_TOKEN_SIZE_LIMIT);
        THROW();
        return;
    }

    if(removeEntry(token) == 0){
        fprintf(stdout, "forgot word '%s'", token);
    }else{
        push(parameterStack, ERR_UNDEFINED_WORD);
        THROW();
    }
}

void EMIT(){
    cell_t num = pop(parameterStack);
    if(num == nil){
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    fprintf(stdout, "%c", (char) num);
}

void PICK(){
    cell_t u = pop(parameterStack);
    cell_t num;
    if((u == nil) || ((num = pickElement(parameterStack, u)) == nil)){
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }
    push(parameterStack, num);
}


void DROP(){
    /*cell_t u = pop(parameterStack);
    if((u == nil) || (dropElement(parameterStack, u) == nil)){
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }*/

    if((dropElement(parameterStack, 0) == nil)){
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

}

void OVER(){
    cell_t num;
    if((num = pickElement(parameterStack, 1)) == nil){
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }
    push(parameterStack, num);
}

void ROT(){
    cell_t num;
    if((num = dropElement(parameterStack, 2)) == nil){
        push(parameterStack, ERR_STACK_UNDERFLOW);
        THROW();
        return;
    }

    push(parameterStack, num);
}