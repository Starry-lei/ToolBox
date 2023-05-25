#include "../include/toolBox.h"

#include <boost/filesystem.hpp>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include<opencv2/opencv.hpp>

int main(){

//    string depthPath = "../data/depthChecking/0000000000031666668.png";

    string depthPath = "../data/depthChecking/11197.086112.png";


    Mat depth = imread(depthPath, IMREAD_ANYDEPTH);
    // print the type of depth
    cout << "depth type: " << depth.type() << endl;
    // print all the depth value in the type of 16uc1
    for (int i = 0; i < depth.rows; i++){
        for (int j = 0; j < depth.cols; j++){

            if (static_cast<float>(depth.at<ushort>(i, j))==0.0){ continue;}

            cout << static_cast<float>(depth.at<ushort>(i, j))/5000.0 << " ";
        }
        cout << endl;
    }


    return 0;
}