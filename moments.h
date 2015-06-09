#ifndef MOMENTS_H
#define MOMENTS_H

#include "cutting.h"

typedef struct {
    cv::Mat mat;
    cv::Rect box;

    float S;
    float L;

    float M1;
    float M2;
    float M3;
    float M4;
    float M5;
    float M6;
    float M7;
    float M8;
    float M9;
    float M10;

} MatInfo;

MatInfo doTheMath(const MatBox &matBox);

void printMatInfo(const MatInfo& mat);

#endif // MOMENTS_H
