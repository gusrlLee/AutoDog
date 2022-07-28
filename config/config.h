#ifndef CONFIG_H
#define CONFIG_H

#define _countof( _Array ) (int)(sizeof(_Array) / sizeof(_Array[0]))
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
#define PIXEL_RATIO 0.1

#endif // CONFIG_H
