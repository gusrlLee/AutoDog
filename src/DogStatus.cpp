#include "DogStatus.h"

DogStatus::DogStatus() {}

cv::Mat DogStatus::getCurrentFrame() {
    return curr_frame.clone();
}

void DogStatus::setCurrentFrame(cv::Mat current_frame) {    
    this->curr_frame = current_frame;
}

