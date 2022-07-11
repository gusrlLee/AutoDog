#ifndef __DOG_STATUS__
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

class DogStatus {
    private:
        cv::Mat current_frame;

    public:
        DogStatus();
        cv::Mat getCurrentFrame();
        cv::Mat setCurrentFrame(cv::Mat current_frame);
};


#endif
