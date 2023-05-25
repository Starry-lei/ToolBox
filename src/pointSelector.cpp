//
// Created by lei on 13.01.23.
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
#include <opencv2/ximgproc/slic.hpp>
#include <opencv2/ximgproc/segmentation.hpp>
#include "../include/slic.h"


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


void superPixel_SLIC(int nc, int nr_superpixels, Mat inputImage ){

    // Create an IplImage header
    // IplImage iplImageHeader = normal_A;
    IplImage iplImageHeader = inputImage;
    // Create a pointer to the IplImage header
    IplImage* image = &iplImageHeader;

    IplImage *lab_image = cvCloneImage(image);
    cvCvtColor(image, lab_image, CV_BGR2Lab);
    int w = image->width, h = image->height;

//    int nr_superpixels=100;
//    int nc = 30;
    double step = sqrt((w * h) / (double) nr_superpixels);

    /* Perform the SLIC superpixel algorithm. */
    Slic slic;
    slic.generate_superpixels(lab_image, step, nc);
    slic.create_connectivity(lab_image);

    /* Display the contours and show the result. */
    slic.display_contours(image, CV_RGB(255,0,0));
    cvShowImage("display_contours", image);
    // calculate the center of each superpixel
    slic.display_center_grid(image, CV_RGB(0,0,255));
    cvShowImage("display_center_grid", image);
    cv::Mat center_grid_rgb = cv::cvarrToMat(image);
    imwrite("display_center_grid_rgb.png",center_grid_rgb);


}


