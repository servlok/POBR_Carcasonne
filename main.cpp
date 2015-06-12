#include "processing.h"
#include "cutting.h"
#include "moments.h"
#include "opencv2/imgproc/imgproc.hpp"

int main(int, char *[]) {
    std::cout << "Start ..." << std::endl;

    std::string folderToSaveTransformed = "/home/servlok/Projekty/POBR_Carcasonne/img/transformed/";
    std::string folderToSaveMoments = "/home/servlok/Projekty/POBR_Carcasonne/img/momenty/";
    std::string folder = "home/servlok/Projekty/POBR_Carcasonne/img/toTest/";

    for (int i = 11; i <= 11; ++i) {
    std::string image_name = folder;
    image_name.append(std::to_string(i));
//    std::string image_name = std::to_string(i);
    image_name.append(".jpg");
    cv::Mat image = cv::imread(image_name);

    cv::Mat prog = image;

    double wygladzenie[3][3] ={{1,1,1},
                            {1,1,1},
                            {1,1,1}};

//    double wykrywanie_kraw[3][3] = {{-1,-1,-1},
//                                 {-1, 8,-1},
//                                 {-1,-1,-1}};

//    prog = useMatrixFiltr(prog, 4, initTable3x3(wygladzenie), 3);

//    prog = useMatrixFiltr(prog,1,initTable3x3(wykrywanie_kraw), 3);


//    cv::GaussianBlur(image, g1, cv::Size(51,51), 0);
//    cv::GaussianBlur(image, g2, cv::Size(3,3), 0);

//        prog = gaussianBlur(prog,10);

      prog = diffrenceOfGaussian(prog,51,3);

//      prog = useMatrixFiltr(prog,1,initTable3x3(wygladzenie),3);

//      prog = useMatrixFiltr(prog,1,initTable3x3(wygladzenie),3);


      prog = progowanie(prog, 2, false);


//    prog = rankFilter(prog, 3, 8);
//    prog = rankFilter(prog, 3, 0);

//    MatBoxList list = partitionBoxes(progx);

//    std::string folderToSaveMomentsIteration = folderToSaveMoments;
//    folderToSaveMomentsIteration.append(std::to_string(i));

//    int j = 0;
//    for( MatBox mat : list){
//        std::string file = folderToSaveMomentsIteration;
//        cv::imwrite(file.append(std::to_string(j).append(".jpg")), mat.first);
//        MatInfo matInfo = doTheMath(mat);
//        std::cout<<"\tBox numer. "<<j;
//        printMatInfo(matInfo);
//        ++j;
//    }

//    cv::resize(prog,prog,cv::Size(800,600));
    cv::imshow("Filtrowany",prog);

    std::string file = folderToSaveTransformed;

    cv::imwrite(file.append(std::to_string(i)).append(".jpg"),prog);

        std::cout<<std::endl<<"Done";
    }
    cv::waitKey(-1);
    return 0;
}
