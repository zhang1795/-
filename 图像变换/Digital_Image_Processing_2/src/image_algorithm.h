//***************************************�Զ���ͼ�����㷨ͷ�ļ�*******************************************//
#pragma once
#include <highgui.hpp>
#include <imgproc.hpp>
#include <imgcodecs.hpp>
constexpr auto Pi = 3.1415926;

using namespace cv;

// ����任�������ο�opencv��warpAffine����
void affine(Mat& src, Mat& dst, Mat& M, Size dsize, int flags = INTER_LINEAR, 
	        int borderMode = BORDER_CONSTANT, Scalar borderValue = Scalar());


 

//  �������任��
class  transformation
{
public:
	float x0, y0;          // ˮƽλ��x0,��ֱλ��y0
	Point2f center;        // ��ת���ĵ�
	double scale,angle;    // �������ӣ���ת�Ƕ�(Ĭ�ϽǶ���)
	// ���캯��
	transformation()
		:x0(0.0), y0(0.0), center(Point2f(0.0, 0.0)), scale(1.0), angle(0.0) {}

	transformation(float x0,float y0)
		:x0(x0), y0(y0), center(Point2f(0.0, 0.0)), scale(1.0), angle(0.0) {}

	transformation(double scale)
		:x0(0.0), y0(0.0), center(Point2f(0.0, 0.0)), scale(scale), angle(0.0) {}

	transformation(double scale,double angle)
		:x0(0.0), y0(0.0), center(Point2f(0.0, 0.0)), scale(scale), angle(angle * Pi / 180.0) {}

	transformation(Point2f center, double scale, double angle)
		:x0(0.0), y0(0.0), center(center), scale(scale), angle(angle * Pi / 180.0) {}

	transformation(float x0, float y0, double scale)
		:x0(x0), y0(y0), center(Point2f(0.0, 0.0)), scale(scale), angle(0.0) {}

	transformation(float x0, float y0, double scale, double angle)
		:x0(x0), y0(y0), center(Point2f(0.0, 0.0)), scale(scale), angle(angle* Pi / 180.0) {}

	transformation(float x0, float y0, Point2f center, double scale, double angle)
		:x0(x0), y0(y0), center(center), scale(scale), angle(angle* Pi / 180.0){}

	Mat getTransformMatrix()
	{
		Mat_<float>   M(2, 3);  // �任���� 2X3 , ������ͬ��Mat���巨
		float alpha = scale * cos(angle), beta = scale * sin(angle);
		// ��������ֵ
		M(0, 0) = alpha; M(0, 1) = beta;  M(0, 2) = (1 - alpha) *  center.x - beta *  center.y + x0;
		M(1, 0) = -beta; M(1, 1) = alpha; M(1, 2) = beta *  center.x   + (1 - alpha) *  center.y + y0;

		return M;
	}
};

