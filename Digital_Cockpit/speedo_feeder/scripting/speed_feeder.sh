#!/bin/sh

set -e

# Display configuration
echo Using following configuration
echo VCAN_INTERFACE: "${VCAN_INTERFACE:=vcan0}"

# Setting up vcan
if ! ip link show "$VCAN_INTERFACE" > /dev/null 2>&1; then
    ip link add "$VCAN_INTERFACE" type vcan
    ip link set up "$VCAN_INTERFACE"
    echo Created vcan
else
    echo vcan interface already exists
fi

make 

./speed_feeder
