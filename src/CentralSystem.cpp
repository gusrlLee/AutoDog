#include "CentralSystem.h"
using namespace rp::standalone::rplidar;

CentralSystem::CentralSystem(bool mode, bool use_lidar) {
    // Camera init
    printf("[SYSTEM]: Initialization Camera....");
    if ( mode ) { // Real Mode 
        cv::Point2d center_point = cv::Point2d(639.5, 359.5);
        camera_ = std::make_shared<Camera>(CAMERA_PATH, REAL_FOCAL_LENGTH, center_point, mode);
    }
    else { // simulation mode 
        cv::Point2d center_point = cv::Point2d(601.8873, 183.1104);
        camera_ = std::make_shared<Camera>(SIMULATION_DATA_PATH, SIMUL_FOCAL_LENGTH, center_point, mode);
    }
    printf("\t[OK]\n");

    use_lidar_ = use_lidar;
    // LiDAR init 
    if (use_lidar_){
        printf("[SYSTEM]: Initialization LiDAR....");
        lidar_ = std::make_shared<Lidar>(LIDAR_PORT, LIDAR_BAUDRATE);
        printf("\t[OK]\n");
    }

    // DogStatus init 
    printf("[SYSTEM]: Initialization Dog Status....");
    dog_status_ = std::make_shared<DogStatus>();
    printf("\t[OK]\n");

    // visual odometry init
    printf("[SYSTEM]: Initialization Visual Odometry....");
    vo_ = std::make_shared<VisualOdometry>(camera_);
    printf("\t[OK]\n");

    printf("[SYSTEM]: Initialization Motor Control System....");
    motor_control_system_ = std::make_shared<MotorControlSystem>(UART_PORT, UART_BAUDRATE);
    printf("\t[OK]\n");

    system_status_ = true;
    this->printfSystemInformation(mode);
    dog_status_->setSystemStatus(true);
}

void CentralSystem::printfSystemInformation(bool mode) {
    printf("==========================System Information===========================\n");
    printf("AUTO DOG SYSTEM v1.0.0\n");
    printf("System Mode = %s\n", mode ? "Real Mode" : "Simulation Mode" );
    if ( mode )
        printf("Camera PATH = %s\n", CAMERA_PATH);
    else 
        printf("Camera PATH = %s\n", SIMULATION_DATA_PATH);

    if (use_lidar_) {
        printf("LiDAR PATH  = %s\n", LIDAR_PORT);
        printf("Boud Rate   = %d\n", LIDAR_BAUDRATE);
    }
    printf("Arduino Path    = %s\n", UART_PORT);
    printf("System Status = %s\n", system_status_ ? "[ON]" : "[OFF]");
    printf("Auto System Start...\n");
    printf("=======================================================================\n\n");
    printf("If you want exit system, Press ESC key\n");
}

// void CentralSystem::cameraCaptureThread(std::shared_ptr<Camera> camera, std::shared_ptr<DogStatus> dog_status) {
//     cv::VideoCapture cap(camera->cameraPath());
//     if (!cap.isOpened()) {
//         printf("[ERROR] Check Your Video or Camrea path!!!\n");
//         return;
//     }

//     cv::Mat current_frame;
//     while(1) {
//         // read current_frame 
//         cap >> current_frame;
//         if (!dog_status->getSystemStatus()) {
//             break;
//         }

//         if (current_frame.empty()) {
//             continue;
//         }

//         dog_status->setCurrentFrame(current_frame);
//         std::this_thread::sleep_for(std::chrono::milliseconds(30));
//     }
// }

