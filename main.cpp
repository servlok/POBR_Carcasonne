#include "processing.h"
#include "cutting.h"
#include "moments.h"
#include "opencv2/imgproc/imgproc.hpp"

int main(int, char *[]) {
    std::cout << "Start ..." << std::endl;

    cv::Mat image = cv::imread("2.jpg");
    cv::Mat prog = progowanie(image, 150, false);

    prog = rankFilter(prog, 3, 0);
    prog = rankFilter(prog, 3, 0);
    prog = rankFilter(prog, 3, 0);

    MatBoxList list = partitionBoxes(prog);

    int i = 0;
    for( MatBox mat : list){
        cv::imshow(std::to_string(i), mat.first);
//        MatInfo matInfo = doTheMath(mat);
//        printMatInfo(matInfo);
        ++i;
    }

//    cv::resize(prog,prog,cv::Size(300,300));
    cv::imshow("Filtrowany",prog);
//    cv::imshow("Normalny",image);

//    cv::imwrite("prog.jpeg", max);
//    cv::namedWindow("Max", cv::WINDOW_NORMAL);

    cv::waitKey(-1);
    return 0;
}
