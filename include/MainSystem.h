#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>

#include "DogStatus.h"
#include "VisualOdometry.h"
#include "Lidar.h"

class MainSystem 
{
    private:
        // true -> camera mode 
        // false -> simulation mode 
        bool system_mode = false;
        int stat;

        DogStatus *dog_status; // status save space 
        VisualOdometry *vo; // visual odometry 
        Lidar* lidar;
        
        // threads  
        static void trajectoryComputeThread(VisualOdometry* vo, DogStatus* dog_status);
        
    public:
        MainSystem(bool mode);
        void startProgram();
};

#endif // MAIN_SYSTEM_H

