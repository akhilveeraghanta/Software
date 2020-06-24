#!/bin/bash
# At the time of creating this script, we have team members with enp3s0f1,
# wlp3s0, wlp7s0, eth1, eth0 and a plethora of other network interfaces 
#
# This script will create two virtual interfaces tbots_wifi and tbots_eth
# and then bridge those with the appropriate physical interfaces on the users
# system.
#
# This script can be rerun to reconfigure the interfaces.
echo "================================================================"
echo " Networking Interface Setup"
echo "================================================================"

# get the "suggested" interface(s). The first interface is usually the correct
# one but we provide the option to select other interfaces, which is useful for VM users
SUGGESTED_INTERFACE=$(route | grep '^default' | grep -o '[^ ]*$')

PS3="Suggested interfaces(s):
$SUGGESTED_INTERFACE
> Select wifi interface (input 0 to skip): "

# remove previous profile if it exists
rm ../src/.tbots_network_profile 2> /dev/null

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
            echo "TBOTS_WIFI_INTERFACE=$INTERFACE" >> ~/.profile
            echo "> WiFi Interface Configured"
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
            echo "TBOTS_ETHERNET_INTERFACE=$INTERFACE" >> ~/.profile
            echo "> Ethernet Interface Configured"
            break
            ;;
    esac
done

echo "Loading Configuration..."
source ~/.profile && echo "Done"
