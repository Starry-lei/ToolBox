#include "../include/toolBox.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include<opencv2/opencv.hpp>
#include <experimental/filesystem>
#include "../include/PFMReadWrite.h"

int main(){

//    string dataFolder="../savePFMAsPNG/PFM1T9";
//    string dataFolder_png= "../savePFMAsPNG/PNG1T9";

//    string dataFolder="/media/lei/Data/datasetPBA/pfm";
//    string dataFolder_png= "/media/lei/Data/datasetPBA/rgb";

    string dataFolder="/media/lei/Data/datasetPBA/morelightpfm/pfm";
    string dataFolder_png= "/media/lei/Data/datasetPBA/morelightpfm/rgb_jpg";



    std::vector<string> fileNames;
    std::vector<string> Names;
    GetFileNames(dataFolder,fileNames,Names);
    cout<<" \n Show fileNames.size():"<<fileNames.size()<< endl;


    for (int i = 1; i <= fileNames.size(); ++i) {

        cout<<" \n Show fileNames[i-1]:"<<fileNames[i-1]<< endl;
        Mat radiance_img= loadPFM(fileNames[i-1]);
//        imshow("radiance_img",radiance_img);
        string image_png_path= dataFolder_png + "/" + Names[i-1] + ".jpg";
        cv::imwrite(image_png_path,radiance_img*255);
//        waitKey(0);

//
//        stringstream ss;
//        ss << i;
//        string img_idx_str;
//        ss >> img_idx_str;
//        string name_prefix = "/orig_";
//        string img_path = dataFolder + name_prefix + img_idx_str + ".pfm";
//        string img_png= dataFolder_png+ name_prefix + img_idx_str + ".png";
//
//        cout<<" \n Show img_path :"<<img_path<<endl;
//        Mat radiance_img= loadPFM(img_path);
//        string ty1 =  type2str(radiance_img.type());
//        printf("radiance_img: %s %dx%d \n", ty1.c_str(), radiance_img.cols, radiance_img.rows );
//
//        Mat radiance_png(radiance_img.rows, radiance_img.cols, CV_8UC3);
//
//        for (int j = 0; j < radiance_img.rows; ++j) {
//            for (int i = 0; i < radiance_img.cols; ++i) {
//
////                cout << "\n show  radiance_img val: " << radiance_img.at<Vec3f>(j,i)<<endl;
//                radiance_png.at<Vec3b>(j,i)= 255.0 *(ACESFilm(radiance_img.at<Vec3f>(j,i)));
////                radiance_png.at<Vec3b>(j,i)= 255.0 *(HDRToOutput(radiance_img.at<Vec3f>(j,i), 0));
////                cout << "\n show  radiance_png val: " << radiance_png.at<Vec3b>(j,i)<<endl;
//
//            }
//        }
//
//        imwrite(img_png, radiance_png);
//
////        imshow("radiance_img",radiance_img);
////        imshow("radiance_png",radiance_png);
////        waitKey(0);


    }




    cout<<"The conversion is done!"<<endl;


    return 0;
}

