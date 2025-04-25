#include "myReadKey.h"
#include "variables.h"

void
rk_readvalue (void)
{
  char buffer[10] = { 0 };
  int number;

  read (0, buffer, sizeof (buffer));

  fflush (0);

  if (buffer[0] != '+' && buffer[0] != '-')
    {
      write (STDOUT_FILENO, "Wrong input", 11);
      return;
    }

  number = (int)strtol (&buffer[1], NULL, 16);

  if (number > 0x3FFF)
    {
      write (STDOUT_FILENO, "Incorrect size of value", 23);
      return;
    }

  if (buffer[0] == '-')
    {
      number = number | 0x4000;
    }

  sc_memorySet (cell, number);
}
