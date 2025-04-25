#include "myReadKey.h"
#include "rk_structs.h"

int
rk_mytermrestore (void)
{
  return tcsetattr (0, TCSANOW, &termTemp);
}
