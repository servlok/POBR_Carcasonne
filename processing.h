#ifndef PROCESSING_H
#define PROCESSING_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#define grayScale( a ) ((a[0] + a[1] + a[2]) / 3)
#define setGrayScale( a, g ) a[0] = g; a[1] = g; a[2] = g;
#define jasnosc(a) ((a[0] > a[1]) ? (a[0] > a[2] ? a[0] : a[2]) : (a[1] > a[2] ? a[1] : a[2]))
#define skorygujPrzedzial(a) (a > 255 ? 255 : (a < 0 ? 0 : a));

cv::Mat rankFilter(cv::Mat& I, const int& N, const int& R);
cv::Mat progowanie(cv::Mat& I, const int& prog, const bool& odwrocone = true);

cv::Mat useMatrixFiltr(cv::Mat& I, const float &podzielnik, double **matrix, const int &sizeOfMatrix);

cv::Mat gaussianBlur(cv::Mat& I, const int& radius);

cv::Mat diffrenceOfGaussian(cv::Mat& I, const int&firstRadius, const int& secondRadius);

double **initTable3x3(double table[][3]);

#endif // PROCESSING_H
