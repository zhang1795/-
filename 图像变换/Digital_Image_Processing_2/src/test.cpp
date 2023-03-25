#include <highgui.hpp>
#include <imgproc.hpp>
#include <imgcodecs.hpp>
#include <vector>
#include<iostream>

#include "image_algorithm.h"  // 相关自定义算法

using namespace cv;

int main()
{
	std::string filepath = "c:/users/34148/pictures/lena.jpg";
	Mat img = imread(filepath);
	Mat figure1, figure2, figure3, figure4, figure5, figure6, figure7, figure8, figure9;
	imshow("lena", img);
	waitKey();

	// 测试transformation类
	transformation TF1;  // 默认情况下，无变换
	Mat M1 = TF1.getTransformMatrix();
	warpAffine(img, figure1, M1, Size(600, 600), INTER_CUBIC);
	imshow("figure1", figure1);

	transformation TF2(50.0f,50.0f);  // 水平移位
	Mat M2 = TF2.getTransformMatrix();
	warpAffine(img, figure2, M2, Size(600, 600), INTER_CUBIC);
	imshow("figure2", figure2);

	transformation TF3(1.5);  // 缩放 
	Mat M3 = TF3.getTransformMatrix();
	warpAffine(img, figure3, M3, Size(600, 600), INTER_CUBIC);
	imshow("figure3", figure3);


	transformation TF4(1.2, 45.0);  // 缩放 + 旋转
	Mat M4 = TF4.getTransformMatrix();
	warpAffine(img, figure4, M4, Size(600, 600), INTER_CUBIC);
	imshow("figure4", figure4);

	Point2f center(img.cols / 2.0f, img.rows / 2.0f);
	transformation TF5(center,1.2, 45.0);  // 指定中心 + 缩放 + 旋转 
	Mat M5 = TF5.getTransformMatrix();
	warpAffine(img, figure5, M5, Size(600, 600), INTER_CUBIC);
	imshow("figure5", figure5);
	

	transformation TF6(100.0f, 100.0f, 1.2);  // 水平移位 + 缩放 
	Mat M6 = TF6.getTransformMatrix();
	warpAffine(img, figure6, M6, Size(600, 600), INTER_CUBIC);
	imshow("figure6", figure6);
	
	transformation TF7(100.0f, 300.0f, 1.0, 45);  // 水平移位 + 旋转  (此时scale=1.0)
	Mat M7 = TF7.getTransformMatrix();
	warpAffine(img, figure7, M7, Size(600, 600), INTER_CUBIC);
	imshow("figure7", figure7);
	
	transformation TF8(150.0f, 150.0f, 0.5, 60);  // 水平移位 + 缩放 + 旋转
	Mat M8 = TF8.getTransformMatrix();
	warpAffine(img, figure8, M8, Size(600, 600), INTER_AREA);
	imshow("figure8", figure8);

	Point2f center2(0.0f, 300.0f);
	transformation TF9(0.0f, 300.0f, 1.2, 45);  // 水平移位 + 指定中心点 + 缩放 + 旋转    
	Mat M9 = TF9.getTransformMatrix();
	warpAffine(img, figure9, M9, Size(600, 600), INTER_CUBIC);
	imshow("figure9", figure9);

	waitKey();



}