// -------------------------------------------------------------------------------
// @file DogStatus.cpp
#include "DogStatus.h"

DogStatus::DogStatus() {
    is_working = false;
}


// -------------------------------------------------------------------------------
/**     
@brief getCurrent frame in saved frame  
@remark there is mutex 
*/
// -------------------------------------------------------------------------------
cv::Mat DogStatus::getCurrentFrame() {
    std::lock_guard<std::mutex> guard(current_frame_mutex);
    return curr_frame.clone();
}

// -------------------------------------------------------------------------------
/**     
@brief set Current frame in this class 
@remark Data currupt!
*/
// -------------------------------------------------------------------------------
void DogStatus::setCurrentFrame(cv::Mat current_frame) {    
    std::lock_guard<std::mutex> guard(current_frame_mutex);
    this->curr_frame = current_frame;
}


bool DogStatus::getSystemStatus() {
    std::lock_guard<std::mutex> guard(is_working_mutex);
    return is_working;
}

void DogStatus::setSystemStatus(bool status) {
    std::lock_guard<std::mutex> guard(is_working_mutex);
    is_working = status;
}

