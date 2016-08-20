#!/bin/bash
#must run as root

$CONFIG_FILE = hardpass-config.sh
source $CONFIG_FILE 

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
$DIR/oled_menu "1: type passwords" "2: settings" "3: update (git)" "4: about"
menu_sel=$?

case $menu_sel in 
	1) echo "pass show ... stuff";; #TODO TODO TODO
	2) settings;;
	3) pass_update;;
	4) echo "(C) 2016 Tobias Girstmair, licensed under the GNU GPL" #TODO: should be on oled
esac


function settings {
	$DIR/oled_menu "1: English (US)" "2: German (AT)" "3: German (ND)"
	LAYOUT=$?
	$DIR/oled_menu "1: GTK (Hold)" "2: GTK (Space)" "3: Windows"
	UNICODE=$?

	sed -c -i "s/\(LAYOUT *= *\).*/\1$LAYOUT/" $CONFIG_FILE
	sed -c -i "s/\(UNICODE *= *\).*/\1$UNICODE/" $CONFIG_FILE
}

function pass_update {
	#TODO: show notificaton / msgbox on oled /TODO
	rmmod i2c-dev
	modprobe mac80211
	modprobe esp8089
	#TODO: wait for network connection /TODO
	pass git push #(necessary??)
	retval=$(pass git pull)
	case $retval in
		"Already up-to-date.") #TODO: display something on oled
		*) #TODO: display number of changes
	esac
	rmmod mac80211
	rmmod esp8089
	modprobe i2c-dev
	# TODO: display menu again
}
