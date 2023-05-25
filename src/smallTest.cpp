//
// Created by lei on 23.01.23.
//


#include "../include/toolBox.h"
#include <boost/filesystem.hpp>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include<opencv2/opencv.hpp>
#include <experimental/filesystem>
#include "../include/PFMReadWrite.h"

#include <boost/version.hpp>

void onMouse_intType(int event,int x,int y,int flags,void* param)
{
    Mat* im = reinterpret_cast<Mat*>(param);
    switch(event)
    {
        case EVENT_LBUTTONDOWN:
            //左键按下显示像素值
            if (static_cast<int>(im->channels())==1)
            {
                //若为灰度图，显示鼠标点击的坐标以及灰度值
                std::cout<<"at("<<y<<","<<x<<")value is:"<<static_cast<int>(im->at<int>(y,x))<<endl;
            }
            else if (static_cast<int>(im->channels() == 3))
            {
                //若图像为彩色图像，则显示鼠标点击坐标以及对应的B, G, R值
                std::cout << "at (" << y << ", " << x << ")"
                          << "  B value is: " << static_cast<int>(im->at<Vec3b>(y, x)[0])
                          << "  G value is: " << static_cast<int>(im->at<Vec3b>(y, x)[1])
                          << "  R value is: " << static_cast<int>(im->at<Vec3b>(y, x)[2])
                          << endl;
            }
    }
}


void onMouse_floatType(int event,int x,int y,int flags,void* param)
{
    Mat* im = reinterpret_cast<Mat*>(param);
    switch(event)
    {
        case EVENT_LBUTTONDOWN:
            //左键按下显示像素值
            if (static_cast<int>(im->channels())==1)
            {
                //若为灰度图，显示鼠标点击的坐标以及灰度值
                std::cout<<"at("<<y<<","<<x<<")value is:"<<static_cast<float>(im->at<float>(y,x))<<endl;
            }
            else if (static_cast<int>(im->channels() == 3))
            {
                //若图像为彩色图像，则显示鼠标点击坐标以及对应的B, G, R值
                std::cout << "at (" << y << ", " << x << ")"
                          << "  B value is: " << static_cast<float>(im->at<Vec3f>(y, x)[0])
                          << "  G value is: " << static_cast<float>(im->at<Vec3f>(y, x)[1])
                          << "  R value is: " << static_cast<float>(im->at<Vec3f>(y, x)[2])
                          << endl;
            }
    }
}

// g: 108, 97    105, 119     105, 117      106, 111
// s: 98, 202
// s2: 95, 242
// b: 125, 102


int main() {



//    string setPFMZero_path = "/media/lei/Data/Kitchen_scene/EnvMap_Kitchen/envMap1/envMapImage.pfm";
//    string PFMIamge02_path = "/media/lei/Data/LivingRoom_scene/testImage/bgr_2.pfm";
////    string PFMIamge03_path = "/media/lei/Data/LivingRoom_scene/testImage/bgr_3.pfm";
//
//    string PFMIamge03_path = "/media/lei/Data/LivingRoom_scene/2frame0370_02/pfm/orig_6.pfm";

    string PFMIamge06_path = "../data/tt/ptc_1.png";
    string PFMIamge07_path = "../data/tt/rgbp_1.png";

    string testDepth ="../data/poseData/testDepth.png";



    Mat PFMIamge06= imread(PFMIamge06_path, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
    Mat PFMIamge07= imread(PFMIamge07_path, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
    Mat depthImage= imread(testDepth, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);

    cout<<"depthImage type: "<<depthImage.type()<<endl;




    Mat greenChn06, greenChn07, greenBaseColor;

        string ty1 =  type2str(PFMIamge06.type());
        printf("ptc_1: %s %dx%d \n", ty1.c_str(), PFMIamge06.cols, PFMIamge06.rows );
        string ty2 =  type2str(PFMIamge07.type());
        printf("rgbp_1: %s %dx%d \n", ty2.c_str(), PFMIamge07.cols, PFMIamge07.rows );
//
//
//    imshow("checkOutput", img);
//
//    for (int j = 0; j < img.rows; ++j) {
//        for (int i = 0; i < img.cols; ++i) {
//            cout << "\n show  Output data_bgr_1: " << img.at<float>(j,i)<<endl;
//        }
//    }
//    printf("Output Image format: %s %dx%d \n", ty1.c_str(), img.cols, img.rows );
//    waitKey(0);





    extractChannel(PFMIamge06,greenChn06,1);
    extractChannel(PFMIamge07,greenChn07,1);


    double min_PFMIamge06, max_PFMIamge06;
    cv::minMaxLoc(greenChn06, &min_PFMIamge06, &max_PFMIamge06);

    double min_PFMIamge06_base, max_PFMIamge06_base;
    cv::minMaxLoc(greenBaseColor, &min_PFMIamge06_base, &max_PFMIamge06_base);

    double min_PFMIamge07, max_PFMIamge07;
    cv::minMaxLoc(greenChn07, &min_PFMIamge07, &max_PFMIamge07);

    std::cout << "\n show PFMIamge06 max, min val: " << max_PFMIamge06 << ", " << min_PFMIamge06 <<endl;
    std::cout << "\n show min_PFMIamge07 max, min val: " << max_PFMIamge07 << ", " << min_PFMIamge07 <<endl;



    // tone mapping
    Mat radiance_png(PFMIamge06.rows, PFMIamge06.cols, CV_8UC3);

//    for (int j = 0; j < PFMIamge06.rows; ++j) {
//        for (int i = 0; i < PFMIamge06.cols; ++i) {
//
////                cout << "\n show  radiance_img val: " << radiance_img.at<Vec3f>(j,i)<<endl;
//            radiance_png.at<Vec3b>(j,i)= 255.0 *(ACESFilm(PFMIamge06.at<Vec3f>(j,i)));
////                radiance_png.at<Vec3b>(j,i)= 255.0 *(HDRToOutput(radiance_img.at<Vec3f>(j,i), 0));
////                cout << "\n show  radiance_png val: " << radiance_png.at<Vec3b>(j,i)<<endl;
//
//        }
//    }
//
//    imshow("radiance_png",radiance_png);
//
//    cv::waitKey(0);
//
//    imwrite("PFMIamge06_pfm2png.png", 255*PFMIamge06);
//    imwrite("PFMIamge07_pfm2png.png", 255*PFMIamge07);
//    imwrite("PFMIamge06.png", radiance_png);
//


    imshow("PFMIamge06", PFMIamge06);
    setMouseCallback("PFMIamge06",onMouse_intType,reinterpret_cast<void*>(&PFMIamge06));//鼠标响应函数

    imshow("PFMIamge07", PFMIamge07);
    setMouseCallback("PFMIamge07",onMouse_intType,reinterpret_cast<void*>(&PFMIamge07));//鼠标响应函数




    waitKey(0);


//    Mat grHistogram(512, 1024, CV_32FC3, Scalar(NAN, NAN, NAN));
//    savePFM(grHistogram, "grHistogram.pfm");


    return 0;
}

// notes

// channel 0  b
//show PFMIamge06 max, min val: 16.8642, 8.09082e-06
//show min_PFMIamge07 max, min val: 17.1422, 3.6594e-05

//channel 1  g
//show PFMIamge06  green channel max, min val: 65.6489, 0.000327137
//show min_PFMIamge07  green channel max, min val: 66.8211, 0.000224367


// channel 2  r
//show PFMIamge06 max, min val: 141.909, 0.000160449
//show min_PFMIamge07 max, min val: 144.329, 0.00129696