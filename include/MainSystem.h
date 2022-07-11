#ifndef __MAIN_SYSTEM__
#define __MAIN_SYSTEM__

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#include "DogStatus.h"

class MainSystem {
    public:
        MainSystem();
        ~MainSystem();
        int startCameraMode(const char* video_path);

};

#endif // __MAIN_SYSTEM__
