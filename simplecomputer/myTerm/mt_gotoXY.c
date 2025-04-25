#include "myTerm.h"

int
mt_gotoXY (int col, int row)
{
  int rows, cols;
  if (mt_getscreensize (&rows, &cols) == -1)
    return -1;
  if ((row > rows) || (row <= 0) || (col > cols) || (col <= 0))
    return -1;

  printf ("\033[%d;%dH", row, col);
  return 0;
}
