#include "moments.h"


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


MatInfo doTheMath(const MatBox &matBox)
{
    MatInfo info;
    info.mat = matBox.first;
    info.box = matBox.second;

    float m00 = moment_zwykly(0, 0, matBox.first);
    float m20 = moment_zwykly(2, 0, matBox.first);
    float m02 = moment_zwykly(0, 2, matBox.first);
    float m10 = moment_zwykly(1, 0, matBox.first);
    float m01 = moment_zwykly(0, 1, matBox.first);
    float m11 = moment_zwykly(1, 1, matBox.first);
    float M20 = m20 - pow(m10, 2) / m00;
    float M02 = m02 - pow(m01, 2) / m00;
    float M11 = m11 - m10*m01 / m00;
    float M1 = (M20 + M02) / pow(m00, 2);
    float M7 = (M20*M02 - pow(M11, 2)) / pow(m00, 4);
    float S = pole(matBox.first);
    float L = obwod(matBox.first);

    info.M1 = M1;
    info.M7 = M7;
    info.S = S;
    info.L = L;
}
