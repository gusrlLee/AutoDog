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

