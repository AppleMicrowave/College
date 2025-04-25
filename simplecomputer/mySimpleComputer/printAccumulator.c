#include "mySimpleComputer.h"
#include "myTerm.h"
#include "sc_variables.h"

void
printAccumulator ()
{
  mt_setfgcolor (WHITE);
  mt_gotoXY (65, 2);

  int accumulator_value;
  sc_accumulatorGet (&accumulator_value);
  printf ("sc: %04d hex: 0x%X", accumulator_value, accumulator_value);
  mt_setfgcolor (DEFAULT);
}
