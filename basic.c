//
// Created by Stefan Walser on 30.03.21.
//

#include "global.h"

//#########  ARITHMETIC #############

void ADD() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t sum = a + b;
    push(parameterStack, sum);
}

void SUBTRACT() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    cell_t diff = a - b;
    push(parameterStack, diff);
}

void MULTIPLY() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t sum = a * b;
    push(parameterStack, sum);
}

void DIVIDE() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
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
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a < b));
}

void GREATER() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a > b));
}

void EQUAL() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a == b));
}

void NOTEQUAL() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a != b));
}

void LESSEQ() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a <= b));
}

void GREATEREQ() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a >= b));
}

void ZEROLESS() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a < 0));
}

void ZEROGREATER() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a > 0));
}

void ZEROEQ() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a == 0));
}

void ZERONOTEQ() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a != 0));
}

void ZEROLESSEQ() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a <= 0));
}

void ZEROGREATEREQ() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, -(a >= 0));
}

//#########  Logical Operators #############

void AND() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, a & b);
}

void OR() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, a | b);
}

void XOR() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
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
        THROW();
        return;
    }

    b == FALSE ? (ip = (Dict **) *ip) : ip++;
}

void PREPFORWARDREF() {
    *user_code = 0;
    push(parameterStack, (cell_t) user_code);
    user_code++;
}

void PREPBACKWARDREF() {
    push(parameterStack, (cell_t) user_code);
}

void RESOLVEFORWARDREF() {
    Dict **ptr = (Dict **) pop(parameterStack);
    *ptr = (Dict *) user_code;
}

void RESOLVEBACKWARDREF() {
    Dict **ptr = (Dict **) pop(parameterStack);
    *user_code = (Dict *) ptr;
}

void IF() {
    compile("?branch");
    PREPFORWARDREF();
}

void ELSE() {
    compile("branch");
    PREPFORWARDREF();
    SWAP();
    RESOLVEFORWARDREF();
}

void THEN() {
    RESOLVEFORWARDREF();
}

//#########  LOOP  #############

void DO() {
    compile("i");
    compile("!");
    compile("pushonreturn");
    PREPBACKWARDREF();
    compile("peekfromreturn");
    compile("i");
    compile("@");
    compile(">");
    compile("?branch");
    PREPFORWARDREF();
    compile("1");
    compile("i");
    compile("@");
    compile("+");
    compile("i");
    compile("!");
}

void LOOP() {
    compile("branch");
    SWAP();
    RESOLVEBACKWARDREF();
    RESOLVEFORWARDREF();
    compile("0");
    compile("i");
    compile("!");
}

void PUSHONRETURN() {
    push(returnStack, pop(parameterStack));
}

void PEEKFROMRETURN() {
    push(parameterStack, peek(returnStack));
}

//#########  STACK #############

void SWAP() {
    cell_t b = pop(parameterStack);
    if (b == nil) {
        THROW();
        return;
    }

    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, b);
    push(parameterStack, a);
}

void DUP() {
    cell_t a = peek(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, a);

}

void PRINTPOPSTACK() {
    cell_t a = pop(parameterStack);
    if (a == nil) {
        THROW();
        return;
    }

    fprintf(stdout, "%ld ", a);
}

void PRINTSTACK() {
    fprintf(stdout, "<%d> ", (parameterStack->top) + 1);

    int i = 0;
    while (i <= parameterStack->top) {
        fprintf(stdout, "%ld ", parameterStack->array[i]);
        i++;
    }
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
    data.definition = user_code;
    cw = addEntry(token, data, &DOCOLON);

    isCompileMode = 1;
}

void DOSEMI() {
    ip = (Dict **) pop(returnStack);
}

void SEMI() {
    compile("dosemi");
    isCompileMode = 0;
}

void DOLIT() {
    cell_t lit = (cell_t) *ip;
    push(parameterStack, lit);
    ip++;
}

void DOSTORESTRING() {
    cell_t a = (cell_t) *ip;
    if (a == nil) {
        THROW();
        return;
    }

    push(parameterStack, a);
    ip++;
}

void DOPRINTSTRING() {
    char *string = (char *) (cell_t) *ip;
    fprintf(stdout, "%s ", string);
    ip++;
}

__attribute__((unused)) void NEXT() {
}

void INTERPRET() {
    interpret();
}

void EXECUTE() {
    char *word = (char *) pop(parameterStack);
    if ((cell_t) word == nil) {
        THROW();
        return;
    }
    execute(word);
}

void BRANCH0() {
    //cell_t val = pop(parameterStack);
    //if(val == 0){
    ip = ip - 3;
    //}
}

void LISTWORDS() {
    Dict *pointer = dict;
    while (pointer != NULL) {
        fprintf(stdout, "%s ", (*pointer).word);
        pointer = (*pointer).link;
    }
}

void STARTSTORESTRING() {
    isStringMode = 1;
}

void STARTPRINTSTRING() {
    isStringMode = 2;
}

void ENDSTRING() {
    if (isCompileMode) {
        if (isStringMode == 1) compile("dostorestring");
        else if (isStringMode == 2) compile("doprintstring");

        char *a = (char *) pop(parameterStack);
        if ((cell_t) a == nil) {
            THROW();
            return;
        }

        *user_code = (Dict *) (cell_t) a;
        user_code++;
        isStringMode = 0;
    } else if (isStringMode == 1) isStringMode = 0;
    else if (isStringMode == 2) {
        isStringMode = 0;
        char *a = (char *) pop(parameterStack);
        if ((cell_t) a == nil) {
            THROW();
            return;
        }

        fprintf(stdout, "%s ", a);
    }
}

void TYPE() {
    char *a = (char *) pop(parameterStack);
    if ((cell_t) a == nil) {
        THROW();
        return;
    }
    fprintf(stdout, "%s ", a);
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
    Data data;
    data.value = (cell_t) malloc(sizeof(cell_t));

    addEntry(token, data, &DOVAR);
}

void DOVAR() {
    push(parameterStack, wp->data.value);
}

void ASSIGNVAR() {
    cell_t *ptr = (cell_t *) pop(parameterStack);
    if ((cell_t) ptr == nil) {
        THROW();
        return;
    }
    cell_t val = pop(parameterStack);
    if (val == nil) {
        THROW();
        return;
    }

    *ptr = val;
}

void FETCHVAR() {
    cell_t *ptr = (cell_t *) pop(parameterStack);
    if (*ptr == nil) {
        THROW();
        return;
    }
    push(parameterStack, *ptr);
}
