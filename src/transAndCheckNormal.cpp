//
// Created by lei on 04.05.23.
//


#include "../include/toolBox.h"
#include <boost/filesystem.hpp>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include<opencv2/opencv.hpp>
#include "../include/PFMReadWrite.h"

using namespace std;
using namespace cv;


cv::Mat loadPFMNormal(std::string N_fn)  {

    std::string normal_fn = N_fn;
    cv::Mat normal = loadPFM(normal_fn.c_str());

    // Scale the pixel values to the range [-1, 1]
    cv::Mat normals_c_oneView = 2 * normal - 1;
    // Swap the R and B channels and invert the G and B channels
    cv::Mat normals;
    cv::cvtColor(normals_c_oneView, normals, cv::COLOR_BGR2RGB);
    cv::Mat channels[3];
    cv::split(normals, channels);
    channels[1] = -channels[1];
    channels[2] = -channels[2];
    cv::merge(channels, 3, normals);

    return normals;
}

cv::Mat loadDATNormal(std::string N_fn){
         std::string normal_fn = N_fn;
        float normalArray[480][640][3]={0.0f};
        ifstream readIn(normal_fn, ios::in | ios::binary);
        readIn.read((char*) &normalArray, sizeof normalArray);
        cv::Mat normal_A(480,640,CV_32FC3, &normalArray);
        cv::Mat normal_map_GT = normal_A.clone();
        return normal_map_GT;
}


int main(){

//    string pfmNormalPath = "../data/checkNormal/PFMnormal.pfm";
    string pfmNormalPath = "../data/checkNormal/first.pfm";


    string datNormalPath = "../data/checkNormal/datNormal.dat";
    cv::Mat pfmNormal = loadPFMNormal(pfmNormalPath);
    cv::Mat datNormal = loadDATNormal(datNormalPath);


    cout<<"show pfmNormal depth of image: "<<pfmNormal.depth()<<endl;
    cout<<"show datNormal depth of image: "<<datNormal.depth()<<endl;


    // get the 0 channel of the normal map
    std::vector<cv::Mat> pfmChannels;
    cv::split(pfmNormal, pfmChannels);
    cv::Mat pfmNormal_r=pfmChannels[0];// r


    std::vector<cv::Mat> datChannels;
    cv::split(datNormal, datChannels);
    cv::Mat datNormal_r=datChannels[0];// r

    Mat diff = pfmNormal_r - datNormal_r;

    // show the max and min value of the difference
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    minMaxLoc( diff, &minVal, &maxVal, &minLoc, &maxLoc );
    cout<<"minVal: "<<minVal<<endl;
    cout<<"maxVal: "<<maxVal<<endl;

    imshow("pfmNormal", pfmNormal);
    imshow("datNormal", datNormal);
    waitKey(0);




    return 0;
}