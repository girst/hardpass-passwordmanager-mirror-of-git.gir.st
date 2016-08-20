#!/bin/bash

# (c) 2016  Tobias Girstmair
# traverse password store on the oled

LAYER=1 #for awk call
SELECTED=""
while true; do
sudo ./oled_menu $(pass list $SELECTED | tail -n +2|awk -F/ "{ print \$${LAYER} }" | sed 's/\.gpg\(\x1B\[[0-9]\+m\)\{0,1\}\( ->\|$\)/\1\2/g' | uniq |cut -c 1-21|xargs echo)
RETVAL=$?

NEW=$(pass list $SELECTED| tail -n +2 | awk -F/ "{ print \$${LAYER} }" |  uniq |head -n $((RETVAL)) | tail -n 1)

if [ -z "$SELECTED" ]; then
	SELECTED=$NEW
else
	SELECTED=${SELECTED}/$NEW
fi

if [[ "$SELECTED" == *.gpg ]]; then
	# is a file
	echo "Requested Password: $(echo $SELECTED|sed 's/\.gpg//g')"
	echo "Username: $(echo $NEW|sed 's/\.gpg//g')"
	# PASSWORD_STORE_GPG_OPTS="--passphrase 12345" pass show $(echo $SELECTED|sed 's/\.gpg\(\x1B\[[0-9]\+m\)\{0,1\}\( ->\|$\)/\1\2/g') | head -n 1 | xargs echo -n |sudo ./scan /dev/hidg0 2 2
	break
else
	#is a dir
	LAYER=$((LAYER+1))
	continue
fi
done
