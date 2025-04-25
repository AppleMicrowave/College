#include "myReadKey.h"
#include "rk_structs.h"

int
rk_readkey (enum keys *key)
{
  char buffer[5] = "\0";
  rk_mytermregime (0, 30, 0, 0, 0);
  read (0, buffer, 5);
  rk_mytermrestore ();

  if (buffer[0] == '\033')
    {
      if (buffer[1] == '[')
        {
          switch (buffer[2])
            {
            case 'A':
              *key = UP;
              break;
            case 'B':
              *key = DOWN;
              break;
            case 'C':
              *key = RIGHT;
              break;
            case 'D':
              *key = LEFT;
              break;
            case '1':
              if (buffer[3] == '5')
                {
                  *key = F5;
                }
              else if (buffer[3] == '7')
                {
                  *key = F6;
                }
              break;
            default:
              *key = ERROR;
            }
        }
      else if (buffer[1] == '\0')
        {
          *key = EXIT;
        }
    }
  else if (buffer[0] == '\n')
    {
      *key = ENTER;
    }
  else if (buffer[0] == '\003')
    {
      *key = EXIT;
    }
  else if (buffer[0] == 'l')
    {
      *key = LOAD;
    }
  else if (buffer[0] == 's')
    {
      *key = SAVE;
    }
  else if (buffer[0] == 'r')
    {
      *key = RUN;
    }
  else if (buffer[0] == 't')
    {
      *key = STEP;
    }
  else if (buffer[0] == 'i')
    {
      *key = RESET;
    }
  else
    {
      *key = ERROR;
    }

  return 0;
}
