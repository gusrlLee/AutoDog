#include "common_header.h"

#include "DogStatus.h"
#include "CentralSystem.h"

const char* keys = {" \\
    {help h ?               |         | this is help. } \\
    {camera-path            | nullptr | Write your Camera Path. } \\
    {focal-length           | 123123  | Write your focal length of Camera.} \\   
    {lidar-path             | nullptr | Write your LIDAR Path. } \\
    {lidar-baudrate         | 115200  | Write your baudrate of lidar. } \\
    {arduino-path           | nullptr | Write your Arduino Path.} \\
    {arduino-baudrate       | 115200  | Write your baudrate of arduino.}"};

void help() {
    std::cout << "[SYSTEM INFORMATION]\n"
        "--------------------------------------------------------------------------------------------------------\n"
        "You need to write argument for this program. \n"
        "If you want simulation mode, you need to write your dataset path for simulation.\n"
        "If you want real mode, you need to write your camera path\n\n"

        "[Arguments]\n"
        "camera-path = Your Camera path or dataset path. check your connect status. (defualt : NULL)\n"
        "lidar-path = Your LIDAR path. check your connect status. (default : NULL)\n"
        "lidar-baudrate = Your baudrate of LIDAR. ex) 9600, 115200, ... (default : 115200)\n"
        "arduino-path = Your Arduino path. check your connect status. (default : NULL)\n"
        "arduino-baudrate = Your baudrate of arduino. ex) 9600, 115200, ... (default : 115200)\n"

        "\n[EXAMPLE]\n"
        "ex) ./auto --camera-path=[YOUR PATH] --focal-length=[FOCAL_LENGTH]--lidar-path=[YOUR PATH] --lidar-baudrate=[BAUDRATE] --arduino-path=[YOUR PATH] --arduino-baudrate=[BAUDRATE]\n"
        "--------------------------------------------------------------------------------------------------------\n" << std::endl;
}


// MAIN SYSTEM =============================================================================================================== 
int main(int argc, char* argv[]) {
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("AutoDog System v1.0.0");

    if ( parser.has("help")) {
        help();
        return 0;
    }
    else if (argc < 2){
        help();
        return 0;
    }

    // init variable 
    SystemInformation system_info;
    
    // init arguments 
    system_info.camera_path = parser.get<std::string>("camera-path");
    system_info.focal_length = parser.get<double>("focal-length");
    system_info.lidar_path = parser.get<std::string>("lidar-path");
    system_info.lidar_baudrate = parser.get<int>("lidar-baudrate");
    system_info.arduino_path = parser.get<std::string>("arduino-path");
    system_info.arduino_baudrate = parser.get<int>("arduino-baudrate");

    CentralSystem* central_system = new CentralSystem(system_info);
    central_system->startProgram();

    return 0;
}
