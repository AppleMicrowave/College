#include "myTerm.h"

int
mt_setcursorvisible (int value)
{
  if (value == 1)
    {
      printf ("\033[?25h"); // show
    }
  else if (value == 0)
    {
      printf ("\033[?25l"); // hide
    }
  else
    {
      return -1;
    }

  return 0;
}
