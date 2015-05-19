#ifndef PROCESSING_H
#define PROCESSING_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

cv::Mat rankFilter(cv::Mat& I, const int& N, const int& R);

#endif // PROCESSING_H
