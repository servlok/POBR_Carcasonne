#ifndef CUTTING_H
#define CUTTING_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <list>

typedef std::pair< cv::Mat, cv::Rect > MatBox;
typedef std::list< MatBox > MatBoxList;

cv::Mat floodCutting(cv::Mat& I, const int& x, const int& y);
std::list< cv::Mat > partition(cv::Mat& I);
MatBoxList partitionBoxes(cv::Mat& I);


#endif // CUTTING_H
