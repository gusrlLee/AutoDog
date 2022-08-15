#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>

#include "opencv2/opencv.hpp"
#include "DogStatus.h"
#include "VisualOdometry.h"
#include "config.h"

#include "rplidar.h"
#include "sl_lidar.h" 
#include "sl_lidar_driver.h"

using namespace rp::standalone::rplidar;

#define _countof( _Array ) (int)(sizeof(_Array) / sizeof(_Array[0]))

class MainSystem 
{
  public:
    MainSystem(bool mode);
    void startProgram();

  private:
    // for LiDAR 
    bool ctrl_c_pressed = false;
    IChannel* _channel;
    ILidarDriver* drv;
    sl_lidar_response_device_info_t devinfo;
    bool connectSuccess = false;
    bool checkSLAMTECLIDARHealth(ILidarDriver * drv);
    void transformTheta(const float theta, double* output_array);

    void ctrlc(int) {
        ctrl_c_pressed = true;
    }

    static inline void delay( _word_size_t ms ) { }

    // true -> Real mode 
    // false -> simulation mode 
    bool system_mode = false;
    int stat;

    DogStatus *dog_status; // status save space 
    VisualOdometry *vo; // visual odometry 
    
    // threads  
    static void trajectoryComputeThread(VisualOdometry* vo, DogStatus* dog_status);
    static void detectScanDataThread(ILidarDriver* drv, DogStatus* dog_status);
        
};

#endif // MAIN_SYSTEM_H

