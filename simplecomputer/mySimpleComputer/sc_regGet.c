#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

int
sc_regGet (int regist, int *value)
{
  if (regist > 0 && regist < 6)
    {
      *value = (flag_register >> (regist - 1)) & 0x1;
      return 0;
    }
  else
    {
      sc_regSet (FLAG_E, 4);
      return -1;
    }
}
