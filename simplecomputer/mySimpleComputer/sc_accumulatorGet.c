#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

int
sc_accumulatorGet (int *value)
{
  if (value == NULL)
    return -1;

  *value = accumulator;

  return 0;
}
