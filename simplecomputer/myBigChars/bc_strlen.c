#include "myBigChars.h"
#include <stddef.h>

int
bc_strlen (char *str)
{
  if (str == NULL)
    return 0;

  int length = 0;
  while (*str)
    {
      if ((*str & 0xC0) != 0x80)
        length++;
      str++;
    }
  return length;
}
