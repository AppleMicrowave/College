#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

int
sc_memoryInit (void)
{
  for (int i = 0; i < 128; i++)
    {
      RAM[i] = 0;
    }
  return 0;
}
