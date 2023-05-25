//
// Created by lei on 26.12.22.
//
#include "../include/toolBox.h"
#include <dirent.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include<opencv2/opencv.hpp>
#include <experimental/filesystem>
#include "../include/PFMReadWrite.h"
#include <sys/stat.h>


typedef uint8_t u8;


/***** Global Variables *****/


/***** Global Variables *****/
//char dir[100] = "../rgb";// /media/lei/Data/Kitchen_scene/Image_data/normal

char dir[100] = "/media/lei/Data/Kitchen_scene/Image_data/normal";
int const MAX_STR_LEN = 200;

/* Show all files under dir_name , do not show directories ! */
void showAllFiles( const char * dir_name )
{
    // check the parameter !
    if( NULL == dir_name )
    {
        cout<<" dir_name is null ! "<<endl;
        return;
    }

    // check if dir_name is a valid dir
    struct stat s;
    lstat( dir_name , &s );
    if( ! S_ISDIR( s.st_mode ) )
    {
        cout<<"dir_name is not a valid directory !"<<endl;
        return;
    }

    struct dirent * filename;    // return value for readdir()
    DIR * dir;                   // return value for opendir()
    dir = opendir( dir_name );
    if( NULL == dir )
    {
        cout<<"Can not open dir "<<dir_name<<endl;
        return;
    }
    cout<<"Successfully opened the dir !"<<endl;


    string data_8bit= "../rgb/";
    string radiance_R_CHN= "../Radiance_R_CHN_8UC3/";
    string radiance_G_CHN= "../Radiance_G_CHN_8UC3/";
    string radiance_B_CHN= "../Radiance_B_CHN_8UC3/";


    /* read all the files in the dir ~ */
    while( ( filename = readdir(dir) ) != NULL )
    {
        // get rid of "." and ".."
        if( strcmp( filename->d_name , "." ) == 0 ||
            strcmp( filename->d_name , "..") == 0    )
            continue;



        //TODO: apply your function here

        string  data_path= data_8bit+ filename->d_name;

        cout<<"show file names:"<<data_path<<endl;
//        string data_radiance_r_chn_path= radiance_R_CHN+ filename->d_name;
//        string data_radiance_g_chn_path= radiance_G_CHN+ filename->d_name;
//        string data_radiance_b_chn_path= radiance_B_CHN+ filename->d_name;


//        Mat Image_8u3= imread(data_path, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
//        Mat Image_8u3_spilt[3]; // b g r
//        cv::split(Image_8u3, Image_8u3_spilt);
//
//        Mat image_Radiace_R(Image_8u3.rows, Image_8u3.cols, CV_8UC3);
//        Mat image_Radiace_G(Image_8u3.rows, Image_8u3.cols, CV_8UC3);
//        Mat image_Radiace_B(Image_8u3.rows, Image_8u3.cols, CV_8UC3);


//        imshow("Image_8u3_spilt[2]", Image_8u3_spilt[2]);



////        type_info()
//        for (int j = 0; j < Image_8u3.rows; ++j) {
//            for (int i = 0; i < Image_8u3.cols; ++i) {
//
//
////                cout << "\n 1 show  Image_8u3_spilt[2]:" << (int) Image_8u3_spilt[2].at<uchar>(j,i) << ",at :"<< j<< ","<<i<<endl;
////                cout << "\n 1 show  Image_8u3:" << Image_8u3.at<Vec3b>(j,i) << ",at :"<< j<< ","<<i<<endl;
////
////
//
//                int radiance_R= (int) Image_8u3_spilt[2].at<uchar>(j,i) * 256;
//                int radiance_G= (int) Image_8u3_spilt[1].at<uchar>(j,i) * 256;
//                int radiance_B= (int) Image_8u3_spilt[0].at<uchar>(j,i) * 256;
//
//
////                cout<<"\n radiance_R:"<<radiance_R<<endl;
//                int radiance_R_Store_in_CR=  (radiance_R - radiance_R% 255)/ 255;
//                int radiance_G_Store_in_CR=  (radiance_G - radiance_G% 255)/ 255;
//                int radiance_B_Store_in_CR=  (radiance_B - radiance_B% 255)/ 255;
//
////                cout<<"\n radiance_R_Store_in_CR:"<<radiance_R_Store_in_CR<<endl;
//                int radiance_R_Store_in_CG= radiance_R% 255;
//                int radiance_G_Store_in_CG= radiance_G% 255;
//                int radiance_B_Store_in_CG= radiance_B% 255;
//
//
////                cout<<"\n radiance_R_Store_in_CG:"<<radiance_R_Store_in_CG<<endl;
//                image_Radiace_R.at<Vec3b>(j,i).val[2]= radiance_R_Store_in_CR;
//                image_Radiace_R.at<Vec3b>(j,i).val[1]= radiance_R_Store_in_CG;
//
//
//                image_Radiace_G.at<Vec3b>(j,i).val[2]= radiance_G_Store_in_CR;
//                image_Radiace_G.at<Vec3b>(j,i).val[1]= radiance_G_Store_in_CG;
//
//                image_Radiace_B.at<Vec3b>(j,i).val[2]= radiance_B_Store_in_CR;
//                image_Radiace_B.at<Vec3b>(j,i).val[1]= radiance_B_Store_in_CG;
//
//
//
////            cout<<"\n show r  image_Radiace_R.at<Vec3b>(j,i).val[2]:"<< (int) image_Radiace_R.at<Vec3b>(j,i).val[2]<<endl;
////            cout<<"\n show g image_Radiace_R.at<Vec3b>(j,i).val[1]:"<< (int) image_Radiace_R.at<Vec3b>(j,i).val[1]<<endl;
////            cout<<"\n show b image_Radiace_R.at<Vec3b>(j,i).val[1]:"<< (int) image_Radiace_R.at<Vec3b>(j,i).val[0]<<endl;
////
//
//
//
//
//
//
//            }
//        }
//
//        imwrite(data_radiance_r_chn_path, image_Radiace_R);
//        imwrite(data_radiance_g_chn_path, image_Radiace_G);
//        imwrite(data_radiance_b_chn_path, image_Radiace_B);

//        imshow("image_Radiace_R",image_Radiace_R);


//        string ty =  type2str(Image_8u3_spilt[2].type());
//        printf("pic1: %s %dx%d \n", ty.c_str(), Image_8u3_spilt[2].cols, Image_8u3_spilt[2].rows );
//        waitKey(0);

//
//
//        Mat targetImage;
//
//        Mat singleChannel(testImage.rows, testImage.cols, CV_16S, Scalar(0));
//
//        singleChannel.at<uchar>(10,10)=655;
//
//////        imshow("pic1",testImage);
////        string ty =  type2str(testImage.type());
////        printf("pic1: %s %dx%d \n", ty.c_str(), testImage.cols, testImage.rows );
////
////
////        for (int j = 0; j < testImage.rows; ++j) {
////            for (int i = 0; i < testImage.cols; ++i) {
////
////                cout << "\n 1 show  testImage" << testImage.at<Vec3b>(j,i);
////                targetImage.at<Vec3w >(j,i) = Vec3w (100*testImage.at<Vec3b>(j,i));
////                cout << "\n 2 show  targetImage" << targetImage.at<Vec3w>(j,i);
////
////            }
////        }
////////
//
//
//        cout << "\n  0 show  singleChannel :" <<  (singleChannel.at<uchar>(10,10))<<endl;
//        cout << "\n  1 show  pic1 val change" << testImage.at<Vec3b>(10,10) <<endl;
//////
////        testImage.convertTo(targetImage, CV_16UC3, 1);
////
//////        normalize(targetImage,targetImage, 0, 256*256, NORM_MINMAX);
//////
////        cout << "\n  2 show  pic1 val change" << targetImage.at<Vec3w>(10,10) <<endl;
////        cout << "\n  2-1 show  pic1 val change" << targetImage.at<Vec3b>(10,10) <<endl;
//////
//        waitKey(0);
        cout<<filename ->d_name <<endl;
    }
}



