
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

void GetFileNames(string path,vector<string>& filenames)
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str()))){
        cout<<"Folder doesn't Exist!"<<endl;
        return;
    }
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0){
            filenames.push_back(path + "/" + ptr->d_name);
        }
    }
    closedir(pDir);
}





int main() {
    // Open the file for reading

    int image_width = 640;
    int image_height = 480;

    string dataFolder="../hdr_rgbe";
    std::vector<string> fileNames;
    GetFileNames(dataFolder,fileNames);
    cout<<" \n Show fileNames.size():"<<fileNames.size()<< endl;



    string data_png= "../data/origfovroughness_1.png";
    Mat testImage= imread(data_png, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
    imshow("origfovroughness_1",testImage);
	string ty =  type2str(testImage.type());
	printf("origfovroughness_1: %s %dx%d \n", ty.c_str(), testImage.cols, testImage.rows );


    for (int j = 0; j < testImage.rows; ++j) {
        for (int i = 0; i < testImage.cols; ++i) {

            cout << "\n show  origfovroughness_1" << testImage.at<Vec3b>(j,i);
        }
    }


    double min_depth, max_depth;
    cv::minMaxLoc(testImage, &min_depth, &max_depth);
    cout << "\n show  origfovroughness_1  map min, max:\n" << (double ) 1/5000.0*min_depth << "," << (double ) 1/5000.0*max_depth << endl;




    waitKey(0);


    int max_val_radiance=0;

    for (int i = 1; i < fileNames.size(); ++i) {

        stringstream ss;
        ss<<i;
        string pose_idx_str;
        ss>> pose_idx_str;
        string name_prefix= "origfov_";
        string pose_path="../hdr_rgbe/"+ name_prefix+ pose_idx_str+".rgbe";
        //        ifstream poseFile(pose_path);
        cout<<"show pose_path.c_str():"<<pose_path.c_str()<<endl;
        FILE *fp = fopen( pose_path.c_str(), "rb");




        unsigned char rgbe[4];
        if (fread(rgbe, sizeof(rgbe), 1, fp) < 1) {
            // Handle error or empty file
            std::cout << "false file" << std::endl;
            return 0;
        } else {

            RGBE_ReadHeader(fp, &image_width, &image_height, NULL);

            float *image = (float *) malloc(sizeof(float) * 3 * image_width * image_height);

            RGBE_ReadPixels_RLE(fp, image, image_width, image_height); // read in pixel data in the size of 640 * 480

            Mat envMap(image_height, image_width, CV_32FC3);
            std::memcpy(envMap.data, image, 3 * image_width * image_height * sizeof(float));

//            double min, max;
//            testImage.convertTo(testImage, CV_8UC3, 1.0/255.0);
//        for (int i = 0; i <testImage.rows ; ++i) {
//            for (int j = 0; j < testImage.cols; ++j) {
////                if (testImage.at<Vec3b>(i,j).val[0]==0){ continue;}
//                cout<<"\n show testImage val:"<< testImage.at<Vec3b>(i,j);
//
//            }
//        }

//            cv::minMaxLoc(testImage, &min, &max);
//            cout << "\n show  testImage min, max:\n" << min<< "," << max<< endl;

            double min_inv, max_inv;
            cv::minMaxLoc(envMap, &min_inv, &max_inv);
            cout << "\n show  envMap min, max:\n" << min_inv << "," << max_inv << endl;

            if (max_inv>max_val_radiance){
                max_val_radiance=max_inv;
            }
//            max_inv>max_val_radiance?: max_val_radiance= max_inv; max_val_radiance;
            imshow("pic1", envMap);
            waitKey(0);
        }


        fclose(fp);


    }

    cout << "\n Show  max_val_radiance :\n" << max_val_radiance<<endl;





////    string data_png= "../data/11197.086112.png";

//    FILE *fp = fopen("../origfov_2.rgbe", "rb");
//  FILE *fp = fopen("../every2_replaced_200.rgbe", "rb");

    return 0;
}

// note
//    std::vector<float> one_pixel;
//    float max=0, min=1;
//    for (int i = 0; i < 3 * image_width * image_height; i + 3) {
//
//      one_pixel.push_back(image[i]);
//      one_pixel.push_back(image[i + 1]);
//      one_pixel.push_back(image[i + 2]);
//
//      std::cout << one_pixel[i] << std::endl;
//      std::cout << one_pixel[i + 1] << std::endl;
//      std::cout << one_pixel[i + 2] << std::endl;
//    }

//    for (int i = 0; i <one_pixel.size() ; ++i) {
//      if (one_pixel[i]>max){max=one_pixel[i];}
//      if (one_pixel[i]<min){min=one_pixel[i];}
//    }
//
//    std::cout <<"Max value: "<<max<<std::endl;
//    std::cout <<"Min value: "<<min<<std::endl;

//    const auto [min, max] = std::minmax_element(begin(one_pixel), end(one_pixel));
//    std::cout << "min = " << *min << ", max = " << *max << '\n';