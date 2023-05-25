//
// Created by lei on 24.12.22.
//
#include "../rgbe.h"
#include <ctype.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include "../rgbe.c"
#include <iostream>
#include <vector>
#include <memory>
#include "../include/toolBox.h"
#include <sstream>
#include <dirent.h>

#include "../include/PFMReadWrite.h"


int main(){

    int image_width = 640;
    int image_height = 480;

//    string  env_map_path= "../fourColorProblem/ctrlPointMask.png";

    string  env_map_path= "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/cmake-build-release/ctrlPointMask.png";



    Mat Image_8u3= imread(env_map_path, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
    imshow("Image_8u3",Image_8u3);    double min_depth12, max_depth12;
    cv::minMaxLoc(Image_8u3, &min_depth12, &max_depth12);
    cout << "\n show  _BGR_10  map min, max:\n" <<min_depth12 << "," << max_depth12 << endl;
    string ty1 =  type2str(Image_8u3.type());
    printf("envMap_01: %s %dx%d \n", ty1.c_str(), Image_8u3.cols, Image_8u3.rows );


    std::unordered_map<int, int> sortsCtrl;


    for (int u = 0; u < Image_8u3.rows; u++) // colId, cols: 0 to 480
    {
        for (int v = 0; v < Image_8u3.cols; v++) // rowId,  rows: 0 to 640
        {
            if (Image_8u3.at<Vec3w>(u, v)[0]==0){ continue;}

            cout<<"\n show vals:"<< Image_8u3.at<Vec3w>(u, v)<<endl;
            sortsCtrl.emplace((int)Image_8u3.at<Vec3w>(u, v)[0], 1);

        }
    }

    cout<<"show sortsCtrl size:"<< sortsCtrl.size()<<endl;





    waitKey(0);



    return 0;
}

//ote

//    Mat data_envMap= loadPFM(envMap);
//    Mat data_envMap_alpha= loadPFM(envMap_alpha);
//
//
//    Mat data_pfm= loadPFM(data_pfm_path);
////    cvtColor(data_pfm,data_pfm, CV_BGR2RGB);
//    Mat data_baseColor_pfm= loadPFM(data_baseColor_pfm_path);
//
////    cvtColor(data_baseColor_pfm,data_baseColor_pfm, CV_BGR2RGB);
//
//    imshow("data_pfm",data_pfm);
//    imshow("data_baseColor_pfm",data_baseColor_pfm);

//
//
//
//    waitKey(0);
//    imshow("data_envMap",data_envMap);
//    imshow("data_envMap_alpha",data_envMap_alpha);
//    Mat data_bgr_1= loadPFM(envMap_alpha);
//    imshow("data_bgr_1",data_bgr_1);
////


//
//    show  _BGR_10  map min, max:
//    2.8228e-17,20.9158


//    for (int j = 0; j < envMap_01.rows; ++j) {
//        for (int i = 0; i < envMap_01.cols; ++i) {
//            cout << "\n show  envMap_01: " << envMap_01.at<Vec3f>(j,i)<<endl;
//        }
//    }
////    depth_data_pfm_10=1.0/5000.0*depth_data_pfm_10;




//    show  envMap_01: [0.149808, 0.713888, 2.08151]
//
//    show  envMap_01: [0.162121, 0.787876, 2.09342]
//
//    show  envMap_01: [0.160609, 0.730476, 2.0339]
//
//    show  envMap_01: [0.152747, 0.688464, 1.90674]
//
//
//    savePFM(data_bgr_1, "data_bgr_1.pfm");
//
//
//    Mat data_bgr_2= loadPFM("data_bgr_1.pfm");
//    string ty2 =  type2str(data_bgr_2.type());
//    printf("data_bgr_2: %s %dx%d \n", ty2.c_str(), data_bgr_2.cols, data_bgr_2.rows );
//


//    Mat rediance_pfm10 = loadPFM(data_pfm10);
//    Mat rediance_pfm11 = loadPFM(data_pfm11);
//    Mat rediance_pfm12 = loadPFM(data_pfm12);
//    Mat rediance_pfm13 = loadPFM(data_pfm13);
//    Mat rediance_pfm14 = loadPFM(data_pfm14);


//    imshow("rediance_pfm",rediance_pfm10);
//    imshow("rediance_pfm11",rediance_pfm11);
//    imshow("rediance_pfm12",rediance_pfm12);
//    imshow("rediance_pfm13",rediance_pfm13);
//    imshow("rediance_pfm14",rediance_pfm14);


//    string ty =  type2str(rediance_pfm11.type());
//    printf("rediance_pfm11: %s %dx%d \n", ty.c_str(), rediance_pfm11.cols, rediance_pfm11.rows );
//    cout<<"sample point 11: "<< rediance_pfm11.at<Vec3f>(10,10)<<endl;
//    string ty12 =  type2str(rediance_pfm12.type());
//    printf("rediance_pfm12: %s %dx%d \n", ty12.c_str(), rediance_pfm12.cols, rediance_pfm12.rows );
//    cout<<"sample point 12: "<< rediance_pfm12.at<Vec3f>(10,10)<<endl;
//    double min_depth, max_depth;
//    cv::minMaxLoc(rediance_pfm11, &min_depth, &max_depth);
//    cout << "\n show  rediance_pfm11  map min, max:\n" <<min_depth << "," << max_depth << endl;






