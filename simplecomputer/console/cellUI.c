#include "console.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "rk_structs.h"

int
cellUI (void)
{
  mt_gotoXY (63, 18);
  mt_setfgcolor (BLUE);
  mt_setbgcolor (DEFAULT);
  printf (" Номер редактируемой ячейки: %03d ", cell);
  mt_setfgcolor (DEFAULT);
  return 0;
}
