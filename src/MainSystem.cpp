#include "MainSystem.h"
#include <stdio.h>
#include <time.h>

// camera mode constructor 
MainSystem::MainSystem(bool mode) 
{
    system_mode = mode;
    dog_status = new DogStatus(); 
    vo = new VisualOdometry();
    lidar = new Lidar();

    printf("Initialization Main System...\n");
}

void MainSystem::trajectoryComputeThread( VisualOdometry* vo, DogStatus* dog_status ) 
{
    //const char* file_path = "../Data/highway.mp4";
    const char* file_path = "../Data/07/image_0/%06d.png";

    cv::VideoCapture cap(file_path);
    if (!cap.isOpened()) 
    {
        printf("[ERROR] Check Your Video or Camrea path!!!\n");
        return;
    }

    cv::Mat frame;

    while(1) 
    {
        cap >> frame;
        if (dog_status->getSystemStatus() == false) {
            break;
        }
        if (frame.empty()) 
        {
            continue;
        }
        dog_status->setCurrentFrame(frame);
        vo->addFrame(frame); 

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void MainSystem::startProgram() 
{
    // start program 
    std::thread traj_compute_thread(&MainSystem::trajectoryComputeThread, vo, this->dog_status);

    dog_status->setSystemStatus(true);

    while (true) 
    {
        cv::Mat current_frame = dog_status->getCurrentFrame();
        if (current_frame.empty()) {
            continue;
        }

        cv::imshow("Dobug", current_frame);
        cv::imshow("Traj", this->vo->getMatchedFrame());
        int key = cv::waitKey(27);
        if (key == 27) 
        {
            dog_status->setSystemStatus(false);
            break;
        }
    }

    traj_compute_thread.join();
}