int main(){


    showAllFiles(dir);




//
//      uchar ace= 23;
//
//      cout<<"ace:"<<ace*10<<endl;

//      uchar ace_uchar= static_cast<uchar>(ace);
//    cout<<"ace_uchar:"<<to_string(ace_uchar)<<endl;



//    waitKey(0);
    string data_8bit= "../data/11219.019818.png";
    string data_16bit= "../rgb_16bit/11197.086112.png"; //testInput
//    string data_16bit= "../data/test16bitImage/testInput.png"; //testInput
//    string data_16bit="/home/lei/Documents/Research/dataset/mannequin_1/rgb/11197.344156.png";
//    string data_16bit="/home/lei/Documents/Research/dataset/mannequin_1/depth/11197.344156.png";



    Mat data_8bit_Image= imread(data_8bit, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);

    Mat data_16bit_Image= imread(data_16bit, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
    string ty =  type2str(data_16bit_Image.type());
    imshow("data_16bit_Image",data_16bit_Image);
    printf("\n data_16bit_Image: %s %dx%d \n", ty.c_str(), data_16bit_Image.cols, data_16bit_Image.rows );
    cout << " data_16bit_Image.channels() = " << data_16bit_Image.channels() << endl;
    cout<<" \n show 8 bit image:"<< data_8bit_Image.at<Vec3b>(50,70)<<endl;
    double min_depth, max_depth;
    cv::minMaxLoc(data_16bit_Image, &min_depth, &max_depth);
    cout << "\n show  data_16bit_Image  map min, max:\n" << (double) 1/256.0*min_depth << "," << (double) 1/256.0*max_depth << endl;
    cout << "\n show  data_16bit_Image  map min, max:\n" << (double ) min_depth << "," << (double ) max_depth << endl;


    double min_depth8, max_depth8;
    cv::minMaxLoc(data_8bit_Image, &min_depth8, &max_depth8);
    cout << "\n show  data_8bit_Image  map min, max:\n" << (double ) min_depth8 << "," << (double )max_depth8 << endl;



    cout<<" \n show 16 bit image:"<< (double) (1/3.0)*(1/256.0)*data_16bit_Image.at<Vec3w>(50,70) <<endl;
    waitKey(0);



    return 0;
}

////    void* addr1 = (void*)0x280054005a002b00;
////    void* addr2 = (void*)0x7fffd000f0b0;
////    //0x7fffc800c170
////
////    if (((uintptr_t)addr1 & 7) == 0 && ((uintptr_t)addr2 & 7) == 0) {
////        // addr1 and addr2 are aligned to an 8-byte boundary
////        cout<< "aligned" << endl;
////    } else {
////        // addr1 and addr2 are not aligned to an 8-byte boundary
////        cout<< "not aligned" << endl;
////    }