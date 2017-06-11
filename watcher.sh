#!/bin/bash

################################################################################

__default_pattern='0,500,3,255'

################################################################################

__notify () {

case "${1}" in

################################################################################

    "Zenity notification" | "test")
        __pattern="0,250,1,255-1,250,1,255-2,250,1,255"
        ;;
    
    "VLC media player")
        __pattern="1,1000,2,255"
        ;;
    
################################################################################
    
    *)
        __pattern="${__default_pattern}"
        ;;

esac

echo -n "${__pattern}-"

}

if ! [ -z "${1}" ]; then
    __interface="${1}"
else
    __candidates="$(ls /dev/ | grep USB | sed 's#^#/dev/#')"
    __interface="$(head -n 1 <<< "${__candidates}")"
    if [ "$(wc -l <<< "${__candidates}")" -gt 1 ]; then
        echo "More than one possible option found, proceeding with '${__interface}"
    fi
fi

if ! [ -e "${__interface}" ]; then
    echo "Interface '${__interface}' unavailable"
fi

stty -F "${__interface}" cs8 9600 || exit

dbus-monitor "interface='org.freedesktop.Notifications',member='Notify'" | grep --line-buffered "member=Notify\|string" | sed -un '/^method/{n;p}' | sed -u 's/.*"\(.*\)"/\1/' | while read -r __line; do
    __notify "${__line}"
done | tee "${__interface}" | tr '-' '\n'

exit
