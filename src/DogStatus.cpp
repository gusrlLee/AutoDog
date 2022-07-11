#include "DogStatus.h"

DogStatus::DogStatus() {}

cv::Mat DogStatus::getCurrentFrame() {
    return current_frame;
}

cv::Mat DogStatus::setCurrentFrame(cv::Mat current_frame) {
    this->current_frame = current_frame;
}
