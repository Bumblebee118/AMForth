//
// Created by Alexander on 06.04.2021.
//

#ifndef AMFORTH_ERROR_H
#define AMFORTH_ERROR_H

#define ERR_UNDEFINED_WORD -1
#define ERR_STACK_UNDERFLOW -2
#define ERR_STACK_OVERFLOW -3
#define ERR_PARSING_ERROR -4
#define ERR_TOKEN_SIZE_LIMIT -5
#define ERR_INTERPRET_COMPILE_ONLY -6

void THROW();

#endif //AMFORTH_ERROR_H
