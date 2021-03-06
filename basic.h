//
// Created by Stefan Walser on 30.03.21.
//

#ifndef AMFORTH_BASIC_H
#define AMFORTH_BASIC_H

#include <limits.h>

#define COMP_IF nil+1
#define COMP_ELSE nil+2
#define COMP_DO nil+3
#define COMP_BEGIN nil+4
#define COMP_WHILE nil+5

/**
 * typedefs for function pointers
 */
typedef void (*CODEPOINTER)();

//#########  ARITHMETIC #############

/**
 * adds the top most two numbers on the stack and pushes the result back onto the stack
 */
void ADD();

/**
 * subtracts the top most two numbers on the stack and pushes the result back onto the stack
 */
void SUBTRACT();

/**
 * multiplies the top most two numbers on the stack and pushes the result back onto the stack
 */
void MULTIPLY();

/**
 * divides the top most two numbers on the stack and pushes the result back onto the stack
 */
void DIVIDE();


//#########  CONDITIONAL #############
/**
 * pushes -1 on the stack if the second number on the stack is less than the first, 0 otherwise
 */
void LESS();

/**
 * pushes -1 on the stack if the second number on the stack is greater than the first, 0 otherwise
 */
void GREATER();

/**
 * pushes -1 on the stack if the second number on the stack is equal to the first, 0 otherwise
 */
void EQUAL();

/**
 * pushes -1 on the stack if the second number on the stack is not equal to the first, 0 otherwise
 */
void NOTEQUAL();

/**
 * pushes -1 on the stack if the second number on the stack is less or equal to the first, 0 otherwise
 */
void LESSEQ();

/**
 * pushes -1 on the stack if the second number on the stack is greater or equal to the first, 0 otherwise
 */
void GREATEREQ();

/**
 * pushes -1 on the stack if the second number on the stack is less than zero, 0 otherwise
 */
void ZEROLESS();

/**
 * pushes -1 on the stack if the second number on the stack is greater than zero, 0 otherwise
 */
void ZEROGREATER();

/**
 * pushes -1 on the stack if the second number on the stack is equal to zero, 0 otherwise
 */
void ZEROEQ();

/**
 * pushes -1 on the stack if the second number on the stack is not equal to zero, 0 otherwise
 */
void ZERONOTEQ();

/**
 * pushes -1 on the stack if the second number on the stack is equal or less than zero, 0 otherwise
 */
void ZEROLESSEQ();

/**
 * pushes -1 on the stack if the second number on the stack is equal or greater than zero, 0 otherwise
 */
void ZEROGREATEREQ();

//#########  Logical Operators #############
/**
 * takes the top two values of the stack, ANDs them and pushes the result back on the stack
 */
void AND();

/**
 * takes the top two values of the stack, ORs them and pushes the result back on the stack
 */
void OR();

/**
 * takes the top two values of the stack, XORs them and pushes the result back on the stack
 */
void XOR();

//#########  Flow Control #############
/**
 * branch to address that comes next in the dict
 */
void BRANCH();

/**
 * check if the number on the stack not 0 and then branch to the address next in the dict
 */
void CHECKBRANCH();

/**
 * prepare for a forward jump
 */
void PREPFORWARDREF();

/**
 * prepare for a backward jump
 */
void PREPBACKWARDREF();

/**
 * add the the address to the branch spot
 */
void RESOLVEFORWARDREF();

/**
 * add the the address to the branch spot
 */
void RESOLVEBACKWARDREF();

/**
 * perform the part after if when there is number unqual to 0 on the stack
 */
void IF();

/**
 * else part of the if
 */
void ELSE();

/**
 * then closes an if then else -> like end
 */
void THEN();

//#########  LOOP  #############

void DO();

void LOOP();

void ADDLOOP();

void BEGIN();

void UNTIL();

void AGAIN();

void WHILE();

void REPEAT();

void chooseCorrectLoopVar();

void PUSHONRETURN();

void PEEKFROMRETURN();

void POPFROMRETURN();

//#########  STACK #############

/**
 * swaps the to top most values on the stack
 */
void SWAP();

/**
 * duplicates the number on top of the stack
 */
void DUP();

/**
 * Pops the top element of the stack in prints it to stdout
 */
void PRINTPOPSTACK();

/**
 * Prints content of the whole stack without modifying the stack
 */
void PRINTSTACK();


//#########  COMPILE #############
/**
 * Pushes the current ip on the return stack and sets the ip to the next instruction of the current word
 */
void DOCOLON();

/**
 * Reads in the next token as name and adds a new entry in the dictionary with that name and DOCOLON as basic func
 * Starts compile mode
 */
void COLON();

/**
 * Pops the top data of the stack and sets the ip to its data
 */
void DOSEMI();

/**
 * A macro, that compiles DOSEMI and stops the compile mode
 */
void SEMI();

/**
 * Treats the current entry in ip as number and pushes it on the parameter stack
 * Then the ip gets incremented
 */
void DOLIT();

/**
 * takes the string from the userDict and pushes it to the stack
 */
void DOSTORESTRING();

/**
 * takes the string from the userDict and prints it to the console
 */
void DOPRINTSTRING();

/**
 * Reads in one token and pushes its address on the stack
 */
void INTERPRET();

/**
 * Pops the address of the current token of the stack and executes it
 */
void EXECUTE();

/**
 * Pops the address of the current token of the stack and compiles it
 */
void COMPILE();

/**
 * Test branch
 */
void BRANCH0();

/**
 *
 */
void LISTWORDS();

/**
 * Prints a neww line
 */
void CR();

/**
 * Sets the interpreter into string-reading mode
 */
void STORESTRING();

/**
 * Sets the interpreter into string-reading mode and prints the string in the end instead of storing it
 */
void PRINTSTRING();

/**
 * Writes the string on top of the stack to the terminal
 */
void TYPE();

//#########  VARIABLE AND CONST #############

/**
 * takes the next token from the stream and adds a new word to dict with the value currently on the stack
 */
void CONST();

/**
 * pushes the value of the current wp on the stack
 */
void DOCONST();

/**
 * takes the next token from the stream and adds a new word to dict with the value of an address of new variable
 */
void VAR();

/**
 * pushes the address of the current wp on the stack
 */
void DOVAR();

void DOLOOPVAR();

/**
 * pops the address of the variable and new value of the stack and assigns the variable that value
 */
void ASSIGNVAR();

void DOUBLEASSIGN();

/**
 * pops the address of the variable of the stack and pushes the value of the variable on the stack
 */
void FETCHVAR();

void DOUBLEFETCH();

/**
 * lets you remove the first entry, that matches a given name from the dictionary
 */
void FORGET();

/**
 * takes the number from the top of the stack and converts it to a char
 */
void EMIT();

/**
 * takes the number i from top of the stack and duplicates the i-th element on the top of stack
 */
void PICK();

/**
 * drops the x element from the stack
 */
void DROP();

/**
 * copies second item to top
 */
 void OVER();

 /**
  * rotates third item to top
  */
  void ROT();

  void ALLOT();

  void STOREONHEAP();

  void CREATE();

  void CELLS();

  void INCR();

  void DECR();

  void PARTORET();

  void RETTOPAR();

  void INCRCELL();

  void DROP2();

#endif //AMFORTH_BASIC_H
