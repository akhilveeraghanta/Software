#!/bin/bash
# At the time of creating this script, we have team members with enp3s0f1,
# wlp3s0, wlp7s0, eth1, eth0 and a plethora of other network interfaces 
#
# This script will prompt to select the interfaces to use for tbots networking
# This script can be rerun to reconfigure the interfaces.
echo "================================================================"
echo " Networking Interface Setup"
echo "================================================================"

# get the "suggested" interface(s). The first interface is usually the correct
# one but we provide the option to select other interfaces, which is useful for VM users
SUGGESTED_INTERFACES=$(route | grep '^default' | grep -o '[^ ]*$')

PS3="Suggested interfaces(s):
$SUGGESTED_INTERFACES
> Select wifi interface (input 0 to skip): "

echo "> Configure WiFi interface"

select INTERFACE in $(ls /sys/class/net);
do
    case $INTERFACE in
        "")
            echo "WiFi interface not configured"
            break
            ;;
        *)
            echo "> Selected interface $INTERFACE ($REPLY)"
            echo "export TBOTS_WIFI_INTERFACE=$INTERFACE" >> ~/.profile
            source ~/.profile && echo "> WiFi Interface Configured"
            break
            ;;
    esac
done

PS3="> Select ethernet interface (input 0 to skip): "

echo "> Configure Ethernet interface"
select INTERFACE in $(ls /sys/class/net);
do
    case $INTERFACE in
        "")
            echo "Ethernet interface not configured"
            break
            ;;
        *)
            echo "> Selected interface $INTERFACE ($REPLY)"
            echo "export TBOTS_ETHERNET_INTERFACE=$INTERFACE" >> ~/.profile
            source ~/.profile && echo "> Ethernet Interface Configured"
            break
            ;;
    esac
done

echo "================================================================"
echo "Done. Please run source ~/.profile or restart all shell sessions"
echo "Be sure to cleanup duplicate TBOTS_INTERFACE entries in ~/.profile 
if this script has been run more than once"
echo "================================================================"
