#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "opencv2/opencv.hpp"

class Camera {
  public:
    Camera() {}
    Camera(double focal_length, cv::Point2d principar_point);

  public:
    cv::Mat_<double> m_K;
    cv::Point2d m_principal_point;
    cv::Mat m_camera_pose;
    cv::Point2d camera_current_location;
};

#endif