#include "myBigChars.h"
#include "myTerm.h"

int
bc_bigcharwrite (int fd, int *big, int count)
{
  if (write (fd, big, count * 2 * sizeof (unsigned int)))
    return -1;
  return 0;
}
