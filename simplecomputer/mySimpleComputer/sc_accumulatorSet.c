#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

int
sc_accumulatorSet (int value)
{
  int min_value = -(1 << 15);
  int max_value = (1 << 15) - 1;

  if (value < min_value || value > max_value)
    return -1;

  accumulator = value;

  return 0;
}
