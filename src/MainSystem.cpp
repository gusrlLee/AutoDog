#include "MainSystem.h"

MainSystem::MainSystem(bool mode) {
    this->system_mode = mode;
    this->dog_status = new DogStatus(); 
    this->visual_odometry = new VisualOdometry();
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
    cv::Mat debug_frame;
    int a;
    cv::VideoCapture cap(file_path);

    // std::thread hello_thread(&MainSystem::hello, this);

    if (!cap.isOpened()) {
        std::cout << "[ERROR]::Cannot to load frame or camera!, Check camera or Video" << std::endl;
        return;
    }

    while (1) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }
        dog_status->setCurrentFrame(frame);
        visual_odometry->addFrame(frame);

        debug_frame = visual_odometry->getMatchedFrame();
        if ( debug_frame.empty()) {
            continue;
        }
        cv::imshow("debug", debug_frame);
        cv::imshow("Monitor", dog_status->getCurrentFrame());
        int key = cv::waitKey(25);
        if (key == 27) {
            break;
        }
    }

    // hello_thread.join();
}
