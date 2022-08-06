/**
 * @file DogStatus.cpp
 * @author gusrlLee (gusrlLee@github.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
// -------------------------------------------------------------------------------
#include "DogStatus.h"

/**
 * @brief Construct a new Dog Status:: Dog Status object
 * 
 */
DogStatus::DogStatus() {
    is_working = false;
}

/**
 * @brief 현재 Dog Status에 저장 된 frame을 얻어 옴.
 * 
 * @return cv::Mat : current_frame 
 */
cv::Mat DogStatus::getCurrentFrame() {
    std::lock_guard<std::mutex> lock(current_frame_mutex);
    return curr_frame.clone();
}

/**
 * @brief Dog Status의 저장 된 current frame을 setting 해주는 method
 * @param current_frame : 저장할 현재 frame
 */
void DogStatus::setCurrentFrame(cv::Mat current_frame) {    
    std::lock_guard<std::mutex> lock(current_frame_mutex);
    curr_frame = current_frame;
}


/**
 * @brief 현재 System의 Status 실행 여부에 대한 상태를 얻어 옴.
 * 
 * @return true : 실행 중.
 * @return false : 종료.
 */
bool DogStatus::getSystemStatus() {
    std::lock_guard<std::mutex> lock(is_working_mutex);
    return is_working;
}

/**
 * @brief 현재 System의 Status를 setting 해주는 method 
 * 
 * @param status : setting할 flag
 */
void DogStatus::setSystemStatus(bool status) {
    std::lock_guard<std::mutex> lock(is_working_mutex);
    is_working = status;
}

/**
 * @brief 현재 DogStatus에 저장 된 Visual odometry의 결과 값을 저장. 
 * 
 * @param current_traj_data : trajectory가 저장되어 있는 vector
 */
void DogStatus::setTrajData(std::vector<cv::Point2f> current_traj_data) { 
    std::lock_guard<std::mutex> lock(current_traj_mutex);
    this->current_traj = current_traj_data;
}

/**
 * @brief 현재 DogStatus에 저장 된 Visual odoemtry에 대한 결과 값인 trajectory를 가져 옴.
 * 
 * @return std::vector<cv::Point2f> : trajectory가 담겨 있는 vector
 */
std::vector<cv::Point2f> DogStatus::getTrajData() {
    std::lock_guard<std::mutex> lock(current_traj_mutex);
    return current_traj;
}

/**
 * @brief LIDAR에서 받아온 데이터를 DogStatus에 저장해주는 method
 * 
 * @param current_lidar_scan_data : LIDAR에서 받아 온 데이터.
 * @param count : current_lidar_scan_data 의 size
 * @remark parameter로 넣어 줄때 array를 vector로 변환 필요.
 */
void DogStatus::setScanData(std::vector<sl_lidar_response_measurement_node_hq_t> current_lidar_scan_data, size_t count) {
    std::lock_guard<std::mutex> lock(current_scan_data_mutex);
    this->current_scan_data = current_lidar_scan_data;

}

/**
 * @brief DogStatus에 저장 된 LiDAR data를 가지고 옴.
 * 
 * @return std::vector<sl_lidar_response_measurement_node_hq_t> : LiDAR data 
 */
std::vector<sl_lidar_response_measurement_node_hq_t> DogStatus::getScanData() {
    std::lock_guard<std::mutex> lock(current_scan_data_mutex);
    return current_scan_data; 
}


  

