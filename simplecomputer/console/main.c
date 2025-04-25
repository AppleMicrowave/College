#include "console.h"
#include "variables.h"
#include <fcntl.h>
#include <unistd.h>

int
main (void)
{
  int value;

  if (!isatty (fileno (stdout)))
    {
      fprintf (stderr, "Launch");
      return 1;
    }

  int col = 0, row = 0;
  mt_getscreensize (&col, &row);
  if (col < 20 || row < 30)
    {
      fprintf (stderr, "The terminal screen is too small");
      return 1;
    }
  rk_mytermsave ();
  sc_memoryInit ();
  sc_regInit ();
  sc_icounterInit ();
  sc_accumulatorInit ();

  sc_regSet (FLAG_T, 1);
  command_counter = 0;
  int buffer, ignoringImp, segmentationFault, incorrectCom, devZero;
  enum keys key;
  char name[20];
  char filename[128];
  signal (SIGALRM, IRC);
  signal (SIGUSR1, IRC);
  uiAdd ();
  do
    {
      sc_regGet (FLAG_T, &ignoringImp);
      uiAdd ();
      rk_readkey (&key);
      if (ignoringImp)
        {
          sc_regGet (FLAG_0, &devZero);
          sc_regGet (FLAG_P, &segmentationFault);
          sc_regGet (FLAG_E, &incorrectCom);
          if (devZero || segmentationFault || incorrectCom)
            {
              switch (key)
                {
                case RUN:
                  uiAdd ();
                  printf ("Input file name for load: ");
                  scanf ("%s", filename);
                  filename[strlen (filename) - 1] = '\0';
                  if (sc_memoryLoad (filename))
                    {
                      messageUI ((char *)"Failed to load memory", RED);
                      break;
                    }
                  else
                    messageUI ((char *)"Successful load", GREEN);
                  break;
                case SAVE:
                  printf ("Input file name for save > ");
                  scanf ("%s", filename);
                  // filename[strlen (filename) - 1] = '\0';
                  if (sc_memorySave (filename))
                    {
                      messageUI ((char *)"Failed to save memory", RED);
                      break;
                    }
                  else
                    messageUI ((char *)"Successful save", GREEN);
                  break;
                case RESET:
                  raise (SIGUSR1);
                  break;
                }
            }
          else
            {
              // tacts++;
              switch (key)
                {
                case UP:
                  if (cell < 128)
                    {
                      if (cell <= 9)
                        {
                          cell = 120 + cell;
                        }
                      else
                        {
                          cell -= 10;
                        }
                      if (cell == 128 || cell == 129)
                        {
                          cell -= 10;
                        }
                    }
                  break;
                case DOWN:
                  if (cell < 128)
                    {
                      if (cell >= 120)
                        {
                          cell = cell - 120;
                        }
                      else
                        {
                          cell += 10;
                        }
                      if (cell == 128 || cell == 129)
                        {
                          cell = cell - 120;
                        }
                    }
                  break;
                case LEFT:
                  if (cell < 128)
                    {
                      if (!(cell % 10))
                        {
                          cell += 9;
                        }
                      else
                        {
                          cell--;
                        }
                    }

                  if (cell == 128 || cell == 129)
                    {
                      cell -= 2;
                    }
                  break;
                case RIGHT:
                  if (cell < 128)
                    {
                      if (!((cell + 1) % 10))
                        {
                          cell -= 9;
                        }
                      else
                        {
                          cell++;
                        }
                    }

                  if (cell == 128 || cell == 129)
                    {
                      cell -= 8;
                    }
                  break;
                case SAVE:
                  printf ("Input file name for save > ");
                  scanf ("%s", filename);
                  // filename[strlen (filename) - 1] = '\0';
                  if (sc_memorySave (filename))
                    {
                      messageUI ((char *)"Failed to save memory", RED);
                      break;
                    }
                  else
                    messageUI ((char *)"Successful save", GREEN);

                  break;
                case LOAD:
                  printf ("Input file name for load: ");
                  scanf ("%s", filename);
                  // filename[strlen (filename) - 1] = '\0';
                  if (sc_memoryLoad (filename))
                    {
                      messageUI ((char *)"Failed to load memory", RED);
                      break;
                    }
                  else
                    messageUI ((char *)"Successful load", GREEN);
                  break;
                case RUN:
                  sc_regInit ();
                  sc_regSet (FLAG_T, 0);
                  raise (SIGALRM);
                  // printTerm (cell, 1, membuffer);
                  break;
                case STEP:
                  sc_icounterGet (&cell);
                  uiAdd ();
                  // printTerm (cell, 1, membuffer);
                  CU ();
                  break;
                case RESET:
                  sc_memoryInit ();
                  sc_accumulatorInit ();
                  sc_icounterInit ();
                  raise (SIGUSR1);
                  break;
                case ENTER:
                  printf ("Set the value of the cell under the number "
                          "\033[38;5;%dm0x%02X\033[0m\n",
                          SOFT_GREEN, cell);
                  printf ("Enter value in \033[38;5;%dmHEX\033[0m format > ",
                          PEACH);
                  rk_mytermregime (1, 30, 0, 0, 0);
                  rk_readvalue ();
                  mt_termEnqueue (cell, 1);
                  break;
                case F5:
                  printf ("Set accumulator: ");
                  scanf ("%d", &accumulator);
                  if (accumulator > 32767 || accumulator < -32767)
                    {
                      accumulator = 0;
                      sc_regSet (FLAG_M, 1);
                    }
                  break;
                case F6:
                  printf ("Set instruction counter: ");
                  scanf ("%d", &command_counter);
                  if (command_counter < 0 || command_counter > 128)
                    {
                      sc_regSet (FLAG_M, 1);
                      command_counter = cell;
                    }
                  cell = command_counter;
                  break;
                }
            }
        }
      else
        {
          if (key == RESET)
            {
              raise (SIGUSR1);
            }
        }
    }
  while (key != EXIT);
  printf ("Execute successfully.\n");
  return 0;
}
