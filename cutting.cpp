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
    if(x < I.rows - 1)
        flood(I, R, x + 1, y);
    if(y < I.cols - 1)
        flood(I, R, x, y + 1);
}

cv::Mat floodCutting(cv::Mat &I, const int &x, const int &y)
{
    cv::Mat res(I.rows,I.cols, CV_8UC3, cv::Scalar(255,255,255));

    cv::Mat_<cv::Vec3b> _I = I;
    cv::Mat_<cv::Vec3b> _R = res;

    flood(_I, _R, x, y);

    res = _R;
    return res;
}

std::list<cv::Mat> partition(cv::Mat &I)
{
    cv::Mat_<cv::Vec3b> _I = I;
    std::list< cv::Mat > list;

    for( int i = 0; i < I.rows; ++i){
        for( int j = 0; j < I.cols; ++j ){
            if(_I(i, j)[0] == 0){
                list.push_back(floodCutting(I, i, j));
            }
        }
    }

//    list.push_back(floodCutting(I, 1, 1));

    return list;
}

MatBox boundingBox(int rColor, cv::Mat& I){
    cv::Mat_<cv::Vec3b> _I = I;
    int minX, maxX, minY, maxY;
    minX = maxX = minY = maxY = -1;
    for (int i = 0; i < _I.rows; ++i){
        for (int j = 0; j < _I.cols; ++j){
            if (_I(i, j)[2] == rColor){
                if (minX == -1){
                    minX = maxX = i;
                    maxY = minY = j;
                }
                else {
                    minX = std::min(minX, i);
                    minY = std::min(minY, j);
                    maxX = std::max(maxX, i);
                    maxY = std::max(maxY, j);
                }
            }
        }
    }
    MatBox mb;
    mb.second = cv::Rect(minY, minX, maxY - minY, maxX - minX);
    mb.first = cv::Mat(I, mb.second).clone();
    return mb;
}

MatBoxList partitionBoxes(cv::Mat &I)
{
    MatBoxList listBoxes;
    std::list<cv::Mat> list = partition(I);

    for( cv::Mat mat : list ){
        listBoxes.push_back(boundingBox(0, mat));
    }

    return listBoxes;
}
