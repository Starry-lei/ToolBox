//
// Created by lei on 15.01.23.
//
//
// Created by lei on 13.01.23.
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


void readCtrlPointPoseData(string fileName, vector<Sophus::SE3f, Eigen::aligned_allocator<Sophus::SE3f>>& pose) {

    ifstream trajectory(fileName);
    if (!trajectory.is_open()) {
        cout << "No controlPointPose data!" << fileName << endl;
        return;
    }

    float  qw, qx, qy, qz, tx, ty, tz;
    string line;
    while (getline(trajectory, line)) {
        stringstream lineStream(line);
        lineStream >> qw >> qx >> qy >> qz>> tx >> ty >> tz;

        Eigen::Vector3f t(tx, ty, tz);
        Eigen::Quaternionf q = Eigen::Quaternionf(qw, qx, qy, qz).normalized();
        Sophus::SE3f SE3_qt(q, t);
        pose.push_back(SE3_qt);
    }

}


template <class T>
struct hash3d
{
    size_t operator()(const T &key) const
    {
        float mult = 10000.0;
        size_t hash = 137 * std::round(mult * (key.x+10.0)) + 149 * std::round(mult * (key.y+10.0)) + 163 * std::round(mult * (key.z+10.0));
        return hash;
    }
};

template <class T>
struct equalTo
{
    bool operator()(const T &key1, const T &key2) const
    {

        bool res= key1.x == key2.x && key1.y == key2.y && key1.z == key2.z;
//        cout<<"\n Hash res:"<< res<<endl;
        return res ;
    }
};
int main() {

    string slamImg_path= "../data/A_SelectControlPoint/bgr_10.png";
    string Image_depth= "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/data/SimulationEnvData/leftImage/origfovdepth_10.png";
    Mat depth_map= imread(Image_depth);


    Vec2i boundingBoxUpperLeft(0,0);
    Vec2i boundingBoxBotRight(240,320);


    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
    Eigen::Matrix<float,3,3> K_;

    K_<<   577.8705, 0, 320,
            0, 577.8705, 240,
            0, 0, 1;

    float fx = K_(0, 0), cx = K_(0, 2), fy =  K_(1, 1), cy = K_(1, 2);


    Mat depth_reference(depth_map.rows, depth_map.cols, CV_64FC1);

    for (int j = 0; j < depth_map.rows; ++j) {
        for (int i = 0; i < depth_map.cols; ++i) {

            depth_reference.at<double>(j,i)= 1.0/5000.0 * ((double) depth_map.at<unsigned short>(j,i));
            cout << "\n show  depth_target: " << depth_reference.at<double>(j,i)<<endl;
        }
    }




    Mat img= imread(slamImg_path);
    Mat orig_img= img.clone();


//    img.convertTo(img, CV_64FC1, 1/255.0);




    pcl::PCDWriter writer;
    // read controlPoint cloud
    pcl::PointCloud<pcl::PointXYZ>::Ptr ControlpointCloud(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr nearestPointCloud(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr scenePointCloud  (new pcl::PointCloud<pcl::PointXYZ>());


    string controlPointPose_path="../data/A_SelectControlPoint/scene0704_01_control_cam_pose.txt";
    std::vector<Sophus::SE3f, Eigen::aligned_allocator<Sophus::SE3f>> controlPointPoses;
    readCtrlPointPoseData(controlPointPose_path,controlPointPoses);
    std::cout<<" \n Show controlPointPoses.size():"<<controlPointPoses.size()<< std::endl;

    std::unordered_map<cv::Point3f, int , hash3d<cv::Point3f>, equalTo<cv::Point3f>> pointCloud_UnorderedMap;


    for (size_t i=1;i<=controlPointPoses.size();i++) {

        Sophus::SE3f envMapPose_world= controlPointPoses[i-1].cast<float>();
        cv::Point3f pointBase= Vec3f (  controlPointPoses[i-1].translation().x(), controlPointPoses[i-1].translation().y(),  controlPointPoses[i-1].translation().z());
        ControlpointCloud->push_back(pcl::PointXYZ(pointBase.x, pointBase.y, pointBase.z));
        pointCloud_UnorderedMap.insert(make_pair(pointBase, (int)i));

    }

    if (ControlpointCloud->empty()){std::cerr<<"\n Wrong Control-pointCloud!"<< endl;}
    kdtree.setInputCloud(ControlpointCloud);



    imshow("slamImg", img);

    Mat checkingArea(480,640, CV_8UC3, Scalar(0));
    // K nearest neighbor search
    int num_K = 3;
    std::unordered_map<cv::Point3f, vector<int>, hash3d<cv::Point3f>, equalTo<cv::Point3f>> envLightMap;

    vector<int> AllIndex;


    for (int u = 0; u < depth_reference.rows; u++)// colId, cols: 0 to 480
    {
        for (int v = 0; v < depth_reference.cols; v++)// rowId,  rows: 0 to 640
        {


//            if (v<boundingBoxUpperLeft.val[1] || v>boundingBoxBotRight.val[1] ||
//            u< boundingBoxUpperLeft.val[0] ||  u> boundingBoxBotRight.val[0]
//            ){ continue;}



            checkingArea.at<Vec3b>(u, v)= orig_img.at<Vec3b>(u, v);

            // projection
            double iDepth = depth_reference.at<double>(u, v);

            Eigen::Vector2f pixelCoord((float) v, (float) u);//  u is the row id , v is col id
            Eigen::Vector3f p_3d_no_d((pixelCoord(0) - cx) / fx, (pixelCoord(1) - cy) / fy, (float) 1.0);
            Eigen::Vector3f p_c1;
            p_c1 = (float)iDepth* p_3d_no_d;

//            cout<<"show p_c1"<<p_c1<<endl;

            pcl::PointXYZ searchPoint(p_c1.x(), p_c1.y(), p_c1.z());

            scenePointCloud->push_back(searchPoint);


            cv::Point3f key_shaderPoint(p_c1.x(), p_c1.y(), p_c1.z());

            std::vector<int> pointIdxKNNSearch(num_K);
            std::vector<float> pointKNNSquaredDistance(num_K);

            vector<int> controlPointIndex[3];

            Vec3f key4Search;
            if ( kdtree.nearestKSearch(searchPoint, num_K, pointIdxKNNSearch, pointKNNSquaredDistance) > 0) {

//                std::cout << "\n---The Nearest point---"<<
//                          (*(ControlpointCloud))[ pointIdxKNNSearch[0] ].x
//                          << " " << (*(ControlpointCloud))[ pointIdxKNNSearch[0]].y
//                          << " " << (*(ControlpointCloud))[ pointIdxKNNSearch[0]].z
//                          << " (squared distance: " << pointKNNSquaredDistance[0] << ")" << std::endl;

                nearestPointCloud->push_back(pcl::PointXYZ((*(ControlpointCloud))[pointIdxKNNSearch[0]].x, (*(ControlpointCloud))[pointIdxKNNSearch[0]].y, (*(ControlpointCloud))[pointIdxKNNSearch[0]].z));

                for (std::size_t idx = 0; idx < pointIdxKNNSearch.size (); ++idx)
                {
                    Vec3f key4Search_;
                    key4Search_.val[0] = (*(ControlpointCloud))[pointIdxKNNSearch[idx]].x;
                    key4Search_.val[1] = (*(ControlpointCloud))[pointIdxKNNSearch[idx]].y;
                    key4Search_.val[2]=(*(ControlpointCloud))[pointIdxKNNSearch[idx]].z;
                    controlPointIndex->push_back(pointCloud_UnorderedMap[key4Search_]);

                    AllIndex.push_back(pointCloud_UnorderedMap[key4Search_]);




                }

                envLightMap.emplace(key_shaderPoint, *controlPointIndex);

//
//                key4Search.val[0] = (*(ControlpointCloud))[pointIdxKNNSearch[0]].x;
//                key4Search.val[1] = (*(ControlpointCloud))[pointIdxKNNSearch[0]].y;
//                key4Search.val[2] = (*(ControlpointCloud))[pointIdxKNNSearch[0]].z;


            }

        }
    }


    for (auto pair: envLightMap) {

        cout<<"\n show correspondence between shader point and its ctrlPointIndex:"<< endl;
        for (int i = 0; i < pair.second.size(); ++i) {
            cout<<pair.second[i]<<",";
        }
    }



    sort(AllIndex.begin(), AllIndex.end());
    AllIndex.erase(unique(AllIndex.begin(), AllIndex.end()), AllIndex.end());
    cout<<"\n show AllIndex size:"<<AllIndex.size()<< endl;

//    for (int i = 0; i < AllIndex.size(); ++i) {
//        cout<<"\n show AllIndex:"<<AllIndex[i]<< endl;
//    }


    writer.write("./ControlpointCloud.pcd",*ControlpointCloud, false);// do we need the sensor acquisition origin?
    writer.write("./nearestPointCloud.pcd",*nearestPointCloud, false);// do we need the sensor acquisition origin?
    writer.write("./scenePointCloud.pcd",*scenePointCloud, false);// do we need the sensor acquisition origin?



    imshow("checkingArea", checkingArea);

    waitKey(0);








            return 0;
}