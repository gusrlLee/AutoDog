#include <stdio.h>
#include <time.h>

#include "MainSystem.h"

// camera mode constructor 
MainSystem::MainSystem(bool mode) {
    // create ptr
    system_mode = mode;
    dog_status = new DogStatus(); 
    vo = new VisualOdometry();
    lidar = new Lidar();

    printf("Initialization Main System...\n");
}

void MainSystem::trajectoryComputeThread( VisualOdometry* vo, DogStatus* dog_status ) {
    //const char* file_path = "../Data/highway.mp4";
    const char* file_path = "../Data/07/image_0/%06d.png";

    // load camera path or data_path
    cv::VideoCapture cap(file_path);
    if (!cap.isOpened()) {
        printf("[ERROR] Check Your Video or Camrea path!!!\n");
        return;
    }

    cv::Mat frame;
    while(1) 
    {
        // read frame 
        cap >> frame;
        if (dog_status->getSystemStatus() == false) {
            break;
        }
        if (frame.empty()) {
            continue;
        }
        dog_status->setCurrentFrame(frame);
        vo->addFrame(frame); 

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void MainSystem::detectScanDataThread(Lidar* lidar, DogStatus* dog_status) {
    while ( true ) {
        if (dog_status->getSystemStatus() == false) {
            break;
        }
        lidar->getScanLidarData(current_scan_data);
        size_t count = _countof(current_scan_data);

        for (int pos = 0; pos < (int)count ; ++pos) {
            printf("theta: %03.2f Dist: %08.2f\n", (current_scan_data[pos].angle_z_q14 * 90.f) / 16384.f, current_scan_data[pos].dist_mm_q2/4.0f);
        }
    }
}

void MainSystem::startProgram() {
    // start program 
    // threads 
    std::thread traj_compute_thread(&MainSystem::trajectoryComputeThread, vo, this->dog_status);
    std::thread detect_scan_data_thread(&MainSystem::detectScanDataThread, lidar, this->dog_status);

    // turn on system start flag 
    dog_status->setSystemStatus(true);

    while (true) {
        cv::Mat current_frame = dog_status->getCurrentFrame();
        if (current_frame.empty()) {
            continue;
        }

        cv::imshow("Dobug", current_frame);
        // cv::imshow("Traj", this->vo->getMatchedFrame());
        int key = cv::waitKey(27);
        if (key == 27) {
            dog_status->setSystemStatus(false);
            break;
        }
    }

    // wait for thread exit 
    detect_scan_data_thread.join();
    traj_compute_thread.join();
}
