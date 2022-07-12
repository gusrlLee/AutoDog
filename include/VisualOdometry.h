#ifndef __VISUAL_ODOMETRY__
#define __VISUAL_ODOMETRY__

#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>


class VisualOdometry {
    public:
        VisualOdometry();
        ~VisualOdometry();

        void addFrame(cv::Mat frame);
        // std::vector<cv::DMatch> getMatchedFeatures();
        cv::Mat getMatchedFrame();
        
    private:
        // ORB feature detection 
        cv::Ptr<cv::FeatureDetector> orb_detector;
        cv::Ptr<cv::DescriptorExtractor> descriptor;
        cv::Ptr<cv::DescriptorMatcher> matcher;

        // descritor and vector for ORB detector 
        cv::Mat curr_descriptors, prev_descriptors;
        std::vector<cv::KeyPoint> curr_keypoints, prev_keypoints;

        cv::Mat curr_frame;
        cv::Mat prev_frame;

        // this value, check ready prev_frame 
        bool is_ready = false;
        // for Debug 
        cv::Mat frame_good_match;

        void extractKeyPoints();
        void computeDescriptors();
        void featureMatching();
    
};

#endif // __VISUAL_ODOMETRY__
