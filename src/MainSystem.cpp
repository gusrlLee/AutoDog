#include "MainSystem.h"

MainSystem::MainSystem(bool mode) {
    this->system_mode = mode;
}


void MainSystem::hello() {
    int i=0;
    while(i < 10) {
        std::cout << "hello world\n" << std::endl;
        i++;
    }
}

void MainSystem::startProgram(const char* file_path) {
    cv::Mat frame; 
    int a;
    cv::VideoCapture cap(file_path);

    std::thread hello_thread(&MainSystem::hello, NULL, 1);

    if (a < 0) {
        std::cout << "ERROR not create thread" << std::endl;
        return;
    }

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
