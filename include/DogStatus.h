#ifndef __DOG_STATUS__
#define __DOG_STATUS__

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class DogStatus {
    private:
        cv::Mat curr_frame;
        cv::Mat prev_frame;
        
    public:
        DogStatus();
        cv::Mat getCurrentFrame();
        void setCurrentFrame(cv::Mat current_frame);

};

#endif // __DOG_STATUS__
