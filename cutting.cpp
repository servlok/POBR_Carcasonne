#include "cutting.h"
#include "processing.h"
#include <queue>

typedef std::pair<int, int> P;

void color(cv::Mat_<cv::Vec3b> &I, cv::Mat_<cv::Vec3b> &R, const int &x, const int &y){
    setGrayScale(I(x, y), 255);
    setGrayScale(R(x, y), 0);
}

bool check_validity(const cv::Mat_<cv::Vec3b> &I, const int &x, const int &y){
    if(x < 0 || y < 0 || x >= I.rows || y >= I.cols )
        return false;

    return I(x,y)[0] == 0;
}

void flood(cv::Mat_<cv::Vec3b> &I, cv::Mat_<cv::Vec3b> &R, const int &x, const int &y){

    std::queue< P > q;
    q.push(P(x, y));

    color(I, R, x, y);

    while (!q.empty()) {
       P p = q.front();
       q.pop();
       int pX = p.first;
       int pY = p.second;

       int nX = pX + 1;
       int nY = pY;
       if(check_validity(I, nX, nY)){
           color(I, R, nX, nY);
            q.push(P(nX, nY));
       }

       nX = pX - 1;
       if(check_validity(I, nX, nY)){
           color(I, R, nX, nY);
            q.push(P(nX, nY));
       }

       nX = pX;
       nY = pY + 1;
       if(check_validity(I, nX, nY)){
           color(I, R, nX, nY);
            q.push(P(nX, nY));
       }

       nY = pY - 1;
       if(check_validity(I, nX, nY)){
           color(I, R, nX, nY);
            q.push(P(nX, nY));
       }
    }
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
    cv::Mat mat = I.clone();
    cv::Mat_<cv::Vec3b> _I = mat;
    std::list< cv::Mat > list;

    for( int i = 0; i < mat.rows; ++i){
        for( int j = 0; j < mat.cols; ++j ){
            if(_I(i, j)[0] == 0){
                list.push_back(floodCutting(mat, i, j));
            }
        }
    }

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
    mb.second = cv::Rect(minY, minX, maxY - minY + 1, maxX - minX + 1);
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
