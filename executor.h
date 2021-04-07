#ifndef AMFORTH_EXECUTOR_H
#define AMFORTH_EXECUTOR_H

#include "stack.h"
#include "dict.h"

int execute(char* word, Dict* dict, Stack* parameterStack, Stack* returnStack);

#endif //AMFORTH_EXECUTOR_H
