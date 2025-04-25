#include "myBigChars.h"
#include "myTerm.h"

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if ((x < 0) || (x > 7) || (y < 0) || (y > 7))
    return -1;
  if (big[y / 4] & (1 << (8 * (y % 4) + (7 - x))))
    *value = 1;
  else
    *value = 0;
  return 0;
}
