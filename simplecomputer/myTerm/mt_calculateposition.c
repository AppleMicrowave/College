#include "../include/myTerm.h"

void
mt_calculatePosition (int address, int element_length, int ammount_per_row,
                      int top_padding, int left_padding)
{
  const int terminal_offset = 1;

  int row = terminal_offset + top_padding + (address / ammount_per_row);
  int column = terminal_offset + left_padding
               + (address % ammount_per_row) * element_length;

  mt_gotoXY (column, row);
}
