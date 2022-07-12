#ifndef __VISUAL_ODOMETRY__
#define __VISUAL_ODOMETRY__

#include <opencv2/opencv.hpp>
#include <opencv2/feature2d.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
#include <math>
#include <string>


class ViualOdometry {
    public:
        

    private:
        cv::Ptr<cv::FeatureDetector> orb_detector;
        cv::Ptr<cv::DescriptorExtractor> descriptor;
        cv::Ptr<cv::descriptorMatcher> matcher;


        cv::Mat descriptor1, descriptor2;
        std::vecotr<cv::KeyPoint> keypoints1, keypoints2;





};

#endif // __VISUAL_ODOMETRY__
