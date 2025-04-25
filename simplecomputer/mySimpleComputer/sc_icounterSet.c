#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_icounterSet (int value)
{
  int min_value = -(1 << 7);
  int max_value = (1 << 7) - 1;

  if (value < min_value || value > max_value)
    return -1;

  command_counter = value;

  return 0;
}
