#!/bin/sh
insmod /opt/brcmutil.ko && insmod /opt/brcmfmac.ko

sleep 2

#ifconfig wlan0 up
ip link set wlan0 up

sleep 1
wpa_supplicant -Dnl80211 -iwlan0 -c/opt/wpa_supplicant.conf -B

wpa_cli_status()
{
    case $1 in
        COMPLETED)
            udhcpc -i wlan0
            exit 0
            ;;
        SCANNING)
            ;;
        ASSOCIATING)
            ;;
        4WAY_HANDSHAKE)
            ;;
        DISCONNECTED)
            ;;
        INACTIVE)
            ;;
        *)
            echo "[$1]"
            echo "No find wpa_supplicant server!"
            echo "start wpa_supplicant"
            wpa_supplicant -Dnl80211 -iwlan0 -c/opt/wpa_supplicant.conf -B
            ;;
    esac
}


while true
do
    sleep 10
    wpa_state=`wpa_cli -iwlan0 status | grep wpa_state | awk -F= '{printf $2}'`
    wpa_cli_status $wpa_state
done

