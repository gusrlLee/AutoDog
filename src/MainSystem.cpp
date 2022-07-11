#include "MainSystem.h"

MainSystem::MainSystem(bool mode) {
    this->system_mode = mode;
}

void MainSystem::display(const char* file_path) {
    cv::Mat frame;  
    cv::VideoCapture cap(file_path);

    if (!cap.isOpened()) {
        std::cout << "[ERROR]::Cannot to load frame or camera!, Check camera or Video" << std::endl;
        return;
    }

    while (1) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        cv::imshow("Monitor", frame);
        int key = cv::waitKey(25);
        if (key == 27) {
            break;
        }
    }
}
