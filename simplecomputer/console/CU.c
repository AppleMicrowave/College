#include "console.h"
#include "sc_variables.h"

int
CU (void)
{
  int sign, operand, command, value, InputValue, valueAc;
  flagUi = false;

  sc_memoryGet (command_counter, &value);
  if (sc_commandDecode (value, &sign, &command, &operand) == -1)
    {
      sc_regSet (FLAG_E, 1);
      return -1;
    }
  if (operand >= 0x1E && operand <= 0x21) // поставил операнд вместо команд
    {
      return ALU (command, operand) == 0 ? 0 : -1;
    }

  switch (operand)
    {
    case 0x0:
      command_counter++;
      break;
    case 0x1:
      flagUi = true;
      command_counter++;
      break;
    case 0xA:
      alarm (0);
      rk_mytermregime (1, 1, 1, 1, 1);
      printf ("[Enter data in %d cell] ", cell);
      scanf ("%d", &InputValue);

      rk_mytermregime (0, 0, 1, 0, 1);
      if (sc_memorySet (cell, InputValue) == -1)
        {
          sc_regSet (FLAG_P, 1);
          return -1;
        }
      mt_termEnqueue (cell, 1);

      printTerm (command_counter, 1, membuffer);
      command_counter++;
      break;
    case 0xB:
      if (sc_memoryGet (operand, &value) == -1)
        {
          sc_regSet (FLAG_P, 1);
          return -1;
        }
      printf ("%X", value);
      membuffer[3].addr = operand;
      membuffer[3].buf = value;

      printTerm (command_counter, 0, membuffer);
      command_counter++;
      break;
    case 0x14:
      if (sc_memoryGet (cell + 1, &value))
        {
          return -1;
        }

      command_counter++;
      accumulator = value;

      break;
    case 0x15:
      if (sc_memorySet (operand, accumulator) == -1)
        {
          sc_regSet (FLAG_P, 1);
          return -1;
        }
      command_counter++;
      break;
    case 0x28:
      command_counter = operand - 1;
      command_counter++;
      break;
    case 0x29:
      if (accumulator < 0)
        {
          command_counter = operand - 1;
        }
      command_counter++;
      break;
    case 0x2A:
      if (accumulator == 0)
        {
          command_counter = operand - 1;
        }
      command_counter++;
      break;
    case 0x2B:
      return -1;
      break;
    case 0x3A:
      break;
    case 0x37:
      if (accumulator > 0)
        {
          command_counter = operand - 1;
        }
      command_counter++;
      break;
    case 0x42:
      if (sc_memoryGet (operand, &value) == -1)
        {
          sc_regSet (FLAG_P, 1);
          return -1;
        }
      if (sc_memoryGet (accumulator, &valueAc) == -1)
        {
          sc_regSet (FLAG_P, 1);
          return -1;
        }
      accumulator -= valueAc;
      command_counter++;
      break;
    default:
      if (ALU (command, operand))
        {
          command_counter++;
          return -1;
        }
    }
  return 0;
}