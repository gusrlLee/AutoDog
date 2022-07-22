// -------------------------------------------------------------------------------
#include "DogStatus.h"

DogStatus::DogStatus() {
    is_working = false;
}

// -------------------------------------------------------------------------------
cv::Mat DogStatus::getCurrentFrame() {
    std::lock_guard<std::mutex> lock(current_frame_mutex);
    cv::Mat current_frame;
    if (!curr_frame_buffer.empty()) {
        current_frame = curr_frame_buffer.front();
        curr_frame_buffer.pop();
    }
    return current_frame;
}

// -------------------------------------------------------------------------------
void DogStatus::setCurrentFrame(cv::Mat current_frame) {    
    std::lock_guard<std::mutex> lock(current_frame_mutex);
    curr_frame_buffer.push(current_frame);
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

