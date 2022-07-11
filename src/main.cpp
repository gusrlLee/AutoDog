#include <iostream>
#include <opencv2/opencv.hpp>


// how to start command 
void printHelp() {
    printf("====================================================================================\n");
    printf("Hello AutoDog System!\n");
    printf("USAGE :\n"); 
    printf("        ./Auto [option]\n");
    printf("OPTION :\n");
    printf("    -s      Simulation mode, if you select this option, Use KITTI dataset\n");
    printf("    -c      Camera mode, Use Connected Camrea and you need to input Calibration data\n");
    printf("            ex) ./Auto -c [YOUR_DATA]\n");
    printf("====================================================================================\n");
    
}

int main(int argc, char* argv[]) {
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("AutoDog System v1.0.0");
    if ( parser.has("help")) {
        parser.printMessage();
        return 0;
    }
    if ( argc < 2 ){
        printHelp();
        return 0;
    }

    // mode option and camera calibration data 
    bool simulation_mode = false;
    bool camera_mode = false;
    const char* calibration_data_file = nullptr;

    return 0;


}
