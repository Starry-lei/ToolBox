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


//    string dataFolder_png= "../data/rgb_Image2_png"; //
//    string dataFolder_png= "../data/newdepth_Seq2";
//    string data_Folder_timeStamp= "../data/depth_Image2_png_timestamp/";


//    string dataFolder_png= "/media/lei/Data/datasetPBA/morelightpfm/depth";
//    string data_Folder_timeStamp= "/media/lei/Data/datasetPBA/morelightpfm/depth_timeStamp/";

    string dataFolder_png= "/media/lei/Data/datasetPBA/normal";
    string data_Folder_timeStamp= "/media/lei/Data/datasetPBA/normal_timeStamp/";


    bool usePNGFile= false;
    bool isRoughness= false;


    std::vector<string> fileNames;
    GetFileNames(dataFolder_png,fileNames);
    cout<<" \n Show fileNames.size():"<<fileNames.size()<< endl;

    double init_time_stamp = 10000.000000;
    double rate = 0.033333; // 1/30=0.033333 s



    for (int i = 0; i < fileNames.size(); ++i) {

        stringstream ss;
        ss << (i+1);
        string img_idx_str;
        ss >> img_idx_str;
        string name_prefix = "/orignormal_";
        string img_path;

        Mat rgb_data_png;
        Mat rgb_data_pfm;
        if (usePNGFile){
             img_path = dataFolder_png + name_prefix + img_idx_str + ".png";
            rgb_data_png= imread(img_path, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
            double cur_time_stamp = init_time_stamp + rate*i;
            string new_img_path= data_Folder_timeStamp+ to_string(cur_time_stamp) + ".png";
//        cout<<" \n new Show img_path :"<<new_img_path<< endl;
            imwrite(new_img_path, rgb_data_png);
        }else{
             img_path = dataFolder_png + name_prefix + img_idx_str + ".pfm";
             rgb_data_pfm= loadPFM(img_path);

            if (isRoughness){
               // only use one channel of the roughness image
                extractChannel(rgb_data_pfm,rgb_data_pfm,0);
            }

            cout<<" \n Show rgb_data_pfm channels :"<<rgb_data_pfm.channels()<< endl;


            double cur_time_stamp = init_time_stamp + rate*i;
            string new_img_path= data_Folder_timeStamp+ to_string(cur_time_stamp) + ".pfm";
//        cout<<" \n new Show img_path :"<<new_img_path<< endl;
            savePFM(rgb_data_pfm,new_img_path);

        }



////        cout<<" \n Show img_path :"<<img_path<< endl;
//        double cur_time_stamp = init_time_stamp + rate*i;
//        string new_img_path= data_Folder_timeStamp+ to_string(cur_time_stamp) + ".png";
////        cout<<" \n new Show img_path :"<<new_img_path<< endl;
//        imwrite(new_img_path, rgb_data_png);
////        imshow("radiance_img",rgb_data_png);
////        imshow("radiance_png",radiance_png);
////        waitKey(0);


    }

    cout<<"Rename is done!"<<endl;



    return 0;
}


