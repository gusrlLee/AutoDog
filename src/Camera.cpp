#include "Camera.h"

Camera::Camera(std::string camera_path, double focal_length, cv::Point2d principal_point) {
    // init
    camera_path_ = camera_path;
    focal_length_ = focal_length;
    principal_point_ = principal_point;
}
