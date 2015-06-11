#include "processing.h"
#include "cutting.h"
#include "moments.h"
#include "opencv2/imgproc/imgproc.hpp"

int main(int, char *[]) {
    std::cout << "Start ..." << std::endl;

    cv::Mat image = cv::imread("3.jpg");

    cv::Mat prog = image;

    double wygladzenie[3][3] ={{1,1,1},
                            {1,4,1},
                            {1,1,1}};

    double wykrywanie_kraw[3][3] = {{-1,-1,-1},
                                 {-1, 8,-1},
                                 {-1,-1,-1}};

//    prog = useMatrixFiltr(prog, 4, initTable3x3(wygladzenie), 3);

//    prog = useMatrixFiltr(prog,1,initTable3x3(wykrywanie_kraw), 3);





//    cv::GaussianBlur(image, g1, cv::Size(51,51), 0);
//    cv::GaussianBlur(image, g2, cv::Size(3,3), 0);

      prog = diffrenceOfGaussian(prog,41,3);



      prog = progowanie(prog, 2, false);

//    prog = rankFilter(prog, 3, 8);
//    prog = rankFilter(prog, 3, 8);

//    prog = rankFilter(prog, 3, 0);
//    prog = rankFilter(prog, 3, 0);
//    prog = rankFilter(prog, 3, 0);
//    prog = rankFilter(prog, 3, 0);
//    prog = rankFilter(prog, 3, 0);

//    MatBoxList list = partitionBoxes(prog);

//    int i = 0;
//    for( MatBox mat : list){
////        cv::imshow(std::to_string(i), mat.first);
//        MatInfo matInfo = doTheMath(mat);
//        printMatInfo(matInfo);
//        ++i;
//    }

    cv::resize(prog,prog,cv::Size(800,600));
    cv::imshow("Filtrowany",prog);
//    cv::imshow("Normalny",image);

//    cv::imwrite("prog.jpeg", max);
//    cv::namedWindow("Max", cv::WINDOW_NORMAL);

    cv::waitKey(-1);
    return 0;
}
