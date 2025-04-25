#include "../include/myTerm.h"

void
mt_termDequeue (cell_history_item_t *history)
{
  int i;
  int j;

  for (i = 0, j = term_history.index; i < HISTORY_SIZE;
       ++i, j = (j - 1 + HISTORY_SIZE) % HISTORY_SIZE)
    {
      history[i] = term_history.history[j];
    }
}
