#include "console.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "sc_variables.h"

void
printFlags ()
{
  mt_setfgcolor (WHITE);
  mt_gotoXY (95, 2);
  int value;
  sc_regGet (FLAG_P, &value);
  if (value)
    {
      printf ("P ");
    }
  else
    {
      printf ("_ ");
    }
  sc_regGet (FLAG_M, &value);
  if (value)
    {
      printf ("M ");
    }
  else
    {
      printf ("_ ");
    }
  sc_regGet (FLAG_T, &value);
  if (value)
    {
      printf ("T ");
    }
  else
    {
      printf ("_ ");
    }
  sc_regGet (FLAG_E, &value);
  if (value)
    {
      printf ("E ");
    }
  else
    {
      printf ("_ ");
    }
  sc_regGet (FLAG_0, &value);
  if (value)
    {
      printf ("0 ");
    }
  else
    {
      printf ("_ ");
    }
  mt_setfgcolor (DEFAULT);
}
