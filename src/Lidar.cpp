#include "Lidar.h"

using namespace rp::standalone::rplidar;

Lidar::Lidar() {
    printf("[Start LiDAR initialization]...\n");

    float temp;
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

bool Lidar::checkSLAMTECLIDARHealth(ILidarDriver* drv) {
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
        } 
        else {
            return true;
        }
    } 
    else {
        fprintf(stderr, "Error, cannot retrieve the lidar health code: %x\n", op_result);
        return false;
    }
}

