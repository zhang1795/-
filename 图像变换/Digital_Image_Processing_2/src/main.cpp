#include <highgui.hpp>
#include <imgproc.hpp>
#include <imgcodecs.hpp>
#include <vector>
#include<iostream>

#include "image_algorithm.h"  // ����Զ����㷨

using namespace cv;

int main()
{
	std::string filepath = "c:/users/34148/pictures/lena.jpg";
	Mat img = imread(filepath);
	imshow("lena", img);
	waitKey();
}