#include "processing.h"
#include "cutting.h"

#define degreesToRadians(angleDegrees) (angleDegrees * CV_PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / CV_PI)

cv::Mat& perform(cv::Mat& I){
  CV_Assert(I.depth() != sizeof(uchar));
  switch(I.channels())  {
  case 1:
    for( int i = 0; i < I.rows; ++i)
        for( int j = 0; j < I.cols; ++j )
            I.at<uchar>(i,j) = (I.at<uchar>(i,j)/32)*32;
    break;
  case 3:
    cv::Mat_<cv::Vec3b> _I = I;
    for( int i = 0; i < I.rows; ++i)
        for( int j = 0; j < I.cols; ++j ){
            _I(i,j)[0] = (_I(i,j)[0]/32)*32;
            _I(i,j)[1] = (_I(i,j)[1]/32)*32;
            _I(i,j)[2] = (_I(i,j)[2]/32)*32;
        }
    I = _I;
    break;
  }
  return I;
}

cv::Mat selectMax(cv::Mat& I){
    CV_Assert(I.depth() != sizeof(uchar));
    cv::Mat  res(I.rows,I.cols, CV_8UC3);
    switch(I.channels())  {
    case 3:
        cv::Mat_<cv::Vec3b> _I = I;
        cv::Mat_<cv::Vec3b> _R = res;
        for( int i = 0; i < I.rows; ++i)
            for( int j = 0; j < I.cols; ++j ){
                int sel = (_I(i,j)[0] < _I(i,j)[1])?1:0;
                sel = _I(i,j)[sel] < _I(i,j)[2]?2:sel;
                _R(i,j)[0] = sel==0?255:0;
                _R(i,j)[1] = sel==1?255:0;
                _R(i,j)[2] = sel==2?255:0;
            }
        res = _R;
        break;
    }
    return res;
}

float moment_zwykly(const float &p, const float &q, cv::Mat& I){

    float m = 0;
    cv::Mat_<cv::Vec3b> _I = I;
    for (int i = 0; i < _I.rows; ++i)
        for (int j = 0; j < _I.cols; ++j)
            if (!_I(i, j)[0])
                m += pow(i, p) * pow(j, q);

    return m;
}

float pole(cv::Mat& I){
    return moment_zwykly( 0, 0, I);
}

int obwod(cv::Mat& I){

    int m = 0;
    cv::Mat_<cv::Vec3b> _I = I;

    for (int i = 1; i < _I.rows - 1; ++i)
        for (int j = 1; j < _I.cols - 1; ++j)

            if (!_I(i, j)[0]){

                bool jest = false;
                for (int a = i - 1; a <= i + 1; ++a)
                    for (int b = j - 1; b <= j + 1; ++b){
                        if (_I(a, b)[0]){
                            jest = true;
                            break;
                        }
                    }

                if (jest)
                    ++m;
            }
    return m;
}

cv::Mat boundingBox(int rColor, cv::Mat& I){
    cv::Mat_<cv::Vec3b> _I = I;
    int minX, maxX, minY, maxY;
    minX = maxX = minY = maxY = -1;
    for (int i = 1; i < _I.rows - 1; ++i){
        for (int j = 1; j < _I.cols - 1; ++j){
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
    return cv::Mat(I, cv::Rect(minY, minX, maxY - minY, maxX - minX)).clone();
}

float katStrzalki(cv::Mat& I){

    int cX = moment_zwykly(1, 0, I) / moment_zwykly(0, 0, I);
    int cY = moment_zwykly(0, 1, I) / moment_zwykly(0, 0, I);
    int geoCenterX = I.rows / 2;
    int geoCenterY = I.cols / 2;

    float opposite = abs(geoCenterX - cX);
    float adjancent = abs(geoCenterY - cY);
    return radiansToDegrees(std::atan(adjancent / opposite));
}

int main(int, char *[]) {
    std::cout << "Start ..." << std::endl;

    cv::Mat image = cv::imread("prog.jpeg");
    cv::Mat copy = cv::imread("test.jpeg");
    cv::Mat prog = progowanie(copy, 175, false);

    prog = rankFilter(prog, 3, 8);
    prog = rankFilter(prog, 3, 8);
    prog = rankFilter(prog, 3, 0);
    prog = rankFilter(prog, 3, 0);
    prog = rankFilter(prog, 3, 0);

    cv::Mat cut = floodCutting(prog, 1, 1);

    cv::imshow("New",cut);
    cv::imshow("Old",prog);

    cv::imshow("Normal",image);

//    cv::imwrite("prog.jpeg", max);
//    cv::namedWindow("Max", cv::WINDOW_NORMAL);

    cv::waitKey(-1);
    return 0;
}
