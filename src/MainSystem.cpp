#include "MainSystem.h"

MainSystem::MainSystem(bool mode) {
    this->system_mode = mode;
    this->dog_status = new DogStatus(); 
    this->vo = new VisualOdometry();
}

void MainSystem::cameraCaptureThread( DogStatus* dog_status, const char* file_path) {
    cv::Mat frame; 
    cv::Mat debug_frame;
    int a;
    cv::VideoCapture cap(file_path);

    if (!cap.isOpened()) {
        std::cout << "[ERROR]::Cannot to load frame or camera!, Check camera or Video" << std::endl;
        return;
    }

    while (1) {
        if (!dog_status->getSystemStatus()) {
            break;
        }

        cap >> frame;
        if (frame.empty()) {
            continue;
        }
        printf("[Camrea]set current_frame\n");
        dog_status->setCurrentFrame(frame);
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
}

void MainSystem::trajectoryComputeThread( VisualOdometry* vo, DogStatus* dog_status ) {

    while(1) {
        if (!dog_status->getSystemStatus()) {
            break;
        }
        cv::Mat current_frame = dog_status->getCurrentFrame();
        printf("[VO] get Frame\n");
        if (current_frame.empty()) {
            continue;
        }

        vo->addFrame(current_frame); 
        printf("[VO] addFrame\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
}


void MainSystem::startProgram(const char* file_path) {

    // start program 
    dog_status->setSystemStatus(true);

    std::thread camera_caputre_thread(&MainSystem::cameraCaptureThread, dog_status, file_path );
    std::thread traj_compute_thread(&MainSystem::trajectoryComputeThread, vo, dog_status);

    while (1) {
        
        cv::Mat debug_frame = vo->getMatchedFrame();
        if ( debug_frame.empty()) {
            continue;
        }

        cv::imshow("debug", debug_frame);
        cv::imshow("Monitor", dog_status->getCurrentFrame());
        int key = cv::waitKey(25);
        if (key == 27) {
            dog_status->setSystemStatus(false);
            break;
        }
    }

    camera_caputre_thread.join();
    traj_compute_thread.join();
}
