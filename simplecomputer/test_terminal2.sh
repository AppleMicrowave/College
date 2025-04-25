#!/bin/bash

enter_alt_charset_mode="\033(0"
exit_alt_charset_mode="\033(B"
acs_chars="++\054\054--..00``aaffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz{{||}}~~"
clear_screen="\033[H\033[2J"

echo -e "${clear_screen}"

echo -e "${enter_alt_charset_mode}"

start_row=10
start_col=5

echo -e "\033[${start_row};${start_col}H┌────────────────────┐"

for ((i = 1; i <= 8; i++)); do
    row=$((start_row + i))
    echo -e "\033[${row};${start_col}H│                    │"
done

echo -e "\033[$((start_row + 9));${start_col}H└────────────────────┘"

echo -e "\033[11;7H"
echo "    │      aaaaaaaa"
echo "    │      aa      "
echo "    │      aaaaaaaa"
echo "    │            aa"
echo "    │      aaaaaaaa"

echo -e "\033[19;0H"
echo -e "${exit_alt_charset_mode}"
