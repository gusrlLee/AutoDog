// -------------------------------------------------------------------------------
// @file DogStatus.cpp
#include "DogStatus.h"

DogStatus::DogStatus() {}


// -------------------------------------------------------------------------------
/**     
@brief getCurrent frame in saved frame  
@remark there is mutex 
*/
// -------------------------------------------------------------------------------
cv::Mat DogStatus::getCurrentFrame() {
    return curr_frame.clone();
}

// -------------------------------------------------------------------------------
/**     
@brief set Current frame in this class 
@remark Data currupt!
*/
// -------------------------------------------------------------------------------
void DogStatus::setCurrentFrame(cv::Mat current_frame) {    
    this->curr_frame = current_frame;
}

