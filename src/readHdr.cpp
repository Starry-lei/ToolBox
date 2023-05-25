//
// Created by lei on 03.01.23.
//
#include "../include/toolBox.h"


int main(){


    float a = 10.0;
    ushort b= 10;
    Eigen::Matrix<ushort,3,1 > a;



    cout << "\n show  a: " << a<<endl;
//    cout << "\n show  b: " << (int) b<<endl;
    cout << "\n show  a*b: " << a*b<<endl;

    string data_env_hdr= "../data/image_imageBlaubeurenNight1k.hdr";
    Mat data_env =imread(data_env_hdr, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);

    string ty1 =  type2str(data_env.type());
    printf("data_env Matrix: %s %dx%d \n", ty1.c_str(), data_env.cols, data_env.rows );

    pyrDown(data_env, data_env, Size(data_env.cols/2, data_env.rows/2));
    pyrDown(data_env, data_env, Size(data_env.cols/2, data_env.rows/2));
//    pyrDown(data_env, data_env, Size(data_env.cols/2, data_env.rows/2));

    string ty2 =  type2str(data_env.type());
    printf("new data_env Matrix: %s %dx%d \n", ty2.c_str(), data_env.cols, data_env.rows );

    imshow("data_env",data_env);
    // save the image
    imwrite("../data/newENV256128.hdr", data_env);

    waitKey(0);


    return 0;
}