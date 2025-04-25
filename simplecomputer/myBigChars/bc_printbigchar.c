#include "myBigChars.h"
#include "myTerm.h"

int
bc_printbigchar (int *big, int x, int y, enum colors fg, enum colors bg)
{
  if (fg != DEFAULT)
    mt_setfgcolor (fg);
  if (bg != DEFAULT)
    mt_setbgcolor (bg);

  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j)
      {
        mt_gotoXY (x + i, y + j);
        int value;
        if (bc_getbigcharpos (big, i, j, &value))
          return -1;
        if (value)
          bc_printA (ACS_CKBOARD);
        else
          printf ("%c", ' ');
      }

  mt_setdefaultcolor ();
  return 0;
}
