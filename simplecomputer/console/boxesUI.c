#include "console.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "rk_structs.h"

int
boxesUI (void)
{
  if (bc_box (1, 1, 61, 15)) // memory
    return -1;
  if (bc_box (62, 1, 27, 3)) // accumulator
    return -1;
  if (bc_box (62, 4, 27, 3)) // counter
    return -1;
  if (bc_box (89, 4, 27, 3)) // operation
    return -1;
  if (bc_box (89, 1, 27, 3)) // flags
    return -1;
  if (bc_box (62, 7, 54, 13)) // bigChars
    return -1;
  if (bc_box (84, 20, 32, 7)) // keys
    return -1;
  if (bc_box (1, 16, 61, 4)) //  bigChar mini
    return -1;
  if (bc_box (1, 20, 69, 7)) //  cashe
    return -1;
  if (bc_box (70, 20, 14, 7)) //  In-Out
    return -1;

  return 0;
}