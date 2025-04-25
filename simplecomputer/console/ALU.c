#include "console.h"
#include "mySimpleComputer.h"
#include "sc_variables.h"

int
ALU (int command, int operand)
{
  int value;
  int buff = sc_memoryGet (cell + 1, &value);
  if (buff == -1)
    {
      sc_regSet (FLAG_P, 1);
      return -1;
    }
  command = operand;
  switch (command)
    {
    case 0x1E:
      accumulator += value;
      if (accumulator > 32767 || accumulator < -32767)
        {
          sc_regSet (FLAG_M, 1);
          return -1;
        }
      command_counter++;
      break;
    case 0x1F:
      accumulator -= value;
      if (accumulator > 32767 || accumulator < -32767)
        {
          sc_regSet (FLAG_M, 1);
          return -1;
        }
      command_counter++;
      break;
    case 0x20:
      if (value == 0)
        {
          sc_regSet (FLAG_0, 1);
          return -1;
        }
      accumulator /= value;
      command_counter++;
      break;
    case 0x21:
      accumulator *= value;
      if (accumulator > 32767 || accumulator < -32767)
        {
          sc_regSet (FLAG_M, 1);
          return -1;
        }
      command_counter++;
      break;
    default:
      return -1;
    }
  return 0;
}
