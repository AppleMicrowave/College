#include "mySimpleComputer.h"
#include "myTerm.h"
#include "sc_variables.h"

void
printCommand (void)
{
  mt_setfgcolor (WHITE);
  int address, value;
  mt_gotoXY (93, 5);
  sc_icounterGet (&address);
  if (address >= 0 && address < 128)
    {
      if (!sc_commandValidate (RAM[address]))
        {
          printf ("! ");
          printf ("+FF: FF");
        }
      else
        {
          sc_memoryGet (address, &value);
          printf ("%03d: %d", address, RAM[address]);
        }
    }
  else
    {
      printf ("Неверный адрес команды");
    }
  mt_setfgcolor (DEFAULT);
}
