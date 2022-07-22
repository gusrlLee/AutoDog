#include "MainSystem.h"
#include <stdio.h>
#include <time.h>

MainSystem::MainSystem(bool mode) {
    this->system_mode = mode;
    this->dog_status = new DogStatus(); 
    this->vo = new VisualOdometry();
}

void MainSystem::cameraCaptureThread( DogStatus* dog_status, const char* file_path) {
    cv::Mat frame; 
    cv::Mat debug_frame;
    cv::VideoCapture cap(file_path);

    if (!cap.isOpened()) {
        std::cout << "[ERROR]::Cannot to load frame or camera!, Check camera or Video" << std::endl;
        return;
    }
    int frame_counter = 0;
    while (1) {
        std::cout << "[Camera counter ] = " << ++frame_counter << std::endl;
        if (!dog_status->getSystemStatus()) {
            break;
        }

        cap >> frame;
        if (frame.empty()) {
            continue;
        }
        dog_status->setCurrentFrame(frame);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void MainSystem::trajectoryComputeThread( VisualOdometry* vo, DogStatus* dog_status ) {

    while(1) {
        // std::cout << "[Start Traj Thread]" << std::endl;
        if (!dog_status->getSystemStatus()) {
            break;
        }
        
        cv::Mat current_frame = dog_status->getCurrentFrame();
        if (current_frame.empty()) {
            continue;
        }
        
        clock_t start = clock();
        vo->addFrame(current_frame); 
        clock_t end = clock();
        // std::cout << "running time = " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
        int key = cv::waitKey(25);
        if (key == 27) {
            dog_status->setSystemStatus(false);
            break;
        }
    }

    camera_caputre_thread.join();
    traj_compute_thread.join();
}
