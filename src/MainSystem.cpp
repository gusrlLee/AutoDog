/**
 * @file MainSystem.cpp
 * @author gusrlLee 
 * @brief 
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <time.h>

#include "MainSystem.h"
#include "config.h"

using namespace rp::standalone::rplidar;

/**
 * @brief Construct a new Main System:: Main System object
 * 
 * @param mode : camrea mode 와 simulation 모드를 선택. 
 */
MainSystem::MainSystem(bool mode) {
    printf("Initialization Main System...\n");
    // create ptr
    system_mode = mode;
    dog_status = new DogStatus(); 
    vo = new VisualOdometry();
    sl_result op_result;


    // for LIDAR initialization 
    printf("[Start LiDAR initialization]...\n");

    drv = *createLidarDriver(); 
    if ( !drv ) {
        fprintf(stderr, "[ERROR] insufficent memory, exit!\n");
        exit(-2);
    }
    _channel = (*createSerialPortChannel(PORT, BAUDRATE));

    if (SL_IS_OK((drv)->connect(_channel))) {
        op_result = drv->getDeviceInfo(devinfo);

        if (SL_IS_OK(op_result)) {
            connectSuccess = true;
        }
        else {
            delete drv;
            drv = NULL;
        }
    }

    if ( !connectSuccess ) {
        printf("[ERROR] connect status = false\n");
        printf("[ERROR] CANNOT Connect port, check your port or connect status\n");
        exit(2);
    }

    if (checkSLAMTECLIDARHealth(drv)) {
        drv->setMotorSpeed();
        // start Sacnning 
        printf("Success Initialization LiDAR.\n");
        drv->startScan(0, 1);
    }
}

/**
 * @brief Visual Odometry에 대한 연산을 진행하는 Thread code 
 * 
 * @param vo : MainSystem에서 생성된 Visual odoemtry class에 대한 ptr 
 * @param dog_status : 현재 Dog의 상태를 저장하는 shared data ptr 
 * @remark static으로 private안에 생성 됨. 
 */
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

/**
 * @brief LIDAR가 받아온 데이터로 우리의 scan Data를 handling하는 thread code 
 * 
 * @param lidar : RPLiDAR A1의 sdk에서 선언 된 class를 이용하여 생성 한 LiDAR ptr
 * @param dog_status : 현재 Dog의 상태를 저장하는 shared data ptr 
 * @remark static으로 private안에 생성 됨. 
 */
