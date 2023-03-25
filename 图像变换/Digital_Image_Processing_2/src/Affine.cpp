//**********************************************仿射变换有关函数和结构********************************************//
#include <highgui.hpp>
#include <imgproc.hpp>
#include <imgcodecs.hpp>
#include <vector>
#include<iostream>

using namespace cv;


// 插值法：仅提供 INTER_NEAREST  INTER_LINEAR INTER_CUBIC   
// 边界模式： 暂时有BORDER_CONSTANT
void affine(Mat& src, Mat& dst, Mat& M,Size dsize,int flags = INTER_LINEAR,int borderMode = BORDER_CONSTANT,Scalar borderValue = Scalar())
{





}




