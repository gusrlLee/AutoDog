#ifndef CONFIG_H
#define CONFIG_H

// Your Camera Path
#define CAMERA_PATH "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, width=(int)1280, height=(int    )720, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink"
#define REAL_FOCAL_LENGTH 1316.9918

#define SIMULATION_DATA_PATH "../Data/07/image_0/%06d.png"
#define SIMUL_FOCAL_LENGTH 707.0912

// Your lidar port in dev 
#define PORT "/dev/ttyUSB0"
#define SCALE 0.1
// screen size 
#define SCREENX 800
#define SCREENY 500
// start location 
#define STARTX 100
#define STARTY 100
// baudrate 
#define BAUDRATE 115200
// PI 
#define PI 3.14
// transform ratio
#define PIXEL_RATIO 0.01

#define _countof( _Array ) (int)(sizeof(_Array) / sizeof(_Array[0]))

#endif // CONFIG_H
