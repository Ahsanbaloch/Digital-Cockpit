FROM ubuntu:latest

# Install dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    libboost-all-dev \
    qt6-base-dev \
    qt6-declarative-dev \
    qt6-serialbus-dev \
    qt6-serialport-dev \
    libgl1-mesa-dev \
    zlib1g-dev \
    libdbus-glib-1-dev \
    libdlt-dev \
    graphviz \
    asciidoc \
    doxygen \
    pkg-config \
    doxygen-gui \
    doxygen-doc \
    git \
    wget \
    unzip \
    openjdk-11-jre \
    iproute2 \
    iputils-ping \
    can-utils \
    net-tools \
    libxcb1 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-shape0 \
    libxcb-xinerama0 \
    libxkbcommon-x11-0 \
    x11-apps \
    qml6-module-qtquick-controls \
    qml6-module-qtquick \
    qml6-module-qtqml-workerscript \
    qml6-module-qtquick-templates \
    qml6-module-qtquick-layouts

# Create necessary directories
RUN mkdir -p /app/generators/commonapi_core_generator \
&& mkdir -p /app/generators/commonapi_someip_generator

# Copy the server script
COPY ./IPC_Service//Library_installation/server_script.sh /app/server_script.sh
RUN chmod +x /app/server_script.sh

COPY ./IPC_Service//Library_installation/vsomeip.json /etc/vsomeip/vsomeip.json
COPY ./IPC_Service//Library_installation/commonapi-someip.ini /etc/commonapi-someip.ini

COPY ./QT/Instrument_cluster /app/Instrument_cluster

# Copy the middleware directory
COPY ./IPC_Service//middleware /app/middleware
# Copy the Service directory
COPY ./IPC_Service//Service /app/Service

# Copy CMakeLists.txt and the source code
COPY ./IPC_Service/ /app/IPC_Serivce
COPY ./IPC_Service/CMakeLists.txt /app/CMakeLists.txt

# Add this line near the top of your Dockerfile
RUN mkdir -p /usr/local/lib/cmake


# Set working directory
WORKDIR /app

# Set environment variables for vsomeip and CommonAPI configuration
ENV VSOMEIP_CONFIGURATION=/etc/vsomeip/vsomeip.json 
ENV COMMONAPI_CONFIG=/etc/commonapi-someip.ini

# Run the server script
CMD ["./server_script.sh"]
