#ifndef DOG_STATUS_H
#define DOG_STATUS_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

class DogStatus {
    private:
        cv::Mat curr_frame;
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

#endif // DOG_STATUS_H
