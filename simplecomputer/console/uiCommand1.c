#include "console.h"

void
uiCommand1 (void)
{
  mt_gotoXY (1, 28);
  mt_setbgcolor (BLUE);
  mt_setfgcolor (WHITE);
  mt_setbgcolor (DEFAULT);
  printf ("Gorbunov Michail Sergeevich, IP-216");
}
