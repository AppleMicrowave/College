#include "myTerm.h"

int
mt_delline ()
{
  printf ("\033[M");
  return 0;
}
