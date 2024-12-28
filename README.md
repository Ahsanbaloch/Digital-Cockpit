# Digital-Cockpit
The primary objective of this project is to simulate and design a comprehensive digital cockpit system that replicates a modern car's instrument cluster. The system will utilize virtual ECUs and a virtual CAN communication system to facilitate the exchange of speed data. This project is intended to provide hands-on experience with distributed embedded systems within the automotive domain.
# Goals
## Simulate Speed Sensor System
- Develop a speed feeder system capable of generating and transmitting real-time speed data, functioning as a virtual speed sensor ECU.

## Instrument Cluster Display
- Create a dynamic instrument cluster using a separate system to receive, process, and display speed data with filtering and smoothing algorithms for real-world accuracy.

## Virtual CAN Communication
- Implement a virtual Controller Area Network (CAN) to enable seamless data transfer between the speed sensor and the instrument cluster.

# Architeture of the Project
![Banner Image](https://github.com/Ahsanbaloch/Digital-Cockpit/blob/main/assets/Structure%20Cockpit.png)


# Speed Feeder

## key Features
- Real-time speed simulation with user input
- Virtual CAN communication for speed data transmission
- Console-based user interface using ncurses
- Containerized setup with Docker
- Automatic virtual CAN interface (vcan0) setup
- MISRA-compliant C++ code
## How it works
- The Speed class manages the vehicle's speed state, allowing for acceleration and braking.
- The CAN class handles communication over a virtual CAN network, formatting and sending speed data.
- The main program provides a console interface for user interaction and displays current speed.
- Speed changes are transmitted as CAN frames over the virtual network.
## Usage
To build and run the Speed Feeder:
```
docker compose build speed_feeder
docker compose run --rm -it speed_feeder
```
Once running, use the following controls:
- w: Accelerate
- space: Brake
- q: Quit the program
## Dependencies
- Ubuntu 24.04 base image
- Build essentials and CAN utilities
- ncurses for the console interface

# Instrument Cluster (SOME/IP Server and Qt Client)
## key Features
- Real-time speed simulation and display
- SOME/IP communication between components
- Qt-based graphical interface for the instrument cluster
- Containerized setup using Docker for easy deployment

## How it works
- The Speed Feeder simulates vehicle speed and sends it over a virtual CAN network.
- The SOME/IP Server (CANService) receives the CAN data and makes it available via SOME/IP.
- The Qt Client (vcan) connects to the SOME/IP Server and receives speed updates.
- The Qt application displays the speed and other vehicle information in a digital cockpit interface.
##Setup and Running
before running docker use this command in terminal
```
xhost +local:docker
```
Build and run the Instrument Cluster:
```
docker compose up --build someip_server
```
## Video demonstration

Check out the video demonstration on [LinkedIn](https://www.linkedin.com/feed/update/urn:li:ugcPost:7278751322311454720/).

