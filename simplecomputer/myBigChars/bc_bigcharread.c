#include "myBigChars.h"
#include "myTerm.h"

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  *count = 0;
  for (int i = 0; i < need_count * 2; ++i)
    {
      if (read (fd, &big[i], sizeof (unsigned int)) == -1)
        return -1;
      if (!((i + 1) % 2))
        (*count)++;
    }
  return 0;
}
