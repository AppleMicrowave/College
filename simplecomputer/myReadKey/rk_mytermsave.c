#include "myReadKey.h"
#include "rk_structs.h"

int
rk_mytermsave (void)
{
  if (tcgetattr (0, &termTemp))
    return -1;
  return 0;
}
