#ifndef CHEMCOUNT_H
#define CHEMCOUNT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_CHEMSTRLEN 50

typedef struct element_tag {
    char name[4];
    float amount;
} cElement;

cElement* chemCount(char* chemCompound);
void findElements(char* chemCompound, cElement** myElements);
int elementFound(char* chemCompound, char* elemSearch, int i, int chemClength);
int isIn_cElement(char* elem, cElement* myElements);
void addToMyElements(char* elem, cElement** myElements);
float readDigits(char* chemCompound, int chemClength,int elemPos);
void printElements(cElement* myElements);

int isWrongSyntax(char* chemCompound);
#define isStrEnd(ch) (ch == '\n' || ch == EOF || ch == '\0')

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
