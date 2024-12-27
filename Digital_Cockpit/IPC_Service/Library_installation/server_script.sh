#!/bin/bash

# Update package list
# apt-get update && apt-get install -y build-essential cmake libboost-all-dev doxygen git wget unzip net-tools iproute2 can-utils

#Clone and build vsomeip
git clone https://github.com/COVESA/vsomeip.git
cd vsomeip
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
make
make install
cd ../..

# Install CommonAPI Core
git clone https://github.com/COVESA/capicxx-core-runtime.git
cd capicxx-core-runtime
sed -i '1i#include <string>' include/CommonAPI/Types.hpp
mkdir build && cd build
cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
make install
cd ../..

# Install CommonAPI SOME/IP
git clone https://github.com/COVESA/capicxx-someip-runtime.git
cd capicxx-someip-runtime && mkdir build && cd build
cmake -D CMAKE_INSTALL_PREFIX=/usr/local -DUSE_INSTALLED_COMMONAPI=ON ..
make
make install
cd ../..

# Ensure CommonAPI-SomeIPConfig.cmake is in the correct location
SOMEIP_CONFIG_PATH=$(find /usr/local -name "CommonAPI-SomeIPConfig.cmake")
if [ -n "$SOMEIP_CONFIG_PATH" ]; then
    SOMEIP_DIR=$(dirname "$SOMEIP_CONFIG_PATH")
    mkdir -p /usr/local/lib/cmake/CommonAPI-SomeIP-3.2
    cp "$SOMEIP_DIR"/CommonAPI-SomeIPConfig.cmake /usr/local/lib/cmake/CommonAPI-SomeIP-3.2/
    cp "$SOMEIP_DIR"/CommonAPI-SomeIPConfigVersion.cmake /usr/local/lib/cmake/CommonAPI-SomeIP-3.2/
    cp "$SOMEIP_DIR"/CommonAPITargets.cmake /usr/local/lib/cmake/CommonAPI-SomeIP-3.2/
    cp "$SOMEIP_DIR"/CommonAPITargets-relwithdebinfo.cmake /usr/local/lib/cmake/CommonAPI-SomeIP-3.2/
    cp "$SOMEIP_DIR"/CommonAPI-SomeIPTargets.cmake /usr/local/lib/cmake/CommonAPI-SomeIP-3.2/
else
    echo "Error: CommonAPI-SomeIPConfig.cmake not found"
    exit 1
fi

# Verify installation and ensure CMake can find the config files
echo "Verifying the installation..."
if [ -f /usr/local/lib/cmake/CommonAPI-SomeIP-3.2/CommonAPI-SomeIPConfig.cmake ]; then
    echo "Installation of CommonAPI-SomeIP was successful."
else
    echo "Error: CommonAPI-SomeIPConfig.cmake was not found."
    exit 1
fi

if [ -f /etc/vsomeip/vsomeip.json ]; then
    echo "vsomeip configuration file found."
else
    echo "Error: vsomeip configuration file not found."
    exit 1
fi

if [ -f /etc/commonapi-someip.ini ]; then
    echo "CommonAPI configuration file found."
else
    echo "Error: CommonAPI configuration file not found."
    exit 1
fi

ldconfig


# Update the CMake module path to include /usr/local/lib/cmake/
export CMAKE_PREFIX_PATH=/usr/local:$CMAKE_PREFIX_PATH

# Build the project using cmake
echo "Building the project using cmake"
mkdir -p /app/build
cd /app/build
cmake ..
make -j$(nproc)
cd ..

# Check if the executable is built
if [ -f "/app/build/CANService" ]; then
    echo "Executable built successfully."
    # Move the executable to the main directory
    mv /app/build/CANService /app/
else
    echo "Error: Executable not found."
    exit 1
fi




if [ -f /etc/vsomeip/vsomeip.json ]; then
    echo "vsomeip configuration file found."
else
    echo "Error: vsomeip configuration file not found."
    exit 1
fi

# ip link add dev vcan0 type vcan
# if [ $? -ne 0 ]; then
#     echo "Error: Failed to add vcan0 device."
#     exit 1
# fi

# ip link set up vcan0
# if [ $? -ne 0 ]; then
#     echo "Error: Failed to set up vcan0 device."
#     exit 1
# else
#     echo "Installed successfully..."
# fi

# Setting up vcan
if ! ip link show vcan0 > /dev/null 2>&1; then
    ip link add vcan0 type vcan
    ip link set up vcan0
    echo Created vcan
else
    echo vcan interface already exists
fi

# Check for vsomeip
if [ ! -f "/usr/local/lib/libvsomeip3.so" ]; then
    echo "Error: vsomeip library not found"
    exit 1
fi

# Check for CommonAPI Core
if [ ! -f "/usr/local/lib/libCommonAPI.so" ]; then
    echo "Error: CommonAPI Core library not found"
    exit 1
fi


# Print the contents of the CommonAPI-SomeIP directory
echo "Contents of /usr/local/lib/cmake/CommonAPI-SomeIP-3.2:"
if [ -d "/usr/local/lib/cmake/CommonAPI-SomeIP-3.2" ]; then
    ls -l /usr/local/lib/cmake/CommonAPI-SomeIP-3.2
else
    echo "Error: Directory /usr/local/lib/cmake/CommonAPI-SomeIP-3.2 does not exist"
    exit 1
fi

# Print the location of the CommonAPI-SomeIP library
echo "Location of libCommonAPI-SomeIP.so:"
SOMEIP_LIB=$(find /usr/local -name "libCommonAPI-SomeIP.so")
if [ -n "$SOMEIP_LIB" ]; then
    echo "$SOMEIP_LIB"
else
    echo "Error: libCommonAPI-SomeIP.so not found"
    exit 1
fi

export QT_DEBUG_PLUGINS=1


# Build Qt application
echo "Building Qt application"
rm -rf /app/Instrument_cluster/build
mkdir -p /app/Instrument_cluster/build
cd /app/Instrument_cluster/build
cmake ..
make

# Check if the Qt executable is built
if [ -f "/app/Instrument_cluster/build/appInstrument_cluster" ]; then
    echo "Qt executable built successfully."
    # Move the executable to the main directory
    mv /app/Instrument_cluster/build/appInstrument_cluster /app/
else
    echo "Error: Qt executable not found."
    exit 1
fi



# Verify that CANService exists in the expected location
echo "Checking if CANService exists..."
if [ -f "/app/CANService" ]; then
    echo "CANService found."
    ls
else
    echo "Error: CANService not found."
    ls 
    exit 1
fi

# Verify that appInstrument_cluster exists in the expected location
echo "Checking if appInstrument_cluster exists..."
if [ -f "/app/appInstrument_cluster" ]; then
    echo "appInstrument_cluster found."
else
    echo "Error: appInstrument_cluster not found."
    exit 1
fi

# Run both CANService and Qt application
echo "Running CANService and Qt application"
if [ -f "/app/CANService" ] && [ -f "/app/appInstrument_cluster" ]; then
    # Ensure executables have execute permissions (this might not be necessary if already set)
    chmod +x /app/CANService
    chmod +x /app/appInstrument_cluster
    
    # Use full paths to avoid any ambiguity about the current working directory
    /app/CANService &
    /app/appInstrument_cluster
else
    echo "Error: Required executables not found."
    exit 1
fi


echo "Installation complete. vsomeip, CommonAPI, and code generators are now installed."
