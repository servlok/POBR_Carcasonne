#ifndef CUTTING_H
#define CUTTING_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <list>

cv::Mat floodCutting(cv::Mat& I, const int& x, const int& y);

#endif // CUTTING_H
