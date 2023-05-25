//
// Created by lei on 06.01.23.
//


#include "../include/toolBox.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include<opencv2/opencv.hpp>
#include <experimental/filesystem>
#include "../include/PFMReadWrite.h"



int main(){

    string dataFolder="../data/rgb_Image2_pfm";

    string dataFolder_png= "../data/rgb_Image2_png";

    std::vector<string> fileNames;
    GetFileNames(dataFolder,fileNames);
    cout<<" \n Show fileNames.size():"<<fileNames.size()<< endl;

//    string baseColor_num1= "../data/bgrbaseColor_1.pfm";
//    Mat baseColor= loadPFM(baseColor_num1);
//    imshow("baseColor BGR:", baseColor);

    for (int i = 1; i <= fileNames.size(); ++i) {

        stringstream ss;
        ss << i;
        string img_idx_str;
        ss >> img_idx_str;
        string name_prefix = "/bgr_";
        string img_path = dataFolder + name_prefix + img_idx_str + ".pfm";
        string img_png= dataFolder_png+ name_prefix + img_idx_str + ".png";

        cout<<" \n Show img_path :"<<img_path<<endl;
        Mat radiance_img= loadPFM(img_path);
        string ty1 =  type2str(radiance_img.type());
        printf("radiance_img: %s %dx%d \n", ty1.c_str(), radiance_img.cols, radiance_img.rows );

        Mat radiance_png(radiance_img.rows, radiance_img.cols, CV_8UC3);

        for (int j = 0; j < radiance_img.rows; ++j) {
            for (int i = 0; i < radiance_img.cols; ++i) {
//                cout << "\n show  radiance_img val: " << radiance_img.at<Vec3f>(j,i)<<endl;
                radiance_png.at<Vec3b>(j,i)= 255.0 *(ACESFilm(radiance_img.at<Vec3f>(j,i)));
//                radiance_png.at<Vec3b>(j,i)= 255.0 *(HDRToOutput(radiance_img.at<Vec3f>(j,i), 0));
//                cout << "\n show  radiance_png val: " << radiance_png.at<Vec3b>(j,i)<<endl;
            }
        }

        imwrite(img_png, radiance_png);

//        imshow("radiance_img",radiance_img);
//        imshow("radiance_png",radiance_png);
//        waitKey(0);


    }




    cout<<"The conversion is done!"<<endl;


    return 0;
}