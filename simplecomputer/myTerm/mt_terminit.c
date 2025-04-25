#include "../include/myTerm.h"

void
mt_termInit (void)
{
  term_history.index = -1;

  for (int i = 0; i < HISTORY_SIZE; ++i)
    {
      mt_termEnqueue (0, 0);
    }
}
