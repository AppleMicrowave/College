#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

int
sc_memoryGet (int address, int *value)
{
  int index = RAM[address];
  if (address < 0 || address > 128)
    {
      sc_regSet (FLAG_P, 1);
      return -1;
    }
  else
    {
      *value = index;
    }
  return 0;
}
