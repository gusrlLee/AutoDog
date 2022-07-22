// VERSION 1.0
#include <iostream>
#include <thread>
#include <mutex>

#include "opencv2/opencv.hpp"
#include "DogStatus.h"
#include "MainSystem.h"

const char* keys = {" \\ 
    {help h ? | | this is help. } \\ 
    {c | false | this option is Camera Mode. } \\ 
    {s | false  | this option is Simulation Mode. }"};

// MAIN SYSTEM 
int main(int argc, char* argv[]) {
    cv::CommandLineParser parser(argc, argv, std::string(keys));
    parser.about("AutoDog System v1.0.0");
    if ( parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    if ( argc < 2 ){
        parser.printMessage();
        return 0;
    }

    // mode option and camera calibration data 
    bool simulation_mode = parser.get<bool>("s");
    bool camera_mode = parser.get<bool>("c");

    const char* calibration_data_file = nullptr;
    const char* camera_path = nullptr;
    const char* file_path = "../Data/07/image_0/%06d.png";
    
    printf("==========================System Information===========================\n");
    printf("System Mode = %s\n", simulation_mode ? "Simulation Mode" : "Camera Mode");
    printf("Camera Path = \n");
    printf("Camera Calibration data file path = \n");
    printf("Auto System Start...\n");
    printf("=======================================================================\n\n");

    MainSystem* main_system = new MainSystem(simulation_mode);
    main_system->startProgram();

//    // create Dog Status
//    DogStatus* dog_status = new DogStatus();
//    
//    // process 
//    std::thread camera_capture_thread(cameraCaptureThread, dog_status);
//    std::thread traj_compute_thread(trajComputeThread, dog_status);
//
//    // wait exit 
//    camera_capture_thread.join();
//    traj_compute_thread.join();

    return 0;
}
