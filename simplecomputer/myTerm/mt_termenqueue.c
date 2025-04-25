#include "../include/myTerm.h"

#include "../include/mySimpleComputer.h"

void
mt_termEnqueue (int address, int input)
{
  int data;
  sc_memoryGet (address, &data);

  term_history.index = (term_history.index + 1) % HISTORY_SIZE;

  term_history.history[term_history.index].address = address;
  term_history.history[term_history.index].input_type = input;
  term_history.history[term_history.index].data = data;
}
