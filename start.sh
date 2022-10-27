#!/bin/bash

echo "Hello Auto Dog!"

# for camera path
CAMERA_PATH="/dev/video0"
#CAMERA_PATH="../Data/turn_dataset1/%05d.png"
FOCAL_LENGTH="707.0912"

# for lidar port and baudrate 
LIDAR_PATH="/dev/ttyUSB0"
LIDAR_BAUDRATE="115200"

# for arduino port and baudrate
ARDUINO_PATH="/dev/ttyUSB1"
ARDUINO_BAUDRATE="115200"

# start command 
echo "./auto --camera-path=${CAMERA_PATH} --focal-length=${FOCAL_LENGTH} --lidar-path=${LIDAR_PATH} --lidar-baudrate=${LIDAR_BAUDRATE} --arduino-path=${ARDUINO_PATH} --arduino-baudrate=${ARDUINO_BAUDRATE}"
# for simulation
./build/Auto --camera-path=${CAMERA_PATH} --focal-length=${FOCAL_LENGTH}

# full real mode 
# ./build/Auto --camera-path=${CAMERA_PATH} --focal-length=${FOCAL_LENGTH} --lidar-path=${LIDAR_PATH} --lidar-baudrate=${LIDAR_BAUDRATE} --arduino-path=${ARDUINO_PATH} --arduino-baudrate=${ARDUINO_BAUDRATE}



