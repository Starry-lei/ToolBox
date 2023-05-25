//
// Created by lei on 10.01.23.
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


void checkOutput( string path){

    Mat img= loadPFM(path);
    string ty1 =  type2str(img.type());


    imshow("checkOutput", img);

    for (int j = 0; j < img.rows; ++j) {
        for (int i = 0; i < img.cols; ++i) {
            cout << "\n show  Output data_bgr_1: " << img.at<float>(j,i)<<endl;
        }
    }
    printf("Output Image format: %s %dx%d \n", ty1.c_str(), img.cols, img.rows );
    waitKey(0);
}


int main() {

//    string checkPath= "../data/formattedRoughness/roughness_1.pfm";
//    checkOutput(checkPath);
//    std::string data_Folder="/media/lei/Data/Kitchen_scene/Image_data/roughness";
//    std::string Output_Folder="../data/formattedRoughness";


    string checkPath= "/home/lei/Documents/Research/dataset/relativePoseDataSet/roughness/origroughness_1.pfm";
    checkOutput(checkPath);
//    std::string data_Folder="/media/lei/Data/Kitchen_scene/Image_data/roughness";
//    std::string Output_Folder="../data/formattedRoughness";

///media/lei/Data/datasetProcessing/ToolBox/data/formattedMetallic





    std::string data_Folder="/home/lei/Documents/Research/dataset/relativePoseDataSet/roughness";
    std::string Output_Folder="/home/lei/Documents/Research/dataset/relativePoseDataSet/for";


    std::vector<string> fileNames;
    GetFileNames(data_Folder,fileNames);
    cout<<" \n Show fileNames.size():"<<fileNames.size()<< endl;
    cout<<" \n Show fileNames(1):"<<fileNames[0]<< endl;

    Mat widthHeight= loadPFM(fileNames[0]);
//    Mat data_C1(widthHeight.rows, widthHeight.cols, CV_32FC1, Scalar(1) );


    for (int i = 1; i <= fileNames.size(); ++i) {

        stringstream ss;
        ss << i;
        string img_idx_str;
        ss >> img_idx_str;
//        string name_prefix = "/bgrroughness_";//bgrmetallic_1
//        string newName_prefix = "/roughness_";

        string name_prefix = "/origroughness_";//bgrmetallic_1
        string newName_prefix = "/metallic_";

        string img_path = data_Folder + name_prefix + img_idx_str + ".pfm";
        string outPutDataPath= Output_Folder+newName_prefix + img_idx_str + ".pfm";

        cout<<" \n Show img_path :"<<img_path<< endl;
        Mat img= loadPFM(img_path);
        string ty1 =  type2str(img.type());
        printf("Image format: %s %dx%d \n", ty1.c_str(), img.cols, img.rows );

//    for (int j = 0; j < img.rows; ++j) {
//            for (int i = 0; i < img.cols; ++i) {
//                cout << "\n show  data_bgr_1: " << img.at<Vec3f>(j,i)<<endl;
//            }
//        }
//        imshow("img",img);
//        waitKey(0);

        Mat data_C1[3];
        split(img, data_C1);
        savePFM(data_C1[0], outPutDataPath);



    }












    return 0;
}