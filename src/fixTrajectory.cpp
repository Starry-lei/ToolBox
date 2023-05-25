

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


void solveForRelativePose(Sophus::SE3f& pose1, Sophus::SE3f& pose2, Sophus::SE3f& relativePose){
    relativePose = pose1.inverse() * pose2;
}

int main() {

    bool userelativePose= false;

    std::vector<Sophus::SE3f, Eigen::aligned_allocator<Sophus::SE3f>> trajectoryPoses;
//    string fileName = "../data/poseData/poses.txt";
    string fileName = "../data/poseData/longerPose.txt";
    readCtrlPointPoseData(fileName, trajectoryPoses);


    std::string  strAssociationFilename = "../data/poseData/associated.txt";
    std::ifstream fAssociation;
    fAssociation.open(strAssociationFilename.c_str());

    std::vector<std::string> timestamps;
    if (!fAssociation)
    {printf("please ensure that you have the associate file\n");
        return -1;}
    while (!fAssociation.eof())
    {
        std::string s;
        std::getline(fAssociation, s);
        if (!s.empty())
        {
            std::stringstream ss;
            ss << s;
            std::string t;
            std::string sRGB, sDepth;
            //std::string sRGB, sDepth, sMetallic, sBasecolor, sNormal, sRoughness;
            // readin rgb file

            ss >> t;
            timestamps.push_back(t);
//            ss >> sRGB;
//            sRGB = sequenceFolder + "/" + sRGB;
//            _rgb.push_back(sRGB);
//            // readin depth file
//            ss >> t;
//            ss >> sDepth;
//            sDepth = sequenceFolder + "/" + sDepth;
//            _depth.push_back(sDepth);
//
        }
    }

    ofstream relativePoseFile;
    relativePoseFile.open("../data/poseData/relativePoses_gt.txt");

    ofstream translationPart_rel;
    ofstream translationPart_abs;
    if (userelativePose){

        translationPart_rel.open("../data/poseData/translationPart_rel.txt");
    }else{

        translationPart_abs.open("../data/poseData/translationPart_abs.txt");
    }

    for (int i = 0; i < trajectoryPoses.size(); ++i) {
        Sophus::SE3f relativePose;

        solveForRelativePose(trajectoryPoses[0], trajectoryPoses[i], relativePose);
//        relativePose = trajectoryPoses[i];

        Eigen::Quaternionf q(relativePose.rotationMatrix());
        Eigen::Vector3f t(relativePose.translation());

        relativePoseFile<<std::fixed << std::setprecision(6)<<timestamps[i]<<" "<<t.x()<<" " << t.y()<<" "<<t.z()<<" "<<q.w()<<" "<< q.x()<<" " << q.y()<<" " << q.z()<<"\n";

        if (userelativePose){
            translationPart_rel<<std::fixed << std::setprecision(6)<<t.x()<<" " << t.y()<<" "<<t.z()<<"\n";
        }else{
            translationPart_abs<<std::fixed << std::setprecision(6)<<t.x()<<" " << t.y()<<" "<<t.z()<<"\n";
        }
    }
    relativePoseFile.close();

    if (userelativePose){
        translationPart_rel.close();
    }else{
        translationPart_abs.close();
    }


    cout<<"fix trajectory done!"<<endl;




    return 0;
}

// note:

//    cout<<"relativePose: \n"<<relativePose.matrix()<<endl;
//
//    Eigen::Matrix3f R12;
//    Eigen::Vector3f t12;
//    R12 = pose2.rotationMatrix().transpose() * pose1.rotationMatrix();
//    t12 = pose2.rotationMatrix().transpose() * (pose1.translation() - pose2.translation());
//    Sophus::SE3f relativePose2(R12, t12);
//
//    cout<<"relativePose2: \n"<<relativePose2.matrix()<<endl;


// solve for relative poses
//    Sophus::SE3f relativePose;
//    solveForRelativePose(trajectoryPoses[0], trajectoryPoses[1], relativePose);
//        cout<<"i: "<<i<<","<<trajectoryPoses[i].matrix()<<endl;
