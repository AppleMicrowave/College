#ifndef CONSOLE_H
#define CONSOLE_H

#include "variables.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

int messageUI (char *str, enum colors color);
int boxesUI (void);
int textsUI (void);
int memoryUI (void);
int bigCharsUI (void);
int uiAdd (void);
int cellUI (void);
int miniCellUI (void);

int CU (void);
int ALU (int command, int operand);
void IRC (int signum);
void uiCommand1 (void);

#endif
