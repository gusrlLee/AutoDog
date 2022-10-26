#include "DogStatus.h"

DogStatus::DogStatus() {
    is_working_ = false;
}

cv::Mat DogStatus::getCurrentFrame() {
    std::lock_guard<std::mutex> lock(current_frame_mutex_);
    return curr_frame_.clone();
}

cv::Mat DogStatus::getCurrentFrame(int a) {
    std::lock_guard<std::mutex> lock(current_frame_mutex_);
    return curr_frame_.clone();
}


void DogStatus::setCurrentFrame(cv::Mat current_frame) {    
    std::lock_guard<std::mutex> lock(current_frame_mutex_);
    curr_frame_ = current_frame;
}

void DogStatus::pushFrameBuffer(cv::Mat current_frame) {
    std::lock_guard<std::mutex> lock(frame_buffer_mutex_);
    frame_buffer_.push(current_frame);
}

cv::Mat DogStatus::popFrameBuffer() {
    std::lock_guard<std::mutex> lock(frame_buffer_mutex_);
    cv::Mat current_frame;
    if (!frame_buffer_.empty()) {
        current_frame = frame_buffer_.front();
        frame_buffer_.pop();
    }
    return current_frame;
}


bool DogStatus::getSystemStatus() {
    std::lock_guard<std::mutex> lock(is_working_mutex_);
    return is_working_;
}

void DogStatus::setSystemStatus(bool status) {
    std::lock_guard<std::mutex> lock(is_working_mutex_);
    is_working_ = status;
}


void DogStatus::setTrajData(std::vector<cv::Point2f> current_traj_data) { 
    std::lock_guard<std::mutex> lock(current_traj_mutex_);
    this->current_traj_ = current_traj_data;
}


void DogStatus::setCurrentLocation(cv::Point2d current_location) {
    std::lock_guard<std::mutex> lock(current_location_mutex_);
    current_location_ = current_location;
}

cv::Point2d DogStatus::getCurrentLocation() {
    std::lock_guard<std::mutex> lock(current_location_mutex_);
    return current_location_;
}


std::vector<cv::Point2f> DogStatus::getTrajData() {
    std::lock_guard<std::mutex> lock(current_traj_mutex_);
    return current_traj_;
}

void DogStatus::setScanData(std::vector<sl_lidar_response_measurement_node_hq_t> current_lidar_scan_data, size_t count) {
    std::lock_guard<std::mutex> lock(current_scan_data_mutex_);
    this->current_scan_data_ = current_lidar_scan_data;

}

std::vector<sl_lidar_response_measurement_node_hq_t> DogStatus::getScanData() {
    std::lock_guard<std::mutex> lock(current_scan_data_mutex_);
    return current_scan_data_; 
}

