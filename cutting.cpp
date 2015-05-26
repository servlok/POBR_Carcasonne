#include "cutting.h"
#include "processing.h"

void flood(cv::Mat_<cv::Vec3b> &I, cv::Mat_<cv::Vec3b> &R, const int &x, const int &y){
    if(I(x, y)[0] == 255){
        return;
    }

    setGrayScale(I(x, y), 255);
    setGrayScale(R(x, y), 0);

    if(x > 0)
        flood(I, R, x - 1, y);
    if(y > 0)
        flood(I, R, x, y - 1);
    if(x < I.rows)
        flood(I, R, x + 1, y);
    if(y < I.cols)
        flood(I, R, x, y + 1);
}

cv::Mat floodCutting(cv::Mat &I, const int &x, const int &y)
{
    cv::Mat res(I.rows,I.cols, CV_8UC3, cv::Scalar(255,255,255));

    cv::Mat_<cv::Vec3b> _I = I;
    cv::Mat_<cv::Vec3b> _R = res;

    flood(_I, _R, x, y);

    return res;
}
