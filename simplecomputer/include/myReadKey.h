#ifndef RK_H
#define RK_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

enum keys
{
  UP,
  RIGHT,
  DOWN,
  LEFT,
  LOAD,
  SAVE,
  RESET,
  RUN,
  STEP,
  ENTER,
  F5,
  F6,
  EXIT,
  ERROR
};

int rk_readkey (enum keys *key);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
void rk_readvalue (void);

#endif
