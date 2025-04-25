#include "mySimpleComputer.h"
#include "sc_variables.h"

int
sc_commandEncode (int command, int operand, int *value)
{
  if (command > 0x7F)
    return -1;
  if (operand > 0x7F)
    return -1;

  *value = 0;

  for (int i = 0; i < 7; i++)
    {
      int bit = (operand >> i) & 1;
      *value |= (bit << i);
    }
  for (int i = 0; i < 7; i++)
    {
      int bit = (command >> i) & 1;
      *value |= (bit << (i + 7));
    }
  return 0;
}
