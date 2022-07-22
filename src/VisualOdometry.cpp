#include "VisualOdometry.h"

VisualOdometry::VisualOdometry() {
    this->principal_point = cv::Point2d(601.8873, 183.1104);
    // intrincis camera data  
    K = (cv::Mat_<double>(3, 3) << focal_length, 0,             principal_point.x, 
                                   0,            focal_length,  principal_point.y,
                                   0,            0,             1);
}

void VisualOdometry::addFrame(cv::Mat frame) {
    cv::Mat frame_buf;
    if ( is_ready ) {
        // save prev information 
        cv::cvtColor(frame, frame_buf, cv::COLOR_BGR2GRAY);
        prev_gray_frame = curr_gray_frame.clone();
        prev_points = curr_points;

        curr_gray_frame = frame_buf.clone();
        extractKeyPoints();
        computeDescriptors();
        poseEstimationPnP();
    }
    else {
        // make prev_information
        cv::cvtColor(frame, frame_buf, cv::COLOR_BGR2GRAY);

        curr_gray_frame = frame_buf.clone();
        extractKeyPoints();
        // And transform ready_status 
        is_ready = true;
    }
    count++;
    std::cout << "receive frame = " << count << std::endl;
}

cv::Mat VisualOdometry::getMatchedFrame() {
    return display;
}

void VisualOdometry::extractKeyPoints() {
    cv::goodFeaturesToTrack(curr_gray_frame, curr_points, 2000, 0.01, 10);
}

void VisualOdometry::computeDescriptors() {
    cv::calcOpticalFlowPyrLK(prev_gray_frame, curr_gray_frame, prev_points, curr_points, status, err );
}

void VisualOdometry::poseEstimationPnP() {

    cv::Mat E, inlier_mask;
    // Essential matrix 
    E = cv::findEssentialMat(prev_points, curr_points, focal_length, principal_point, cv::RANSAC, 0.99, 1, inlier_mask);

    // Rotation matrix and Translation matrix 
    cv::Mat R, t;
    // SVD and R, T extract
    int inlier_num = cv::recoverPose(E, prev_points, curr_points, R, t, focal_length, principal_point, inlier_mask);

    if(inlier_num > min_inlier_num) {
        cv::Mat T = cv::Mat::eye(4, 4, R.type());
        T(cv::Rect(0, 0, 3, 3)) = R * 1.0;
        T.col(3).rowRange(0, 3) = t * 1.0;
        camera_pose = camera_pose * T.inv();
    }

    cv::Point2d camera_point((int)camera_pose.at<double>(0, 3), (int)camera_pose.at<double>(2, 3));
    cv::drawMarker(display, cv::Point(camera_point.x + 500, camera_point.y + 500), cv::Scalar(0, 0, 255), cv::MARKER_SQUARE, 5, 2);
}
