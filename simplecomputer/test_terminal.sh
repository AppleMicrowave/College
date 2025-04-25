#!/bin/bash

# clear_screen=\E[H\E[J
# cursor_address=\E[%i%p1%d;%p2%dH
# set_a_background=\E[4%p1%dm
# set_a_foreground=\E[3%p1%dm
# cursor_invisible=\E[?25l\E[?1c cursor_visible=\E[?25h\E[?8c
# delete_line=\E[M

#Очистка экрана
echo -e "\E[H\E[J"

# Вывод имени красными буквами на черном фоне в пятой строке, начиная с 10 символа
echo -e "\E[5;10H\E[40;31mMichael\E[0m"

# Вывод группы зеленым цветом на белом фоне в шестой строке, начиная с 8 символа
echo -e "\E[6;8H\E[47;32mIP-216\E[0m"

# Перемещение курсора в 10 строку, 1 символ и возврат настроек цвета по умолчанию
echo -e "\E[10;1H\E[m"