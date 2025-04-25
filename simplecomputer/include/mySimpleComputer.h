#ifndef SC_H
#define SC_H

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FLAG_P 1 // out of memory
#define FLAG_M 2 // overflow
#define FLAG_T 3 // ignoring tact pulses
#define FLAG_E 4 // incorrect command
#define FLAG_0 5 // division by zero

int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);

int sc_regInit (void);
int sc_regSet (int regist, int value);
int sc_regGet (int regist, int *value);

int sc_commandEncode (int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandValidate (int command);

int sc_accumulatorInit (void);
int sc_accumulatorGet (int *value);
int sc_accumulatorSet (int value);

int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_icounterGet (int *value);

void printCell (void);
void printFlags (void);
void printDecodedCommand (int value);
void printAccumulator (void);
void printCounters (void);

#endif
