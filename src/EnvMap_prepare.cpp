//
// Created by lei on 08.01.23.
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



int main() {

//    std::string envMap_Folder="/media/lei/Data/Kitchen_scene/Image_data/envmap_panorama";
//    std::string new_envMap_Folder="../data/formattedEnvMap";

//    std::string envMap_Folder="/media/lei/Data/Kitchen_scene/Frame10To16/2framepanoworld";
//    std::string new_envMap_Folder="/media/lei/Data/Kitchen_scene/Frame10To16/formattedF10To16";

//    std::string envMap_Folder="/media/lei/Data/Kitchen_scene/Frame10to16_denser/2framepano3k";
//    std::string new_envMap_Folder="/media/lei/Data/datasetProcessing/ToolBox/data/formattedEnvMap_denser";

//    std::string envMap_Folder="/media/lei/Data/Kitchen_scene/MaskedPoint_EnvMap/panomasknolift";
//    std::string new_envMap_Folder="/media/lei/Data/Kitchen_scene/MaskedPoint_EnvMap/formattedEnvMap";

//    std::string envMap_Folder="/media/lei/Data/LivingRoom_scene/envmap";
//    std::string new_envMap_Folder="/media/lei/Data/LivingRoom_scene/formattedEnvmap";


//    std::string envMap_Folder="/media/lei/Data/LivingRoom_scene/17PointsEnvMap";
//    std::string new_envMap_Folder="/media/lei/Data/LivingRoom_scene/formatted17EnvMap";

//    std::string envMap_Folder="/media/lei/Data/LivingRoom_scene/leitest3/envmapwhole/envmap";
//    std::string new_envMap_Folder="/media/lei/Data/LivingRoom_scene/leitest3/formattedEnvMap";

//    std::string envMap_Folder="/media/lei/Data/LivingRoom_scene/EnvMapSparse/envmap";
//    std::string new_envMap_Folder="/media/lei/Data/LivingRoom_scene/EnvMapSparse/formattedEnvMap";

//    std::string envMap_Folder="/media/lei/Data/LivingRoom_scene/EnvMapSparse/envmap91";
//    std::string new_envMap_Folder="/media/lei/Data/LivingRoom_scene/EnvMapSparse/formattedEnvMap91";

//    std::string envMap_Folder="/media/lei/Data/LivingRoom_scene/EnvMapSparse/envmap200";
//    std::string new_envMap_Folder="/media/lei/Data/LivingRoom_scene/EnvMapSparse/formattedEnvMap200";

//    std::string envMap_Folder="/media/lei/Data/LivingRoom_scene/EnvMapSparse_150EnvMaps/another6EnvMaps/envmap";
//    std::string new_envMap_Folder="/media/lei/Data/LivingRoom_scene/EnvMapSparse_150EnvMaps/formattedEnvMap6";
    // start from 150+1

//    std::string envMap_Folder="/media/lei/Data/LivingRoom_scene/envmap156_PlusLift2mm/envmap";
//    std::string new_envMap_Folder="/media/lei/Data/LivingRoom_scene/envmap156_PlusLift2mm/formattedEnvMap";


//    std::string envMap_Folder="/media/lei/Data/toiletScene/envmap";
//    std::string new_envMap_Folder="/media/lei/Data/toiletScene/envmap_formatted";

//    std::string envMap_Folder="/media/lei/Data/LivingRoom_scene/leitest4/test2_300/2frame0370_02/envmap";
//    std::string new_envMap_Folder="/media/lei/Data/LivingRoom_scene/leitest4/test2_300/2frame0370_02/envMapformatted";
//

    std::string envMap_Folder="/media/lei/Data/LivingRoom_scene/morelight/envmap";
    std::string new_envMap_Folder="/media/lei/Data/LivingRoom_scene/morelight/formattedEnvmap";







    std::vector<string> fileNames;
    GetFileNames(envMap_Folder,fileNames);
    cout<<" \n Show fileNames.size():"<<fileNames.size()<< endl;
    cout<<" \n Show fileNames(1):"<<fileNames[0]<< endl;

    Mat widthHeight= loadPFM(fileNames[0]);

    //32FC1 1024x512
    Mat envMap_alpha(widthHeight.rows, widthHeight.cols, CV_32FC1, Scalar(1) );


    for (int i = 1; i <= fileNames.size(); ++i) {

        stringstream ss;
        ss << i;
        string img_idx_str;
        ss >> img_idx_str;
        string name_prefix = "/rgbp_";
        string img_path = envMap_Folder + name_prefix + img_idx_str + ".pfm";
        cout<<" \n Show img_path :"<<img_path<< endl;
        Mat radiance_img= loadPFM(img_path);
        string ty1 =  type2str(radiance_img.type());

        printf("radiance_img: %s %dx%d \n", ty1.c_str(), radiance_img.cols, radiance_img.rows );
        //        imshow("radiance_img",radiance_img);
        // Creating a directory
        //        sleep(1);

        string envMapfolder= new_envMap_Folder +"/"+"envMap"+to_string(i);

//        int iLength = envMapfolder.length();
//        char *s3 = (char*)malloc((iLength+1)*sizeof(char));
//        envMapfolder.copy(s3,iLength,0);
//        if (mkdir(s3, 0777) == -1)
//            cerr << "Error :  " << strerror(errno) << endl;
//        else
//            cout << "Directory:"+ envMapfolder +" created"<<endl;
//        free(s3);

        if (boost::filesystem::create_directories(envMapfolder)){
            cout << "Directory:"+ envMapfolder +" created"<<endl;
        }

//        boost::filesystem::create_directories(envMapfolder);




        string envMap_folder_path= envMapfolder+"/envMapImage.pfm";
        string envMap_alpha_folder_path= envMapfolder+"/envMapImage_alpha.pfm";

        savePFM(radiance_img, envMap_folder_path);
        savePFM(envMap_alpha,envMap_alpha_folder_path );

      string parameters_csv = "../data/parameters.csv";
      string parameters_csv_out =envMapfolder+"/parameters.csv";
      char buff[256];
//      std::cmatch m;
      fstream parameters_file(parameters_csv);
      ofstream parameters_file_out(parameters_csv_out, ios::out);

      if (!parameters_file.is_open())
        cout << "Error open shader_txt" << endl;
      if (!parameters_file_out.is_open())
        cout << "Error open shader_txt_out" << endl;

      while (!parameters_file.eof()) {
          parameters_file.getline(buff, 100);
          string new_string =buff;
          parameters_file_out << new_string << endl;
      }

        parameters_file.close();
        parameters_file_out.close();


        string parameters_env_diffuse_csv = "../data/parameters_env_diffuse.csv";
        string parameters_env_diffuse_csv_out =envMapfolder+"/parameters_env_diffuse.csv";
        char buff2[256];
        fstream parameters_file2(parameters_env_diffuse_csv);
        ofstream parameters_file_out2(parameters_env_diffuse_csv_out, ios::out);

        if (!parameters_file2.is_open())
            cout << "Error open shader_txt" << endl;
        if (!parameters_file_out2.is_open())
            cout << "Error open shader_txt_out" << endl;

        while (!parameters_file2.eof()) {
            parameters_file2.getline(buff2, 100);
            string new_string =buff2;
            parameters_file_out2 << new_string << endl;
        }

        parameters_file2.close();
        parameters_file_out2.close();

//        sleep(3);







//        waitKey(0);

    }





    return 0;
}