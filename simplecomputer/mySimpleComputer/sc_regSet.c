#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdio.h>

int
sc_regSet (int regist, int value)
{
  if (regist > 0 && regist < 6)
    {
      if (value == 1)
        {
          flag_register = flag_register | (1 << (regist - 1));
          return 0;
        }
      else if (value == 0)
        {
          flag_register = flag_register & (~(1 << (regist - 1)));
          return 0;
        }
      else
        {
          sc_regSet (FLAG_M, 1);
          return -1;
        }
    }
  else
    {
      sc_regSet (FLAG_M, 1);
      return -1;
    }
}
