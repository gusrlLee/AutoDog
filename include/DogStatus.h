#ifndef DOG_STATUS_H
#define DOG_STATUS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
// for lidar 
#include "rplidar.h"
#include "sl_lidar.h" 
#include "sl_lidar_driver.h"

class DogStatus {
    private:
        cv::Mat curr_frame;
        cv::Mat prev_frame;
        std::mutex current_frame_mutex;
        
        bool is_working;
        std::mutex is_working_mutex;

        std::mutex current_traj_mutex;
        std::vector<cv::Point2f> current_traj;

        std::mutex current_scan_data_mutex;
        std::vector<sl_lidar_response_measurement_node_hq_t> current_scan_data;

        
    public:
        DogStatus();

        cv::Mat getCurrentFrame();
        void setCurrentFrame(cv::Mat current_frame);

        bool getSystemStatus();
        void setSystemStatus(bool flag);
        
        // Trajectory data
        void setTrajData(std::vector<cv::Point2f> current_traj_data);
        std::vector<cv::Point2f> getTrajData();

        // LiDAR data
        void setScanData(std::vector<sl_lidar_response_measurement_node_hq_t> current_lidar_scan_data, size_t count);
        std::vector<sl_lidar_response_measurement_node_hq_t> getScanData();

};

#endif // DOG_STATUS_H
