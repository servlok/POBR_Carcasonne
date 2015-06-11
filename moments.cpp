#include "moments.h"

float moment_zwykly(const float &p, const float &q,const cv::Mat& I){

    float m = 0;
    cv::Mat_<cv::Vec3b> _I = I;
    for (int i = 0; i < _I.rows; ++i)
        for (int j = 0; j < _I.cols; ++j)
            if (!_I(i, j)[0])
                m += pow(i, p) * pow(j, q);

    return m;
}

int obwod(const cv::Mat& I){

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
    float m12 = moment_zwykly(1, 2, matBox.first);
    float m21 = moment_zwykly(2, 1, matBox.first);
    float m30 = moment_zwykly(3, 0, matBox.first);
    float m03 = moment_zwykly(0, 3, matBox.first);

    float i = m10/m00;
    float j = m01/m00;

    float M00 = m00;
    float M01 = 0;
    float M10 = 0;
    float M11 = m11 - m10*m01 / m00;
    float M20 = m20 - pow(m10, 2) / m00;
    float M02 = m02 - pow(m01, 2) / m00;
    float M21 = m21 - 2*m11*i - m20*j + 2*m01*pow(i,2);
    float M12 = m12 - 2*m11*j - m02*i + 2*m10*pow(j,2);
    float M30 = m30 - 3*m20*i + 2*m10*pow(i,2);
    float M03 = m03 - 3*m02*j + 2*m01*pow(i,2);

    info.M1 = (M20 + M02) / pow(m00, 2);
    info.M2 = (pow((M20 + M02), 2) + (4 * pow(M11, 2))) / pow(m00, 4);
    info.M3 = (pow((M30 + 3*M12),2) + pow((3*M21 + M03),2))/pow(m00,5);
    info.M4 = (pow((M30 + M12),2) + pow((M21 - M03),2))/pow(m00,5);
    info.M5 = ((M30 - 3*M12)*(M30 + M12)*((pow((M30 + M12),2) - 3*pow((M21 + M03),2)))
               + (3*M21 - M03)*(M21 + M03)*(3*pow((M30 + M12),2) - pow((M21 + M03),2)))
               /pow(m00,10);
    info.M6 = ((M20 - M02)*(pow((M30 + M12),2) - pow((M21 + M03),2)) + 4*M11*(M30 + M12)*(M21 + M03))
               /pow(m00,7);
    info.M7 = (M20*M02 - pow(M11, 2)) / pow(m00, 4);
    info.M8 = (M30*M12 + M21*M03 - pow(M12,2) - pow(M21,2)) / pow(m00,5);
    info.M9 = (M20*(M21*M03 - pow(M12,2)) + M02*(M03*M12 - pow(M21,2)) - M11*(M30*M03 - M21*M12))
               /pow(m00,7);
    info.M10 = (pow((M30*M03 - M12*M21),2) - 4*(M30*M12 - pow(M21,2))*(M03*M21 - M12)) / pow(m00,10);

    info.S = m00;
    info.L = obwod(matBox.first);

    return info;
}

void printMatInfo(const MatInfo& mat)
{
    std::cout<<"M1: "<<mat.M1;
    std::cout<<" M2: "<<mat.M2;
    std::cout<<" M3: "<<mat.M3;
    std::cout<<" M4: "<<mat.M4;
    std::cout<<" M5: "<<mat.M5;
    std::cout<<" M6: "<<mat.M6;
    std::cout<<" M7: "<<mat.M7;
    std::cout<<" M8: "<<mat.M8;
    std::cout<<" M9: "<<mat.M9;
    std::cout<<" M10: "<<mat.M10;
    std::cout<<std::endl;
}
