#include "processing.h"
#include "cutting.h"

#define degreesToRadians(angleDegrees) (angleDegrees * CV_PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / CV_PI)

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

    MatBoxList list = partitionBoxes(prog);

    int i = 0;
    for( MatBox mat : list){
        cv::imshow(std::to_string(i), mat.first);
        ++i;
    }

    cv::imshow("Old",prog);
    cv::imshow("Normal",image);

//    cv::imwrite("prog.jpeg", max);
//    cv::namedWindow("Max", cv::WINDOW_NORMAL);

    cv::waitKey(-1);
    return 0;
}
