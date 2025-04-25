#include "myReadKey.h"
#include "rk_structs.h"

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios term;
  tcgetattr (0, &term);

  if (regime)
    term.c_lflag |= ICANON;
  else
    {
      term.c_lflag &= ~ICANON;
      sigint ? (term.c_lflag |= ISIG) : (term.c_lflag &= ~ISIG);
      echo ? (term.c_lflag |= ECHO) : (term.c_lflag &= ~ECHO);
      term.c_cc[VMIN] = vmin;
      term.c_cc[VTIME] = vtime;
    }

  tcsetattr (0, TCSAFLUSH, &term);
  return 0;
}
