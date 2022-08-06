// -------------------------------------------------------------------------------
#include "DogStatus.h"

DogStatus::DogStatus() {
    is_working = false;
}

// -------------------------------------------------------------------------------
cv::Mat DogStatus::getCurrentFrame() {
    std::lock_guard<std::mutex> lock(current_frame_mutex);
    return curr_frame.clone();
}

// -------------------------------------------------------------------------------
void DogStatus::setCurrentFrame(cv::Mat current_frame) {    
    std::lock_guard<std::mutex> lock(current_frame_mutex);
    curr_frame = current_frame;
}


// -------------------------------------------------------------------------------
bool DogStatus::getSystemStatus() {
    std::lock_guard<std::mutex> lock(is_working_mutex);
    return is_working;
}

// -------------------------------------------------------------------------------
void DogStatus::setSystemStatus(bool status) {
    std::lock_guard<std::mutex> lock(is_working_mutex);
    is_working = status;
}

// -------------------------------------------------------------------------------
void DogStatus::setTrajData(std::vector<cv::Point2f> current_traj_data) { 
    std::lock_guard<std::mutex> lock(current_traj_mutex);
    this->current_traj = current_traj_data;
}

// -------------------------------------------------------------------------------
std::vector<cv::Point2f> DogStatus::getTrajData() {
    std::lock_guard<std::mutex> lock(current_traj_mutex);
    return current_traj;
}

// --------------------------------------------------------------------------------
void DogStatus::setScanData(std::vector<sl_lidar_response_measurement_node_hq_t> current_lidar_scan_data, size_t count) {
    std::lock_guard<std::mutex> lock(current_scan_data_mutex);
    this->current_scan_data = current_lidar_scan_data;

}

// -------------------------------------------------------------------------------
std::vector<sl_lidar_response_measurement_node_hq_t> DogStatus::getScanData() {
    std::lock_guard<std::mutex> lock(current_scan_data_mutex);
    return current_scan_data; 
}


  

