#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

// usrinput
void usr_input(char *buffer, size_t sizeof_buffer, const char *prompt);
void usr_input_diy(char *usrStr, size_t sizeof_usrStr, const char *prompt);
void addCharToString(char* myString, char myChar);
int usr_input_num(double *num, const char *prompt);
double power_int(double base, int32_t exponent);
void pressEnterToContinue();
// stringtools
int existsInString(char* test, char* sample);
void strAppend(char* string1, char* string2);
void verifyMallocSuccess(void* data);

#endif
