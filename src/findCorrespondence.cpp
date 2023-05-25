
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include <pcl/point_cloud.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <unordered_map>


#include "../include/PFMReadWrite.h"

//#include "PFMReadWrite.cpp"

#include <string>
#include <iostream>
#include <fstream>

#include "opencv2/photo.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


#include <cmath>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/StdVector>
#include <sstream>
using namespace cv;
using namespace std;


void onMouse_intType(int event,int x,int y,int flags,void* param)
{
	Mat* im = reinterpret_cast<Mat*>(param);
	switch(event)
	{
	case EVENT_LBUTTONDOWN:
		//左键按下显示像素值
		if (static_cast<int>(im->channels())==1)
		{
			//若为灰度图，显示鼠标点击的坐标以及灰度值
			std::cout<<"at("<<y<<","<<x<<")value is:"<<static_cast<int>(im->at<int>(y,x))<<endl;
		}
		else if (static_cast<int>(im->channels() == 3))
		{
			//若图像为彩色图像，则显示鼠标点击坐标以及对应的B, G, R值
			std::cout << "at (" << y << ", " << x << ")"
				<< "  B value is: " << static_cast<int>(im->at<Vec3b>(y, x)[0]) 
				<< "  G value is: " << static_cast<int>(im->at<Vec3b>(y, x)[1])
				<< "  R value is: " << static_cast<int>(im->at<Vec3b>(y, x)[2])
				<< endl;
		}
	}
}
void onMouse_floatType(int event,int x,int y,int flags,void* param)
{
	Mat* im = reinterpret_cast<Mat*>(param);
	switch(event)
	{
	case EVENT_LBUTTONDOWN:
		//左键按下显示像素值
		if (static_cast<int>(im->channels())==1)
		{
			//若为灰度图，显示鼠标点击的坐标以及灰度值
			std::cout<<"at("<<y<<","<<x<<")value is:"<<static_cast<float>(im->at<float>(y,x))<<endl;
		}
		else if (static_cast<int>(im->channels() == 3))
		{
			//若图像为彩色图像，则显示鼠标点击坐标以及对应的B, G, R值
			std::cout << "at (" << y << ", " << x << ")"
				<< "  B value is: " << static_cast<float>(im->at<Vec3f>(y, x)[0]) 
				<< "  G value is: " << static_cast<float>(im->at<Vec3f>(y, x)[1])
				<< "  R value is: " << static_cast<float>(im->at<Vec3f>(y, x)[2])
				<< endl;
		}
	}
}


template<typename T>
bool operatorDepth ( T* sd ) {

	//  T d= sd[0];

	// Eigen::Map<Eigen::Matrix<T,1,1> const> const d_new(sd);
	// cout<< "show d_new value:"<< d_new<<endl;


	// cout<< "show d value:"<< d<<endl;
	// cout<< "show d adress value:"<< &d<<endl;
	
	// cout<< "show sd value:"<< sd<<endl;
	cout<< "show sd[0] value:"<< sd[0]<<endl;


	sd[0]+=100.0;

return true;

}

// 方法二(bug 较多,不推荐)
// 不创建新文件,直接在源文件上修改指定字符串(覆盖方法,新字符串比原字符串长的时候才能使用)。指针位置对应函数(tellg seekg <-> tellp seekp)
bool FixNewFile(fstream &fixstream)
{
	string str;
	size_t cur; // 记录读指针位置
	size_t pos = 0;
	while (getline(fixstream, str))
	{
		// pos = str.find("0.2");
		pos=85;

		if (pos != string::npos)
		{
			// cur = fixstream.tellg();
			fixstream.seekg(227L, ios::beg);


			size_t len = strlen(str.c_str()) + 2;
			fixstream.seekp(-1 * len, fstream::cur); // (读写指针本来在相同位置),此时写指针回退到上一行

			
			str.replace(pos, 3, "0.6");
			//fixstream.clear();
			fixstream << str;
			fixstream.seekp(cur); // 写指针位置还原
			continue;
		}
	}
	return true;
}


#define BUFFER_SIZE 1000


Scalar RadianceErr(const Mat &depth_gt, const Mat &depth_es) {

		if (depth_es.depth() != depth_gt.depth()) { std::cerr << "the depth image type are different!" << endl; }
		return cv::sum(cv::abs(depth_gt - depth_es)) / cv::sum(depth_gt);

	}



 
