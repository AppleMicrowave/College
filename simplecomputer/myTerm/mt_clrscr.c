#include "myTerm.h"

int
mt_clrscr (void)
{
  printf ("\033[H\033[2J");
  return 0;
}
