
#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_icounterGet (int *value)
{
  if (value == NULL)
    return -1;

  *value = command_counter;

  return 0;
}