int main(){




// string image_ref_path_exr =      "../data/image_leftRGB08.png";
// string image_right_path_exr = "../data/image_rightRGB08.png";

//string image_ref_path_exr =      "../data/000_mask.png";
string image_right_path_exr = "../data/origfovbaseColor_1.png";

// data/bgrnormal_2.png
string image_ref_path_exr = "../data/normal1/bgrnormal_17.png";

// data/imnormal_17.png
//string image_ref_path_exr = "../data/imnormal_17.png";



//Mat image_left_PNG = imread(image_ref_path_exr, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);
//Mat image_right_PNG = imread(image_right_path_exr, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);

    string newNormal= "../data/newNormal.pfm";
    Mat image_left_PNG = loadPFM(newNormal);
    Mat image_right_PNG = imread(image_right_path_exr, IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);




cout<<"left image depth():"<< image_left_PNG.depth()<<endl;
cout<<"right image depth():"<< image_right_PNG.depth()<<endl;
cout<<"left image channel():"<< image_left_PNG.channels()<<endl;


imshow("image_left_PNG",image_left_PNG);
imshow("image_right_PNG", image_right_PNG);


setMouseCallback("image_left_PNG",onMouse_intType,reinterpret_cast<void*>(&image_left_PNG));//鼠标响应函数

setMouseCallback("image_right_PNG",onMouse_intType,reinterpret_cast<void*>(&image_right_PNG));//鼠标响应函数



//Vec3f pointOnWall(image_left_PNG.at<Vec3b>(339, 120).val[2], image_left_PNG.at<Vec3b>(339, 120).val[1], image_left_PNG.at<Vec3b>(339, 120).val[0]);
//pointOnWall= normalize(pointOnWall);
//
//Vec3f pointOnGround(image_left_PNG.at<Vec3b>(337, 101).val[2], image_left_PNG.at<Vec3b>(337, 101).val[1], image_left_PNG.at<Vec3b>(337, 101).val[0]);
//pointOnGround=normalize(pointOnGround);
//
//Vec3f pointOnCabinet(image_left_PNG.at<Vec3b>(313, 144).val[2], image_left_PNG.at<Vec3b>(313, 144).val[1], image_left_PNG.at<Vec3b>(313, 144).val[0]);
//pointOnCabinet=normalize(pointOnCabinet);

// 378, 94
// 151, 50
// 33, 600

    Vec3f pointOnWall(image_left_PNG.at<Vec3f>(33, 600).val[2], image_left_PNG.at<Vec3f>(33, 600).val[1], image_left_PNG.at<Vec3f>(33, 600).val[0]);
    pointOnWall= normalize(pointOnWall);

    Vec3f pointOnGround(image_left_PNG.at<Vec3f>(378, 94).val[2], image_left_PNG.at<Vec3f>(378, 94).val[1], image_left_PNG.at<Vec3f>(378, 94).val[0]);
    pointOnGround=normalize(pointOnGround);

    Vec3f pointOnCabinet(image_left_PNG.at<Vec3f>( 151, 50).val[2], image_left_PNG.at<Vec3f>( 151, 50).val[1], image_left_PNG.at<Vec3f>( 151, 50).val[0]);
    pointOnCabinet=normalize(pointOnCabinet);

    cout<<"\n show pointOnWall"<< pointOnWall<<endl;
    cout<<"\n show pointOnGround"<< pointOnGround<<endl;
    cout<<"\n show pointOnCabinet"<< pointOnCabinet<<endl;
    cout<<"\n show cross product: pointOnWall and pointOnGround:"<<pointOnWall.dot(pointOnGround)<<endl;
    cout<<"\n show cross product: pointOnWall and pointOnCabinet:"<<pointOnWall.dot(pointOnCabinet)<<endl;
    cout<<"\n show cross product: pointOnGround and pointOnCabinet:"<<pointOnGround.dot(pointOnCabinet)<<endl;


// orange: 235, 69
// blue:   208, 561

//Vec3f orangeWall(image_left_PNG.at<Vec3b>(235, 69).val[2], image_left_PNG.at<Vec3b>(235, 69).val[1], image_left_PNG.at<Vec3b>(235, 69).val[0]);
//orangeWall=normalize(orangeWall);
//
//Vec3f blueWall(image_left_PNG.at<Vec3b>(208, 561).val[2], image_left_PNG.at<Vec3b>(208, 561).val[1], image_left_PNG.at<Vec3b>(208, 561).val[0]);
//blueWall=normalize(blueWall);
// 75, 272
//Vec3f ceiling(image_left_PNG.at<Vec3b>( 75, 272).val[2], image_left_PNG.at<Vec3b>( 75, 272).val[1], image_left_PNG.at<Vec3b>( 75, 272).val[0]);
//ceiling=normalize(ceiling);

//25, 469
    Vec3f ceiling(image_left_PNG.at<Vec3b>( 25, 469).val[2], image_left_PNG.at<Vec3b>( 25, 469).val[1], image_left_PNG.at<Vec3b>( 25, 469).val[0]);
    ceiling=normalize(ceiling);


//cout<<"\n show blueWall:"<<blueWall<<endl;

//cout<<"\n show orangeWall:"<<orangeWall<<endl;

cout<<"\n show purple ceiling:"<<ceiling<<endl;

//cout<<"\n show cross product: pointOnGround and blueWall:"<<blueWall.dot(pointOnGround)<<endl;
//
//cout<<"\n show cross product: pointOnGround and orangeWall:"<<orangeWall.dot(pointOnGround)<<endl;

cout<<"\n show cross product: purple ceiling and orangeWall:"<<ceiling.dot(pointOnGround)<<endl;








waitKey(0);






return 0;

   
    
}


// correspondences:
// at (240, 189)  B value is: 36  G value is: 25  R value is: 22
// at (233, 146)  B value is: 35  G value is: 27  R value is: 23