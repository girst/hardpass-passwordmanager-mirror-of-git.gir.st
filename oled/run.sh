#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
sudo $DIR/oled_menu "1: Type Password" "`echo -ne "2: Type User \x1a Pass"`" "`echo -ne "3: Type User \x1a Pass \x19"`" "4: Type Username" "5: Display Password" "6: Display everything" "7: Set Layout" "8: Set Unicode" "9: Modify pass Entry"


