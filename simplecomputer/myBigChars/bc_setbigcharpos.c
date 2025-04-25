#include "myBigChars.h"
#include "myTerm.h"

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if ((x < 0) || (x > 7) || (y < 0) || (y > 7))
    return -1;
  if (value)
    big[y / 4] |= (1 << (8 * (y % 4) + (7 - x)));
  else
    big[y / 4] &= ~(1 << (8 * (y % 4) + (7 - x)));

  return 0;
}
