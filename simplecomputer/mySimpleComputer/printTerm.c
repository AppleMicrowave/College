#include "mySimpleComputer.h"
#include "myTerm.h"
#include "sc_variables.h"

void
printTerm (void)
{
  int address = 0;
  int input = 0;
  int data = 0;

  int sign = 0;
  int command = 0;
  int operand = 0;

  cell_history_item_t history[HISTORY_SIZE];

  mt_termDequeue (history);

  for (int i = 0; i < HISTORY_SIZE; ++i)
    {
      address = history[i].address;
      input = history[i].input_type;
      data = history[i].data;

      sc_commandDecode (data, &sign, &command, &operand);

      mt_gotoXY (72, 21 + i);

      printf ("%02X%c %c%02X%02X", address, input ? '<' : '>',
              sign ? '-' : '+', command, operand);
    }
}
