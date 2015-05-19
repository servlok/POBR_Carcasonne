#include "processing.h"

struct Info{
    int x;
    int y;
    double gray;
};

bool infoSort(Info a, Info b) { return (a.gray < b.gray); }

cv::Mat rankFilter(cv::Mat& I, const int& N, const int& R){
    CV_Assert(I.depth() != sizeof(uchar));
    cv::Mat  res(I.rows, I.cols, CV_8UC3);
    switch (I.channels())  {
    case 3:
        cv::Mat_<cv::Vec3b> _I = I;
        cv::Mat_<cv::Vec3b> _R = res;
        std::vector<Info> pixele;

        int delta = (N - 1) / 2;
        for (int i = delta; i < I.rows - delta; ++i)
            for (int j = delta; j < I.cols - delta; ++j){
                for (int a = i - delta; a <= i + delta; ++a)
                    for (int b = j - delta; b <= j + delta; ++b){
                        double gray = jasnosc(_I(a, b));

                        Info info;
                        info.x = a;
                        info.y = b;
                        info.gray = gray;
                        pixele.push_back(info);

                    }

                std::sort(pixele.begin(), pixele.end(), infoSort);
                Info middle = pixele.at(R);

                _R(i, j) = _I(middle.x, middle.y);
                pixele.clear();

            }
        res = _R;
        break;
    }
    return res;
}

cv::Mat progowanie(cv::Mat& I, const int& prog, const bool& odwrocone){
    CV_Assert(I.depth() != sizeof(uchar));
    cv::Mat res(I.rows,I.cols, CV_8UC3);

    cv::Mat_<cv::Vec3b> _I = I;
    cv::Mat_<cv::Vec3b> _R = res;
    for( int i = 0; i < I.rows; ++i)
        for( int j = 0; j < I.cols; ++j ){
            int g;
            if(!odwrocone)
                g = (jasnosc(_I(i,j)) <= prog) ? 0 : 255;
            else
                g = (jasnosc(_I(i,j)) <= prog) ? 255 : 0;

            setGrayScale(_R(i,j), g);
        }
    res = _R;

    return res;
}

