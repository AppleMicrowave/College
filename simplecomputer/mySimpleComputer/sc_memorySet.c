#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

int
sc_memorySet (int address, int value)
{
  if ((address < 0 || address > 128) || (value < 0 || value > 65535))
    {
      sc_regSet (FLAG_P, 1);
      printf ("OUT_OF_MEMORY_BOUNDS, address: %x\n", address);
      return -1;
    }
  RAM[address] = value;
  return 0;
}
