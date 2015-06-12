#include "processing.h"
#include <math.h>

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
                g = (grayScale(_I(i,j)) <= prog) ? 0 : 255;
            else
                g = (grayScale(_I(i,j)) <= prog) ? 255 : 0;

            setGrayScale(_R(i,j), g);
        }
    res = _R;

    return res;
}

cv::Mat useMatrixFiltr(cv::Mat& I, const float& podzielnik, double **matrix, const int& sizeOfMatrix) {
    CV_Assert(I.depth() != sizeof(uchar));
    cv::Mat res(I.rows,I.cols, CV_8UC3);


    int halfOfSize = floor(sizeOfMatrix/2);
    cv::Mat_<cv::Vec3b> _I = I;
    cv::Mat_<cv::Vec3b> _R = res;

    for( int i =0 ; i < halfOfSize; ++i) {
        for( int j = 0; j < I.cols; ++j) {
            _R(i,j)[0] = _I(i,j)[0];
            _R(i,j)[1] = _I(i,j)[1];
            _R(i,j)[2] = _I(i,j)[2];
        }
    }
    for( int j = 0; j < halfOfSize; ++j) {
        for( int i = 0; i < I.rows; ++i) {
            _R(i,j)[0] = _I(i,j)[0];
            _R(i,j)[1] = _I(i,j)[1];
            _R(i,j)[2] = _I(i,j)[2];
        }
    }

    for(int i = I.rows - halfOfSize; i < I.rows; ++i ) {
        for( int j = 0; j < I.cols; ++j) {
            _R(i,j)[0] = _I(i,j)[0];
            _R(i,j)[1] = _I(i,j)[1];
            _R(i,j)[2] = _I(i,j)[2];
        }
    }

    for( int j = I.cols - halfOfSize; j < I.cols; ++j) {
        for( int i = 0; i < I.rows; ++i) {
            _R(i,j)[0] = _I(i,j)[0];
            _R(i,j)[1] = _I(i,j)[1];
            _R(i,j)[2] = _I(i,j)[2];
        }
    }

    for( int i = halfOfSize; i < I.rows - halfOfSize; ++i)
        for( int j = halfOfSize; j < I.cols - halfOfSize; ++j ){
            float suma[3] = {0,0,0};
            int pos_i;
            int pos_j;
            for(int m_i = 0 ; m_i < sizeOfMatrix; ++m_i) {
                for(int m_j = 0 ; m_j < sizeOfMatrix; ++m_j) {
                    pos_i = i + m_i - halfOfSize;
                    pos_j = j + m_j - halfOfSize;
                    suma[0] += matrix[m_i][m_j]*_I(pos_i,pos_j)[0];
                    suma[1] += matrix[m_i][m_j]*_I(pos_i,pos_j)[1];
                    suma[2] += matrix[m_i][m_j]*_I(pos_i,pos_j)[2];
                }
            }
            suma[0] /= podzielnik;
            suma[1] /= podzielnik;
            suma[2] /= podzielnik;
            suma[0] = skorygujPrzedzial(suma[0]);
            suma[1] = skorygujPrzedzial(suma[1]);
            suma[2] = skorygujPrzedzial(suma[2]);
            _R(i,j)[0] = suma[0];
            _R(i,j)[1] = suma[1];
            _R(i,j)[2] = suma[2];
        }
    res = _R;

    return res;
}

cv::Mat gaussianBlur(cv::Mat& I, const int& radius) {
    CV_Assert(I.depth() != sizeof(uchar));
    cv::Mat res(I.rows,I.cols, CV_8UC3);

    //compute kernel funciton
//    double kernel[radius][radius];
    double **kernel = new double *[radius];
      for(int i=0;i<radius;i++)
        kernel[i] = new double [radius];

    double mean = radius/2;
    double sum = 0.0; // For accumulating the kernel values
    for (int x = 0; x < radius; ++x)
        for (int y = 0; y < radius; ++y) {
            kernel[x][y] = exp( -0.5 * (pow((x-mean)/radius, 2.0) + pow((y-mean)/radius,2.0)) )
                             / (2 * M_PI * radius * radius);

            // Accumulate the kernel values
            sum += kernel[x][y];
        }

    // Normalize the kernel
    for (int x = 0; x < radius; ++x)
        for (int y = 0; y < radius; ++y)
            kernel[x][y] /= sum;
    //end of computing kernel function

    res = useMatrixFiltr(I,1,kernel,radius);

    return res;
}

cv::Mat diffrenceOfGaussian(cv::Mat& I, const int&firstRadius, const int& secondRadius) {
    cv::Mat g1, g2;

    g1 = gaussianBlur(I, firstRadius);
    g2 = gaussianBlur(I, secondRadius);

    return g1 - g2;
}

double **initTable3x3(double table[][3]) {
    double **newTable = new double *[3];
    for(int i=0;i<3;i++) {
        newTable[i] = new double[3];
        for(int j=0; j<3; j++){
            newTable[i][j] = table[i][j];
        }
    }

    return newTable;
}