void MainSystem::detectScanDataThread(ILidarDriver* lidar, DogStatus* dog_status) {
    sl_result op_result; // bool 

    while ( true ) {
        if (dog_status->getSystemStatus() == false) {
            break;
        }
        sl_lidar_response_measurement_node_hq_t nodes[8192];
        size_t count = _countof(nodes);

        op_result = lidar->grabScanDataHq(nodes, count);

        if (SL_IS_OK(op_result)) {
            lidar->ascendScanData(nodes, count);
        std::vector<sl_lidar_response_measurement_node_hq_t> current_scan_data(std::begin(nodes), std::end(nodes));
        dog_status->setScanData(current_scan_data, count);
            // for (int pos = 0; pos < int(count); ++pos) {
            //     printf("theta: %03.2f Dist: %08.2f\n", (nodes[pos].angle_z_q14 * 90.f) / 16384.f, nodes[pos].dist_mm_q2/4.0f);
            // }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    lidar->stop();
    lidar->setMotorSpeed(0);
}

/**
 * @brief main에서 호출되는 System start call method 
 * 
 */
void MainSystem::startProgram() {
    // start program 
    // threads 
    std::thread traj_compute_thread(&MainSystem::trajectoryComputeThread, vo, this->dog_status);
    std::thread detect_scan_data_thread(&MainSystem::detectScanDataThread, drv, this->dog_status);
    float temp = 0;

    // turn on system start flag 
    dog_status->setSystemStatus(true);
    cv::Mat display_image = cv::Mat::zeros(1000, 1000, CV_8UC3);  
    double theta_array[2] = {0};

    while (true) {
        cv::Mat current_frame = dog_status->getCurrentFrame();
        
        if (current_frame.empty()) {
            continue;
        }

        cv::Point2d current_location = vo->getCurrentLocation();

        std::vector<sl_lidar_response_measurement_node_hq_t> current_scan_data;
        current_scan_data = dog_status->getScanData();
        size_t count = current_scan_data.size();

        int loc_x = current_location.x + 500;
        int loc_y = current_location.y + 500;
        cv::drawMarker(display_image, cv::Point(loc_x, loc_y), cv::Scalar(0, 0, 255), cv::MARKER_SQUARE, 5, 2);

        for (int pos = 0; pos < (int)count; ++pos) {
            // printf("theta: %03.2f Dist: %08.2f\n", (curr[pos].angle_z_q14 * 90.f) / 16384.f, nodes[pos].dist_mm_q2 / 4.0f);
            temp = current_scan_data[pos].angle_z_q14 * 90.f / 16384.f;
            transformTheta(temp, theta_array);

            int x = int((current_scan_data[pos].dist_mm_q2 / 4.0f) * theta_array[0] * PIXEL_RATIO);
            int y = int((current_scan_data[pos].dist_mm_q2 / 4.0f) * theta_array[1] * PIXEL_RATIO);

            cv::line(display_image, cv::Point(loc_x, loc_y), cv::Point(loc_x + x, loc_y + y), cv::Scalar(100, 100, 100), 1, cv::LINE_AA);
            cv::circle(display_image, cv::Point(loc_x + x, loc_y + y), 1, cv::Scalar(0, 0, 255), -1, cv::FILLED);
        }

        cv::imshow("Display", display_image);
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

/**
 * @brief LiDAR의 현재 상태를 확인해 주는 method MainSystem에서 LiDAR 객체를 생성할 때 상태 체크.
 * 
 * @param drv : status를 check할 LiDAR의 ptr
 * @return true : available
 * @return false : not available
 */
bool MainSystem::checkSLAMTECLIDARHealth(ILidarDriver * drv)
{
    sl_result     op_result;
    sl_lidar_response_device_health_t healthinfo;

    op_result = drv->getHealth(healthinfo);
    if (SL_IS_OK(op_result)) { // the macro IS_OK is the preperred way to judge whether the operation is succeed.
        printf("SLAMTEC Lidar health status : %d\n", healthinfo.status);
        if (healthinfo.status == SL_LIDAR_STATUS_ERROR) {
            fprintf(stderr, "Error, slamtec lidar internal error detected. Please reboot the device to retry.\n");
            // enable the following code if you want slamtec lidar to be reboot by software
            // drv->reset();
            return false;
        } else {
            return true;
        }

    } else {
        fprintf(stderr, "Error, cannot retrieve the lidar health code: %x\n", op_result);
        return false;
    }
}

/**
 * @brief 라이다에서 받아온 theta를 가지고 좌표계 상에서 표현할 수 있는 좌표로 만들어 줌.  
 * 
 * @param theta : Rotation 될 각도.
 * @param output_array : output
 */
void MainSystem::transformTheta(const float theta, double* output_array){
    double x_theta = 0;
    double y_theta = 0;

    if(0 <= theta && theta < 90){
        x_theta = sin(theta*(PI/180));
        y_theta = -1 * (cos(theta*(PI/180)));

    } else if(90 <= theta && theta < 180){
        x_theta = cos((theta - 90) * (PI/180));
        y_theta = sin((theta - 90) * (PI/180));

    } else if(180 <= theta && theta < 270) {
        x_theta = -1 * sin((theta - 180) * (PI/180));
        y_theta = cos((theta - 180.f) * (PI/180));

    } else {
        x_theta = -1 * cos((theta - 270) * (PI/180));
        y_theta = -1 * sin((theta - 270) * (PI/180));
    }

    output_array[0] = x_theta;
    output_array[1] = y_theta;

    return;
}

