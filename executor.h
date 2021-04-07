#ifndef AMFORTH_EXECUTOR_H
#define AMFORTH_EXECUTOR_H

#include <string.h>
#include "stack.h"

extern int inCompileMode;

int execute(char* word, Stack* returnStack);

#endif //AMFORTH_EXECUTOR_H
