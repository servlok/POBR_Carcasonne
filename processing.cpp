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
                            double gray = (_I(a, b)[0] + _I(a, b)[1] + _I(a, b)[2]) / 3;
                            Info info;
                            info.x = a;
                            info.y = b;
                            info.gray = gray;
                            pixele.push_back(info);

                        }

                    std::sort(pixele.begin(), pixele.end(), infoSort);

                    Info middle = pixele.at(R);

                    _R(i, j)[0] = _I(middle.x, middle.y)[0];
                    _R(i, j)[1] = _I(middle.x, middle.y)[1];
                    _R(i, j)[2] = _I(middle.x, middle.y)[2];
                    pixele.clear();

            }
        res = _R;
        break;
    }
    return res;
}

