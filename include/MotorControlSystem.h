#ifndef MOTOR_CONTROL_SYSTEM_H
#define MOTOR_CONTROL_SYSTEM_H

#include "config/config.h"

#include <stdio.h>
#include <unistd.h>       // Used for UART
#include <sys/fcntl.h>    // Used for UART
#include <termios.h>      // Used for UART
#include <string>

#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <vector>
#include <string>

class MotorControlSystem {
  public:
    MotorControlSystem(const char* port_path, speed_t baud_rate);
    ~MotorControlSystem() { close(fid_); };
    // TRANSMISSION
    bool sendToCommand(char command);

  private:
    int fid_;
    struct termios port_options_;
};


#endif
