#include "console.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "rk_structs.h"

int
messageUI (char *str, enum colors color)
{
  printf ("\033[38;5;%dm%s\033[0m", color, str);
  return 0;
}
