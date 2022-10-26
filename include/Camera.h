#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/opencv.hpp"
#include "opencv2/features2d.hpp"
#include "config/config.h"

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <queue>


class Camera {
  public:
    // constructor 
    Camera(std::string camera_path, double focal_length, cv::Point2d principar_point);

    std::string getCameraPath() { return camera_path_; } // return camera path
    double getFocalLength() { return focal_length_; } // return focal length
    cv::Point2d getPrincipalPoints() { return principal_point_; } // return center point 

  private:
    double focal_length_;
    cv::Point2d principal_point_;

    cv::Mat camera_pose_;
    std::string camera_path_;
};

#endif
