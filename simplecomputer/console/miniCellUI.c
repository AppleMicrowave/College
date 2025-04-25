#include "console.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "rk_structs.h"
#include "sc_variables.h"

int
miniCellUI ()
{
  int value;
  sc_memoryGet (cell, &value);
  printDecodedCommand (value);
  return 0;
}
