#include "mySimpleComputer.h"
#include "myTerm.h"
#include "sc_variables.h"

void
printCounters (void)
{
  mt_setfgcolor (WHITE);
  mt_gotoXY (66, 5);

  int icounter_value, tacts = 0;
  int value;
  sc_regGet (FLAG_T, &value);
  if (value)
    {
      tacts++;
    }
  else
    {
      tacts = 0;
    }
  sc_icounterGet (&icounter_value);
  printf ("T: %02d   IC: +%04X", tacts, icounter_value);
  mt_setfgcolor (DEFAULT);
}
