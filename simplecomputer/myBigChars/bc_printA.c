#include "myBigChars.h"
#include "myTerm.h"

int
bc_printA (char str)
{
  printf ("\033(0%c\033(B", str);
  return 0;
}
