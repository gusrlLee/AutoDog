#ifndef __MAIN_SYSTEM__
#define __MAIN_SYSTEM__
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class MainSystem {
    private:
        // false -> simulation mode 
        // true -> camera mode 
        bool system_mode = false;

    public:
        MainSystem(bool mode);
        void display(const char* file_path);

};

#endif // __MAIN_SYSTEM__