void CentralSystem::computeTrajectoryThread(std::shared_ptr<Camera> camera, std::shared_ptr<VisualOdometry> vo, std::shared_ptr<DogStatus> dog_status) {
    cv::Mat current_frame;
    // issue : if divide camera capture thread, not work visual odometry 
    cv::VideoCapture cap;
    if (camera->systemMode()) {
        cap.open(camera->cameraPath(), cv::CAP_GSTREAMER);
        // cap.open("/dev/video1");
    }
    else {
        cap.open(camera->cameraPath());
    }

    if (!cap.isOpened()) {
        printf("[ERROR] Check Your Video or Camrea path!!!\n");
        return;
    }

    while(1) {
        // read current_frame 
        if (!dog_status->getSystemStatus()) {
            cap.release();
            break;
        }

        cap >> current_frame;
        // current_frame = dog_status->getCurrentFrame();
        if (current_frame.empty()) {
            continue;
        }

        dog_status->setCurrentFrame(current_frame);
        vo->addFrame(current_frame); 
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    cap.release();
}

void CentralSystem::scanLidarThread(std::shared_ptr<Lidar> lidar, std::shared_ptr<DogStatus> dog_status) {
    while(1) {
        if (!dog_status->getSystemStatus()) {
            break;
        }

        sl_lidar_response_measurement_node_hq_t nodes[8192];
        size_t count = _countof(nodes);
        count = lidar->grabScanedLidarData(nodes, count);
        std::vector<sl_lidar_response_measurement_node_hq_t> current_scan_data(std::begin(nodes), std::end(nodes));
        dog_status->setScanData(current_scan_data, count);
        // for degug
        // printf("====================================== LiDAR Data =============================================");
        // for (int pos = 0; pos < (int)count; ++pos) {
        //     printf("[pos : %d] theta: %03.2f Dist: %08.2f\n", pos, (nodes[pos].angle_z_q14 * 90.f) / 16384.f, nodes[pos].dist_mm_q2 / 4.0f);
        // }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void CentralSystem::communicationSystemThread(std::shared_ptr<MotorControlSystem> motor_control_system, std::shared_ptr<DogStatus> dog_status) {
    char command;
    bool status;
    bool is_in_dangerzone = false;
    bool is_safe_left = true;
    bool is_safe_right = true;
    float object_collision_distance_threshold = 600;
    motor_control_system->sendToCommand(UP_FLAG);

    while(1) {
        if (!dog_status->getSystemStatus()) {
            motor_control_system->sendToCommand(END_FLAG);
            break;
        }

        std::vector<sl_lidar_response_measurement_node_hq_t> current_scan_data = dog_status->getScanData();
        
        // our LIDAR 
        //
        //  ----------------
        // |                |
        // |    OUR ZONE    |
        // |                |
        //  ----------------
        //         0
        //        ****   
        // 270   ******    90
        //        ****   
        //         \/    
        //        180

        for (int i=0; i<current_scan_data.size(); i++) {
            float theta = current_scan_data[i].angle_z_q14 * 90.f / 16384.f; 
            // we consider 90 > theta,
            // so other theta break
            if ( theta > 90) break;
            float object_distance = current_scan_data[i].dist_mm_q2 / 4.0f;
            if (theta < 45) { // check colision warning
                if (object_distance != 0 && object_distance < object_collision_distance_threshold) {
                    is_in_dangerzone = true;
                }
            }
            else { // check right 
                if (object_distance != 0 && object_distance < object_collision_distance_threshold) {
                    is_safe_right = false;
                }
            }
        }

        for (int i=current_scan_data.size() - 1; i>=0; i--) {
            float theta = current_scan_data[i].angle_z_q14 * 90.f / 16384.f; 
            // we consider 270 < theta,
            // so other theta break
            if ( theta < 270) break;
            float object_distance = current_scan_data[i].dist_mm_q2 / 4.0f;
            if (theta > 315) { // check colision warning
                if (object_distance != 0 && object_distance < object_collision_distance_threshold) {
                    is_in_dangerzone = true;
                }
            }
            else { // check left
                if (object_distance != 0 && object_distance < object_collision_distance_threshold) {
                    is_safe_left = false;
                }
            }
        }

        if ( is_in_dangerzone ) {
            if ( is_safe_right == true && is_safe_left == false ) { // safe right 
                command = TRUN_RIGHT;
            }
            else if ( is_safe_left == true && is_safe_right == false ) { // safe left 
                command = TURN_LEFT;
            }
            else if ( is_safe_right == false && is_safe_left == false ) {
                // if dog can't turn left and turn right, dog need to turn arround
                // So Continue giving 's' to command, due to turn arround.
                command = TRUN_RIGHT;
            }
            else if ( is_safe_right == true && is_safe_left == true ) {
                // if both is_safe_right and is_safe_left is true, we choice right turn.
                command = TRUN_RIGHT;
            }
        } 
        else {
            // If there is nothing in the danger zone, we give 'w' for going forward
            command = GO_FORWARD;
        }

        // send command to Arduino. 
        // printf("[Debug] Is in Dangerzone : %s\n", is_in_dangerzone ? "Yes!" : "No!");
        // printf("[Debug] Safe Left : %s\n", is_safe_left ? "Yes!" : "No!");
        // printf("[Debug] Safe Right : %s\n", is_safe_right ? "Yes!" : "No!");
        // printf("[Debug] Command : %c\n", command);
        status = motor_control_system->sendToCommand(command);

        // init flag
        is_in_dangerzone = false;
        is_safe_left = true;
        is_safe_right = true;

        if (!status) {
            continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

void CentralSystem::startProgram() {
    float temp = 0;
    double theta_array[2] = {0};
    // camera_capture_thread_ = std::thread(&CentralSystem::cameraCaptureThread, camera_, dog_status_);
    compute_traj_thread_ = std::thread(&CentralSystem::computeTrajectoryThread, camera_, vo_, dog_status_);
    if(use_lidar_)
        scan_lidar_thread_ = std::thread(&CentralSystem::scanLidarThread, lidar_, dog_status_);

    communication_system_thread_ = std::thread(&CentralSystem::communicationSystemThread, motor_control_system_, dog_status_);

    cv::Mat current_display;
    cv::Mat traj_display = cv::Mat::zeros(cv::Size(1000, 1000), CV_8UC3);

    while (1) {
        if (!dog_status_->getSystemStatus()) {
            break;
        }

        current_display = dog_status_->getCurrentFrame();

        cv::Point2d current_location = vo_->getCurrentLocation();
        int curr_loc_x = (2*int(current_location.x)) + 500;
        int curr_loc_y = 500 - (2*int(current_location.y));
        // printf("x : %d y: %d\n", curr_loc_x, curr_loc_y);

        cv::drawMarker(traj_display, cv::Point(curr_loc_x, curr_loc_y), cv::Scalar(0, 0, 255), cv::MARKER_SQUARE, 5, 2);
        // traj_display = dog_status_->getTrajData();
        
        std::vector<sl_lidar_response_measurement_node_hq_t> current_scan_data;
        current_scan_data = dog_status_->getScanData();
        size_t count = current_scan_data.size();

        for (int pos = 0; pos < (int)count; ++pos) {
            // printf("theta: %03.2f Dist: %08.2f\n", (curr[pos].angle_z_q14 * 90.f) / 16384.f, nodes[pos].dist_mm_q2 / 4.0f);
            temp = current_scan_data[pos].angle_z_q14 * 90.f / 16384.f;
            transformTheta(temp, theta_array);
            float object_distance = current_scan_data[pos].dist_mm_q2 / 4.0f;

            if ( object_distance > 0) {
                if ((object_distance) < OUR_LIDAR_MAX_DISTANCE) {
                    int x = int((object_distance) * theta_array[0] * PIXEL_RATIO);
                    int y = int((object_distance) * theta_array[1] * PIXEL_RATIO);
                    cv::line(traj_display, cv::Point(curr_loc_x, curr_loc_y), cv::Point(curr_loc_x + x, curr_loc_y + y), cv::Scalar(100, 100, 100), 1, cv::LINE_AA);
                    cv::circle(traj_display, cv::Point(curr_loc_x + x, curr_loc_y + y), 1, cv::Scalar(0, 0, 255), -1, cv::FILLED);
                }
                else { // if (current_scan_data[pos].dist_mm_q2 / 4.0f > 2000)
                    int x = int((OUR_LIDAR_MAX_DISTANCE) * theta_array[0] * PIXEL_RATIO);
                    int y = int((OUR_LIDAR_MAX_DISTANCE) * theta_array[1] * PIXEL_RATIO);
                    cv::line(traj_display, cv::Point(curr_loc_x, curr_loc_y), cv::Point(curr_loc_x + x, curr_loc_y + y), cv::Scalar(100, 100, 100), 1, cv::LINE_AA);
                }
            }
        }

        if (current_display.empty()) 
            continue;

        cv::imshow("display", current_display);
        cv::imshow("Tracjectory", traj_display);
        int key = cv::waitKey(27);
        if (key == 27) {
            dog_status_->setSystemStatus(false);
            break;
        }
    }
    cv::destroyAllWindows();

    
    // camera_capture_thread_.join();
    compute_traj_thread_.join();
    
    if(use_lidar_)
        scan_lidar_thread_.join();

    communication_system_thread_.join();
    printf("[SYSTEM]: Exit system!\n");
}

void CentralSystem::transformTheta(const float theta, double* output_array){
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
