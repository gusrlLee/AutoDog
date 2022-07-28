#include <iostream>
#include <filesystem>

#include "opencv2/opencv.hpp"

namespace fs = std::__fs::filesystem;

int main()
{
    printf("Start ImageCapture Program!\n");
    
    // camera 
    cv::VideoCapture cap(0);
    if ( !cap.isOpened()) {
        std::cout << "[ERROR] check your camera path!!" << std::endl;
    }

    int counter = 0;
    char buf[1024];
    fs::path file_path("../checkimage_dataset");
    if (!fs::exists(file_path)) {
        printf("Not exists directory. So make directory...\n");
        fs::create_directory(file_path);
    }

    cv::Mat frame;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        cv::imshow("Display", frame);
        int key = cv::waitKey(27);
        if (key == 27) {
            break;
        }
        if (key == 115) {
            sprintf(buf, "../checkimage_dataset/%05d.png", counter);
            cv::imwrite(buf, frame);
            std::cout << "save image path = " << buf << std::endl;
            counter++;
        }
    }


    cv::destroyAllWindows();
    cap.release();
    return 0;
}
