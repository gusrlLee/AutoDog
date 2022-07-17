#ifndef __MAIN_SYSTEM__
#define __MAIN_SYSTEM__

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>

#include "DogStatus.h"
#include "VisualOdometry.h"

class MainSystem {
    private:
        // false -> simulation mode 
        // true -> camera mode 
        bool system_mode = false;
        int stat;
        
        // threads  
        static void cameraCaptureThread(DogStatus* dog_status, const char* file_path);
        static void trajectoryComputeThread(VisualOdometry* vo, DogStatus* dog_status);

        DogStatus *dog_status;
        VisualOdometry *vo;
        
    public:
        MainSystem(bool mode);
        void startProgram(const char* file_path);
};

#endif // __MAIN_SYSTEM__

