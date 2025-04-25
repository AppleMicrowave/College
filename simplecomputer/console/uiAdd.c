#include "console.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "rk_structs.h"

int
uiAdd (void)
{
  mt_clrscr ();
  boxesUI ();
  textsUI ();
  memoryUI ();
  printFlags ();
  cellUI ();
  miniCellUI ();
  printAccumulator ();
  printCommand ();
  printCounters ();
  bigCharsUI ();
  printTerm (cell, 0, membuffer);

  if (flagUi)
    {
      uiCommand1 ();
    }

  mt_gotoXY (1, 27);
  printf ("Input:\n");
  return 0;
}
