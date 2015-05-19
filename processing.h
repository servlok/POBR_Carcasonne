#ifndef PROCESSING_H
#define PROCESSING_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#define grayScale( a ) ((a[0] + a[1] + a[2]) / 3)
#define setGrayScale( a, g ) a[0] = g; a[1] = g; a[2] = g;
#define jasnosc(a) ((a[0] > a[1]) ? (a[0] > a[2] ? a[0] : a[2]) : (a[1] > a[2] ? a[1] : a[2]))

cv::Mat rankFilter(cv::Mat& I, const int& N, const int& R);
cv::Mat progowanie(cv::Mat& I, const int& prog, const bool& odwrocone = true);


#endif // PROCESSING_H
