// VERSION 1.0
/**
 * @file main.cpp
 * @author hyeon ki (gusrlLee@github.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <thread>
#include <mutex>

#include "opencv2/opencv.hpp"
#include "DogStatus.h"
#include "MainSystem.h"

const char* keys = {" \\ 
    {help h ?            |       | this is help. } \\ 
    {real-mode           |       | this option is Real Mode. } \\
    {simulation-mode     |       | this option is Simulation Mode. }"};

void printSystemInformation(bool mode) {
    printf("==========================System Information===========================\n");
    printf("System Mode = %s\n", mode ? "Real Mode" : "Simulation Mode" );
    printf("Auto System Start...\n");
    printf("=======================================================================\n\n");
}

// MAIN SYSTEM =============================================================================================================== 
int main(int argc, char* argv[]) {
    // if system mode true, system mode is RealMode 
    // else system mode is simulationMode      
    bool system_mode = false;

    cv::CommandLineParser parser(argc, argv, std::string(keys));
    parser.about("AutoDog System v1.0.0");
    if ( parser.has("help")) {
        parser.printMessage();
        return 0;
    }
    else if (argc < 2){
        parser.printMessage();
        return 0;
    }
    else if (parser.has("real-mode")) {
        system_mode = true; // Real mode 
    }
    else if (parser.has("simulation-mode")){
        system_mode = false; // simulation mode 
    }

    printSystemInformation(system_mode);

    MainSystem* main_system = new MainSystem(system_mode);
    main_system->startProgram();

    return 0;
}
