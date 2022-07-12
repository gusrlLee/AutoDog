#include "VisualOdometry.h"

VisualOdometry::VisualOdometry() {
    this->orb_detector = cv::ORB::create();
    this->descriptor = cv::ORB::create();
    this->matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
}

void VisualOdometry::addFrame(cv::Mat frame) {
    if ( is_ready ) {
        // save prev information 
        prev_frame = curr_frame.clone();
        prev_keypoints = curr_keypoints;
        prev_descriptors = curr_descriptors.clone();

        curr_frame = frame.clone();
        extractKeyPoints();
        computeDescriptors();
        featureMatching();
    }
    else {
        // make prev_information
        curr_frame = frame.clone();
        extractKeyPoints();
        computeDescriptors();
        // And transform ready_status 
        is_ready = true;
    }
}

cv::Mat VisualOdometry::getMatchedFrame() {
    return frame_good_match;
}

void VisualOdometry::extractKeyPoints() {
    orb_detector->detect(curr_frame, curr_keypoints);
}

void VisualOdometry::computeDescriptors() {
    orb_detector->compute(curr_frame, curr_keypoints, curr_descriptors);
}

void VisualOdometry::featureMatching() {
    std::vector<cv::DMatch> matches;
    // select the candidates in map
    matcher->match(curr_descriptors, prev_descriptors, matches);

    // extract good match 
    auto min_max = minmax_element(matches.begin(), matches.end(),
                            [](const cv::DMatch &m1, const cv::DMatch &m2) { return m1.distance < m2.distance; });
    double min_dist = min_max.first->distance;
    double max_dist = min_max.second->distance;

    std::vector<cv::DMatch> good_matches;
    for (int i = 0; i < curr_descriptors.rows; i++) {
        if (matches[i].distance <= std::max(2 * min_dist, 30.0)) {
            good_matches.push_back(matches[i]);
        }
    }

    // for debug 
    cv::drawMatches(curr_frame, curr_keypoints, prev_frame, prev_keypoints, good_matches, frame_good_match);
}
