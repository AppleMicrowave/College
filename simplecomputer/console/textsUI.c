#include "console.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "rk_structs.h"

int
textsUI (void)
{
  mt_gotoXY (25, 1);
  mt_setfgcolor (RED);
  printf (" Оперативная память ");
  mt_gotoXY (66, 1);
  printf (" Аккумулятор ");
  mt_gotoXY (65, 4);
  printf (" Счётчик команд ");
  mt_gotoXY (93, 4);
  printf (" Команда ");
  mt_gotoXY (91, 1);
  printf (" Регистр флагов ");
  mt_gotoXY (70, 7);
  mt_setbgcolor (WHITE);
  printf (" Редактируемая ячейка (увеличено) ");
  mt_gotoXY (20, 16);
  printf (" Редактируемая ячейка (формат) ");

  mt_setbgcolor (WHITE);
  mt_setfgcolor (GREEN);
  mt_gotoXY (23, 20);
  printf (" Кеш процессора ");

  mt_gotoXY (73, 20);
  printf (" IN-OUT ");

  mt_gotoXY (95, 20);

  printf (" Клавиши ");
  mt_setfgcolor (WHITE);
  mt_setbgcolor (DEFAULT);

  mt_gotoXY (85, 21);
  printf ("l - load");
  mt_gotoXY (95, 21);
  printf ("s - save");
  mt_gotoXY (105, 21);
  printf ("i - reset");
  mt_gotoXY (85, 22);
  printf ("r  - run");
  mt_gotoXY (95, 22);
  printf ("t  - step");
  mt_gotoXY (85, 23);
  printf ("ESC - выход");
  mt_gotoXY (85, 24);
  printf ("F5 - accumulator");
  mt_gotoXY (85, 25);
  printf ("F6 - instruction counter");
  mt_setfgcolor (DEFAULT);
  return 0;
}
