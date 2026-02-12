#ifndef SCANNERFUNC_H
#define SCANNERFUNC_H

#include <stdbool.h>
#include "token.h"

int scanFile(bool parsing);
int printOuptut(enum yytokentype token, char* text, bool parsing);
char * beautifyString(char* str);
char * beautifyChar(char* str);

#endif