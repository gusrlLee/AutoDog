#!/bin/bash

echo "Hello Auto Dog!"

# for camera path
CAMERA_PATH="/dev/video0"
FOCAL_LENGTH="707.0912"

# for lidar port and baudrate 
LIDAR_PATH="/dev/ttyUSB0"
LIDAR_BAUDRATE="115200"

# for arduino port and baudrate
ARDUINO_PATH="/dev/ttyUSB1"
ARDUINO_BAUDRATE="115200"

# start command 
echo "./auto --camera-path=${CAMERA_PATH} --focal-length=${FOCAL_LENGTH} --lidar-path=${LIDAR_PATH} --lidar-baudrate=${LIDAR_BAUDRATE} --arduino-path=${ARDUINO_PATH} --arduino-baudrate=${ARDUINO_BAUDRATE}"
./auto --camera-path=${CAMERA_PATH} --focal-length=${FOCAL_LENGTH} --lidar-path=${LIDAR_PATH} --lidar-baudrate=${LIDAR_BAUDRATE} --arduino-path=${ARDUINO_PATH} --arduino-baudrate=${ARDUINO_BAUDRATE}



