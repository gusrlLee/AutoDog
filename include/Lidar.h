#ifndef LIDAR_H
#define LIDAR_H

#include <stdio.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>

#include "config.h"
#include "opencv2/opencv.hpp"

#include <rplidar.h>
#include "sl_lidar.h" 
#include "sl_lidar_driver.h"

using namespace rp::standalone::rplidar;

class Lidar 
{
    public:
        Lidar();

    private:
        bool ctrl_c_pressed = false;

        IChannel* _channel;
        sl_result     op_result;
        ILidarDriver * drv;
        sl_lidar_response_device_info_t devinfo;
        bool connectSuccess = false;

        bool checkSLAMTECLIDARHealth(ILidarDriver * drv);
        void ctrlc(int) {
            ctrl_c_pressed = true;
        }

        static inline void delay( _word_size_t ms ) { }

};
#endif // LIDAR_H