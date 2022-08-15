#include "Camera.h"

Camera::Camera(double focal_length, cv::Point2d principal_point) {
    // calibration data
    m_principal_point = principal_point;
    m_K = (cv::Mat_<double>(3, 3) << focal_length, 0,             principal_point.x, 
                                   0,              focal_length,  principal_point.y,
                                   0,              0,             1);
}