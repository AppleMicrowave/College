#include "console.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "rk_structs.h"
#include "sc_variables.h"

void
IRC (int signum)
{
  switch (signum)
    {
    case SIGALRM:
      {
        int flag_clock_pulses_ignore;

        sc_regGet (FLAG_T, &flag_clock_pulses_ignore);

        if (flag_clock_pulses_ignore == 1)
          {
            return;
          }

        sc_icounterGet (&cell);
        uiAdd ();
        if (CU ())
          {
            sc_regSet (FLAG_T, 1);
            uiAdd ();
            alarm (0);
          }
        else
          {
            alarm (1);
          }
        rk_mytermregime (0, 1, 1, 0, 0);
        break;
      }

    case SIGUSR1:
      alarm (0);
      command_counter = 0;
      rk_mytermsave ();
      sc_icounterInit ();
      sc_memoryInit ();
      // sc_accumulatorInit ();
      accumulator &= (1 << 14);
      sc_regInit ();
      sc_regSet (FLAG_T, 1);
      break;
    default:
      break;
    }
}
