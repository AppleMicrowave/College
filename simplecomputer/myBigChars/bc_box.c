#include "myBigChars.h"
#include "myTerm.h"

int
bc_box (int x, int y, int width, int height)
{
  int rows, cols;
  mt_getscreensize (&rows, &cols);
  if ((x <= 0) || (y <= 0) || (x + width - 1 > cols) || (y + height - 1 > rows)
      || (width <= 1) || (height <= 1))
    return -1;

  mt_gotoXY (x, y);
  bc_printA ((char)ACS_ULCORNER);
  mt_gotoXY (x + width - 1, y);
  bc_printA ((char)ACS_URCORNER);
  mt_gotoXY (x + width - 1, y + height - 1);
  bc_printA ((char)ACS_LRCORNER);
  mt_gotoXY (x, y + height - 1);
  bc_printA ((char)ACS_LLCORNER);

  /* Горизонтальные линии */
  for (int i = 1; i < width - 1; ++i)
    {
      // верхняя
      mt_gotoXY (x + i, y);
      bc_printA ((char)ACS_HLINE);
      // нижняя
      mt_gotoXY (x + i, y + height - 1);
      bc_printA ((char)ACS_HLINE);
    }

  /* Вертикальные линии */
  for (int i = 1; i < height - 1; ++i)
    {
      // верхняя
      mt_gotoXY (x, y + i);
      bc_printA ((char)ACS_VLINE);
      // нижняя
      mt_gotoXY (x + width - 1, y + i);
      bc_printA ((char)ACS_VLINE);
    }
  return 0;
}
