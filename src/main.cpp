#include <iostream>
#include <opencv2/opencv.hpp>

#include "MainSystem.h"

const char* keys = {" \\ 
    {help h ? | | this is help} \\ 
    {c | false | this option is Camera Mode if you select this option, input camera path and Calibration data of Camera ex) ./Auto -c [YOUR_CAMERA_PATH] [Calibration_data]} \\ 
    {s | false  | this option is Simulation Mode }"};

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
    
    std::cout << "==========================System Information===========================" << std::endl;
    std::cout << "Simulation Mode = " << simulation_mode << std::endl;
    std::cout << "Camera Mode = " << camera_mode << std::endl;
    std::cout << "Camera Path = " << std::endl;
    std::cout << "Camera Calibration data file path = " << std::endl;
    std::cout << "Auto System Start..." << std::endl;
    std::cout << "=======================================================================" << std::endl;


    MainSystem* main_system = new MainSystem();
    main_system->startCameraMode("../Data/highway.mp4");

    return 0;
}
