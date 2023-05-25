//
// Created by lei on 23.12.22.
//

#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include "sophus/se3.hpp"
#include <pcl/kdtree/kdtree_flann.h>
#include "sophus/types.hpp"
#include <Eigen/Core>

#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <iomanip>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;


float clamp(const float x, const float min_v, const float max_v) {
    return std::min(std::max(x, min_v), max_v);
}

Vec3f clamp_vec3f(Vec3f x) {

    Vec3f res;
    res.val[0] = clamp(x.val[0], 0.0f, 1.0f);
    res.val[1] = clamp(x.val[1], 0.0f, 1.0f);
    res.val[2] = clamp(x.val[2], 0.0f, 1.0f);

    return res;
}


Vec3f RRTAndODTFit(Vec3f v) {
    Vec3f One = Vec3f(1.0f, 1.0f, 1.0f);

    Vec3f a = v.mul(v + 0.0245786f * One) - 0.000090537f * One;
    Vec3f b = v.mul(0.983729f * v + 0.4329510f * One) + 0.238081f * One;

    Vec3f inv_v = Vec3f(1.0f / b.val[0], 1.0f / b.val[1], 1.0f / b.val[2]);

    return a.mul(inv_v);

}

Vec3f ACESFilm(Vec3f radiance) {

    // https://computergraphics.stackexchange.com/questions/11018/how-to-change-a-rgb-value-using-a-radiance-value
    // https://github.com/TheRealMJP/BakingLab/blob/master/BakingLab/ACES.hlsl
    // method 1

    float adapted_lum = 1.0;
    radiance *= adapted_lum;
    Eigen::Matrix3f ACESInputMat, ACESOutputMat;
    Eigen::Vector3f r1, r2;
    ACESInputMat << 0.59719, 0.35458, 0.04823, 0.07600, 0.90834, 0.01566, 0.02840, 0.13383, 0.83777;
    ACESOutputMat << 1.60475, -0.53108, -0.07367, -0.10208, 1.10813, -0.00605, -0.00327, -0.07276, 1.07602;

    r1 = ACESInputMat * Eigen::Vector3f(radiance.val[0], radiance.val[1], radiance.val[2]);
    radiance = RRTAndODTFit(Vec3f(r1.x(), r1.y(), r1.z()));
    r2 = ACESOutputMat * Eigen::Vector3f(radiance.val[0], radiance.val[1], radiance.val[2]);

    radiance = Vec3f(r2.x(), r2.y(), r2.z());
    // method 2
//    			float a = 2.51f;
//    			float b = 0.03f;
//    			float c = 2.43f;
//    			float d = 0.59f;
//    			float e = 0.14f;
//    		    Vec3f One = Vec3f(1.0f, 1.0f, 1.0f);
//    		    Vec3f sndVecor= Vec3f(1.0/(radiance.mul(c*radiance+d*One)+e*One).val[0],
//    		                           1.0/(radiance.mul(c*radiance+d*One)+e*One).val[1],
//    		                           1.0/(radiance.mul(c*radiance+d*One)+e*One).val[2]);
//    		return  clamp_vec3f((radiance.mul(a*radiance+b*One)) .mul(sndVecor));

    // method 1 output
    return clamp_vec3f(radiance);

}

float linear2sRGB(float x)
{
    return x <= 0.0031308 ?
           12.92 * x :
           1.055 * pow(x, 0.41666) - 0.055;
}

Vec3f linear2sRGB(Vec3f rgb)
{
    return Vec3f(
            linear2sRGB(rgb.val[2]),
            linear2sRGB(rgb.val[1]),
            linear2sRGB(rgb.val[0]));
}
// https://substance3d.adobe.com/documentation/spdoc/lib-utils-shader-api-188976084.html

Vec3f linear2sRGBOpt(Vec3f rgb, bool convert_to_srgb_opt= true)
{
    return convert_to_srgb_opt ? linear2sRGB(rgb) : rgb;
}

Vec3f HDRToOutput(Vec3f hdr, float exposure)
{
    // Exposure (tune the value to set the overall brightness;
    // positive makes it brighter, while negative makes it darker)


//    hdr *= exp2(exposure);
//    // Limit saturation to 99% - maps pure colors like (1, 0, 0) to (1, 0.01, 0.01)
//    float maxComp = max(max(hdr.val[2], hdr.val[1]), hdr.val[0]);
//
//    hdr.val[2] = max (hdr.val[2], (float )0.01 * maxComp);
//    hdr.val[1] = max (hdr.val[1], (float )0.01 * maxComp);
//    hdr.val[0] = max (hdr.val[0], (float )0.01 * maxComp);

    // Apply tonemapping curve
    Vec3f ldrLinear = ACESFilm(hdr);

    // Convert to sRGB
    Vec3f ldrSRGB = linear2sRGBOpt(hdr, false);
    return ldrSRGB;
}


void GetFileNames(string path,vector<string>& filenames )
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

void GetFileNames(string path,vector<string>& filenames , vector<string>& filenamesNoPath)
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
            filenamesNoPath.push_back(ptr->d_name);
        }
    }
    closedir(pDir);
}





string type2str(int type) {
    string r;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    switch ( depth ) {
        case CV_8U:  r = "8U"; break;
        case CV_8S:  r = "8S"; break;
        case CV_16U: r = "16U"; break;
        case CV_16S: r = "16S"; break;
        case CV_32S: r = "32S"; break;
        case CV_32F: r = "32F"; break;
        case CV_64F: r = "64F"; break;
        default:     r = "User"; break;
    }

    r += "C";
    r += (chans+'0');

    return r;
}

//
//show  radiance_img val: [0.0336161, 0.0429777, 0.0258381]
//
//show  radiance_png val: [45, 58, 51]
//
//
//show  radiance_img val: [0.033054, 0.0387983, 0.0267249]
//show  radiance_png val: [45, 55, 51]

//show  radiance_img val: [0.0319076, 0.0316164, 0.0258253]
//show  radiance_png val: [45, 50, 50]

//show  radiance_img val: [0.0204763, 0.019001, 0.0261167]
//show  radiance_png val: [45, 38, 39]

//show  radiance_img val: [0.0130861, 0.0189237, 0.0265926]
//show  radiance_png val: [45, 37, 30]


//show  radiance_img val: [0.0079488, 0.0171709, 0.0260889]
//show  radiance_png val: [45, 35, 22]