int main() {

//    string slamImg_path= "../data/radianceMap_leftSave.png";
//
//    string slamImg_REALpath= "../data/bgr_10TTTTTTTTTTTTTTTT.png";
//    string  metallic= "../data/pointSelector/metallic_10.pfm";
//    string selectedPointMask_path= "../data/selectedPointMask1_selectedPointMask1SSSSSSSSSSSSSSSSSSSSSSS.png";
//    string orig_path= "../data/bgr_10_goalFrame.pfm";


    string slamImg_REALpath= "../data/data_checkingLoss/orig_6.pfm";
    string  metallic= "../data/data_checkingLoss/origmetallic_6.pfm";
    string selectedPointMask_path= "../data/data_checkingLoss/pointMask.png";
    //    string orig_path= "../data/bgr_10_goalFrame.pfm";
    string roughtness_path= "../data/data_checkingLoss/origroughness_6.pfm";//    string roughtness_path= "../data/roughness_1000000000000000000000000.pfm";
    string image_normal_GT_path= "../data/data_checkingLoss/orignormal_6.dat";
    string baseColor_path= "../data/data_checkingLoss/origbaseColor_6.pfm";//

    string envMapWork_path= "../data/data_checkingLoss/envMapWorkMap.png";//






    float normalArray[480][640][3]={0.0f};
    ifstream readIn(image_normal_GT_path, ios::in | ios::binary);
    readIn.read((char*) &normalArray, sizeof normalArray);
    cv::Mat normal_A(480,640,CV_32FC3, &normalArray);



//  Mat readRealImage= imread(slamImg_REALpath, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
    Mat readRealImage= loadPFM(slamImg_REALpath);

    Mat baseColorImage= loadPFM(baseColor_path);

    Mat envMapWork= imread(envMapWork_path, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);

    Mat readRealImage_CV8U;
    readRealImage.convertTo(readRealImage_CV8U,CV_8UC3);
    imwrite("readRealImage_CV8U.png", readRealImage_CV8U);
    Mat grayImg, mat_mean, mat_stddev;
    extractChannel(readRealImage, grayImg, 1);
    meanStdDev(grayImg, mat_mean, mat_stddev);
    double m,std;
    m= mat_mean.at<double>(0,0);
    std= mat_stddev.at<double>(0,0);
    Mat orig_mat= loadPFM(slamImg_REALpath);
    Mat roughtness= loadPFM(  roughtness_path);
    Mat metallic_tet= loadPFM(metallic);
    extractChannel(roughtness, roughtness, 1);
    extractChannel(metallic_tet, metallic_tet, 1);
    Mat selectedPointMask= imread(selectedPointMask_path, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);


    imshow("DSO_selector",selectedPointMask);
    setMouseCallback("DSO_selector",onMouse_intType,reinterpret_cast<void*>(&selectedPointMask));//鼠标响应函数

    imshow("envMapWork",envMapWork);
    setMouseCallback("envMapWork",onMouse_intType,reinterpret_cast<void*>(&envMapWork));//鼠标响应函数

    imshow("orig_img: ",orig_mat);
    Mat sPointMask(selectedPointMask.rows,  selectedPointMask.cols, CV_8UC1, Scalar(0));
    Mat sPointLambertianMask(selectedPointMask.rows,  selectedPointMask.cols, CV_8UC1, Scalar(0));

    imshow("metallic_tet", metallic_tet);
    setMouseCallback("metallic_tet",onMouse_floatType,reinterpret_cast<void*>(&metallic_tet));//鼠标响应函数

    imshow("baseColorImage", baseColorImage);
    setMouseCallback("baseColorImage",onMouse_floatType,reinterpret_cast<void*>(&baseColorImage));//鼠标响应函数

    imshow("normal_A", normal_A);
    setMouseCallback("normal_A",onMouse_floatType,reinterpret_cast<void*>(&normal_A));//鼠标响应函数

    imshow("readRealImage", readRealImage);
    setMouseCallback("readRealImage",onMouse_floatType,reinterpret_cast<void*>(&readRealImage));//鼠标响应函数


    imshow("roughtness", roughtness);
    setMouseCallback("roughtness",onMouse_floatType,reinterpret_cast<void*>(&roughtness));//鼠标响应函数








//    Image averge:95.3069
//    Image std:77.3234

//  notes:   m      r      sigma    numPoints  remark
//   1       0.8,   0.2    0.8      3250       part ground
//   2       0.8,   0.2    0.65     6054       part ground
//   3       0.8,  0.15    0.6     6001       part ground

//  notes:   m      r      sigma    numPoints  remark
//   1       0.8,   0.3    0.6     3745         with metallic=1
//   3       0.8,   0.3    0.7     2775         part ground
//   3       0.8,   0.3    0.8     1995         part ground
    float metallic_threshold = 0.8;  // 0.8
    float roughness_threshold = 0.3;
    float scale_std= 0.6;



// --------------------------------interest area-----------------------------------------------------
    Vec2i boundingBoxUpperLeft( 262,244);
    Vec2i boundingBoxBotRight(480, 640);
    ofstream envPixelPointfile;
    envPixelPointfile.open ("envPixelPointfile.txt");
    int point_counter=0;
    int dso_point_counter=0;
    for (int j = 0; j < metallic_tet.rows; ++j) {
        for (int i = 0; i < metallic_tet.cols; ++i) {

//            if ( (i<boundingBoxUpperLeft.val[1] || i>boundingBoxBotRight.val[1]) || (j< boundingBoxUpperLeft.val[0] ||  j> boundingBoxBotRight.val[0])){ continue;}

            if (int (selectedPointMask.at<uchar>(j,i))==255){

                dso_point_counter+=1;

                if (static_cast<int>(roughtness.at<float>(j, i)) ==1){ continue;}
                    //if (static_cast<int>(metallic_tet.at<float>(j, i)) ==1){ continue;}
                    if ( (roughtness.at<float>(j,i) < roughness_threshold || metallic_tet.at<float>(j,i)>metallic_threshold) && (readRealImage.at<Vec3f>(j,i)[1]>(m+scale_std*std) ))
                    {
                        sPointMask.at<uchar>(j,i)= 255;
                        envPixelPointfile << j<<" "<<i<<"\n";
                        point_counter+=1;
                    }



            }
        }
    }
    envPixelPointfile.close();

    imshow("sPointMask", sPointMask);
    setMouseCallback("sPointMask",onMouse_intType,reinterpret_cast<void*>(&sPointMask));//鼠标响应函数


    // ========================================================select lambertian points=====================================
    ofstream LambertianPixelPointfile;
    LambertianPixelPointfile.open ("LambertianPixelPointfile.txt");
    int point_counter_lam=0;
    int dso_point_counter_lam=0;

    int save_ratio=3;

    for (int j = 0; j < metallic_tet.rows; ++j) {
        for (int i = 0; i < metallic_tet.cols; ++i) {

            if ( (i<boundingBoxUpperLeft.val[1] || i>boundingBoxBotRight.val[1]) || (j< boundingBoxUpperLeft.val[0] ||  j> boundingBoxBotRight.val[0])){

                                if (int (selectedPointMask.at<uchar>(j,i))==255) {
                                                        dso_point_counter_lam+=1;
                                    if ((j * metallic_tet.cols + i) % save_ratio != 0) { continue; }
                                    sPointLambertianMask.at<uchar>(j, i) = 255;
                                    point_counter_lam += 1;

                                }

//                if (int (selectedPointMask.at<uchar>(j,i))==255){
//                    dso_point_counter_lam+=1;
//                    if (static_cast<int>(metallic_tet.at<float>(j, i)) ==1){ continue;}
//                    if (static_cast<int>(roughtness.at<float>(j, i)) ==1  ||  (readRealImage.at<Vec3f>(j,i)[1]<(m - 0.2*std ))){
//                        sPointLambertianMask.at<uchar>(j,i)= 255;
//                        LambertianPixelPointfile << j<<" "<<i<<"\n";
//                        point_counter_lam+=1;
//
//                    }
//
////                    if (  (readRealImage.at<Vec3f>(j,i)[1]<(m+scale_std*std))){
////                        sPointLambertianMask.at<uchar>(j,i)= 255;
////                        envPixelPointfile << j<<" "<<i<<"\n";
////                        point_counter_lam+=1;
////                    }
//// for 17512
////                    if (  (readRealImage.at<Vec3f>(j,i)[1]<(m - 0.1*std ))){
////                        sPointLambertianMask.at<uchar>(j,i)= 255;
////                        envPixelPointfile << j<<" "<<i<<"\n";
////                        point_counter_lam+=1;
////                    }
//// for 14976
////                    if (  (readRealImage.at<Vec3f>(j,i)[1]<(m - 0.1*std )) ){
////                        sPointLambertianMask.at<uchar>(j,i)= 255;
////                        LambertianPixelPointfile << j<<" "<<i<<"\n";
////                        point_counter_lam+=1;
////                    }
//                }

            }


        }

    }
    LambertianPixelPointfile.close();

    imshow("sPointLambertianMask", sPointLambertianMask);
    setMouseCallback("sPointLambertianMask",onMouse_intType,reinterpret_cast<void*>(&sPointLambertianMask));//鼠标响应函数

    // =================try to select non_lambertian surface using superpixel======================



    cv::Mat outFrame;  // Result output
    readRealImage.copyTo(outFrame, selectedPointMask);
    imshow("checkMaskedBaseColor", outFrame);
    superPixel_SLIC(30, 100, outFrame);
    cvWaitKey(0);




    std::cerr<<"\n show point_counter:"<<point_counter<<endl;
    std::cerr<<"\n show dso_point_counter:"<<dso_point_counter<<endl;

    std::cerr<<"\n show point_counter_lam:"<<point_counter_lam<<endl;
    std::cerr<<"\n show dso_point_counter_lam:"<<dso_point_counter_lam<<endl;

    cout<<"\n Image averge:"<< m<<endl;
    cout<<"\n Image std:"<<std<<endl;
    imwrite("pointMask_new.png", sPointMask);
    imwrite("sPointLambertianMask.png", sPointLambertianMask);

    waitKey(0);

    return 0;
}