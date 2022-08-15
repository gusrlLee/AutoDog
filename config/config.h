#ifndef CONFIG_H
#define CONFIG_H

// Your Camera Path
#define CAMERA_PATH "/dev/video0"
#define SIMULATION_DATA_PATH "../Data/07/image_0/%06d.png"
#define FOCAL_LENGTH 707.0912

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
