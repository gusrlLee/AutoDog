#include "MainSystem.h"

MainSystem::MainSystem() {}

int MainSystem::startCameraMode(const char* video_path) {
    cv::VideoCapture cap(video_path);
    if (!cap.isOpened()) {
        std::cout << "[ERROR]::Faild to open Video! Check your Video path" << std::endl;
    } 

    return 0;
}
