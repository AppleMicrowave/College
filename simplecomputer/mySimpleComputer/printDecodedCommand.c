#include "mySimpleComputer.h"
#include "myTerm.h"
#include "sc_variables.h"

void
printDecodedCommand (int value)
{
  mt_gotoXY (2, 18);
  mt_setfgcolor (WHITE);
  value &= 0x3FFF;
  printf ("dec: %d | oct: %o | hex: %X | bin: ", value, value, value);
  for (int i = 15; i >= 0; i--)
    {
      printf ("%d", (value >> i) & 1);
    }
  mt_setfgcolor (DEFAULT);
}
