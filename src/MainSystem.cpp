#include "MainSystem.h"
#include <stdio.h>
#include <time.h>

// camera mode constructor 
MainSystem::MainSystem(bool mode) 
{
    system_mode = mode;
    dog_status = new DogStatus(); 
    vo = new VisualOdometry();

    // make thread 
    std::thread traj_compute_thread(&MainSystem::trajectoryComputeThread, vo, dog_status);

    printf("Initialization Main System...\n");
}

void MainSystem::trajectoryComputeThread( VisualOdometry* vo, DogStatus* dog_status ) 
{
    const char* file_path = "../Data/07/image_0/%06%d.png";

    cv::VideoCapture cap(file_path);
    cv::Mat frame;

    if (!cap.isOpened()) 
    {
        printf("[ERROR] Check Your Video or Camrea path!!!\n");
        return;
    }

    while(1) 
    {
        cap >> frame;
        if (frame.empty()) 
        {
            continue;
        }
        dog_status->setCurrentFrame(frame);
        vo->addFrame(frame); 
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void MainSystem::startProgram() 
{
    // start program 
    dog_status->setSystemStatus(true);
    while (true) 
    {
        cv::Mat current_frame = dog_status->getCurrentFrame();
        if (current_frame.empty()) 
        {
            break;
        }
        cv::imshow("Dobug", current_frame);
        int key = cv::waitKey(27);
        if (key == 27) 
        {
            break;
        }
    }
}
