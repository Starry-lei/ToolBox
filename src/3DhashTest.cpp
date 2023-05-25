//
// Created by lei on 08.01.23.
//

#include <fstream>
#include <unordered_map>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "../include/toolBox.h"
template <class T>
struct hashh
{
    size_t operator()(const T &key) const
    {
        float mult = 10000; // 保留6位
        size_t hash = 137 * std::round(mult * (key.x+10)) + 149 * std::round(mult * (key.y+10)) + 163 * std::round(mult * (key.z+10));
        return hash;
    }
};

template <class T>
struct myEqual
{
    bool operator()(const T &key1, const T &key2) const
    {
        return key1.x == key2.x && key1.y == key2.y && key1.z == key2.z;
    }
};

void ReadData(string fileName, vector<Sophus::SE3f, Eigen::aligned_allocator<Sophus::SE3f>>& pose) {

    ifstream trajectory(fileName);
    if (!trajectory.is_open()) {
        cout << "No " << fileName << endl;
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


struct StructTest {
    int a;
};
int main()
{

    cv::Point3f a(50000.00000, 3, 3);
    cv::Point3f b(50000.000001, 3, 3);
    cv::Point3f c(2.111011, 3, 3);

    cv::Point3f d(-2.111012, 3, 3);


    std::unordered_map<cv::Point3f, StructTest, hashh<cv::Point3f>, myEqual<cv::Point3f>> umap_struct;


    StructTest structTest01;

    umap_struct.emplace(c, structTest01);






//    vector<int> testVec;
//
//    testVec.reserve(2);
//
//    testVec.push_back(3);
//    testVec.push_back(4);
//
//    cout<<"show ele:"<< testVec[1]<< endl;
//    testVec.push_back(4);


//    string controlPointPose_path= "../data/kitchen_control_cam_pose.txt";
//
//    vector<Sophus::SE3f, Eigen::aligned_allocator<Sophus::SE3f>> controlPoints;
//    ReadData(controlPointPose_path,controlPoints);
//
//    cout<<"Number of controlPoints.size:"<<controlPoints.size()<<endl;
//    for (int i = 0; i < controlPoints.size(); ++i) {
//        cout<<"show pose:\n"<< controlPoints[i].matrix()<<endl;
//
//    }


//


    cv::Point3f e(1.608823427727570365, -3.349066557048461235e-01, 7.991267625627391791e-01);

    std::unordered_map<cv::Point3f, int, hashh<cv::Point3f>, myEqual<cv::Point3f>> umap;
    umap.emplace(a, 100100101);
    umap.emplace(b, 1);
    umap.emplace(c, 1);

    umap.emplace(d, 1);
    std::cout << std::round(10000 * c.x) << std::endl;
    std::cout << umap.size() << std::endl;
    std::cout << umap.count(c) << std::endl;

    std::cout <<"show number of a:"<< umap.count(a) << std::endl;

    std::cout<<"show e:"<< umap[a]<<std::endl;


    return 0;
}