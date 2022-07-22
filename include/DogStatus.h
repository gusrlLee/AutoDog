#ifndef __DOG_STATUS__
#define __DOG_STATUS__

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

class DogStatus {
    private:
        std::queue<cv::Mat> curr_frame_buffer;
        cv::Mat prev_frame;
        std::mutex current_frame_mutex;
        
        bool is_working;
        std::mutex is_working_mutex;
        
    public:
        DogStatus();

        cv::Mat getCurrentFrame();
        void setCurrentFrame(cv::Mat current_frame);

        bool getSystemStatus();
        void setSystemStatus(bool flag);
        
        void getTrajData();
        void setTrajData();

};

#endif // __DOG_STATUS__
