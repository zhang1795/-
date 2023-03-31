//********************************************����任�йغ����ͽṹ********************************************//
#include <highgui.hpp>
#include <imgproc.hpp>
#include <imgcodecs.hpp>
#include <vector>
#include <iostream>
#include <cmath>

using namespace cv;

// �������任���������� 
void invertTransformMatrix(const Mat& src, Mat& dst)
{   
	dst.create(2, 3, CV_32FC1);
	try
	{
		if (src.cols != 3 || src.rows != 2)
		{
			throw "����任�����Ŀ������ά�ȱ���Ϊ(2,3)��";  // ��������쳣����
		}
		else
		{
			float a11 = src.at<float>(0, 0), a12 = src.at<float>(0, 1),
				  a21 = src.at<float>(1, 0), a22 = src.at<float>(1, 1),
				  b1  = src.at<float>(0, 2), b2  = src.at<float>(1, 2),
				  det = a11 * a22 - a12 * a21; //����ʽ
			
			if (det == 0.0)
			{
				throw "����任���󲻴��������";
			}
			else
			{
				dst.at<float>(0, 0) =  1/det * a22;  dst.at<float>(0, 1) = -1 / det * a12;
				dst.at<float>(1, 0) = -1/det * a21;  dst.at<float>(1, 1) =  1 / det * a11;
				dst.at<float>(0, 2) =  1/det * (b2 * a12 - b1 * a22);  
				dst.at<float>(1, 2) =  1/det * (b1 * a21 - b2 * a11); 
			}
		}
	}
	catch (const std::exception& err)
	{
		std::cout << "Error: " << err.what() << std::endl;
	}
}


// ��ֵ����
enum InterpolationType
{
	NEAREST_NEIGHBOR,
	BILINEAR,
	BICUBIC
};

float mitchell_netravali(float x, float B, float C)      // mitchell_netravali��ֵ��ͬopencv
{
	float x_abs = abs(x),
		  x_2   = x * x, 
	      x_3   = x_abs * x_2;
	if (x_abs < 1)
	{
		return ((12 - 9 * B - 6 * C) * x_3 + (-18 + 12 * B + 6 * C) * x_2 + (6 - 2 * B)) / 6;
	}          
	else if (x_abs < 2)
	{
		return ((-B - 6 * C) * x_3 + (6 * B + 30 * C) * x_2 - (12 * B + 48 * C) * x_abs + (8 * B + 24 * C)) / 6;
	}          
	else
	{
		return 0;
	}
}

void interpolation(const Mat& src, Mat& dst, Mat& invM, InterpolationType flags = BILINEAR, int borderMode = BORDER_CONSTANT, Scalar borderValue = Scalar())
{
	CV_Assert(src.type() == CV_8UC3 || src.type() == CV_8UC1 );     // �ֽ��������ΪCV_8UC3��CV_8UC1��ͼ����
	
	// 
	if (flags == NEAREST_NEIGHBOR)   // ����flags�����жϲ�ֵ��
	{
		for (int row = 0; row < dst.rows; row++)
			for (int col = 0; col < dst.cols; col++)
			{
				Mat vec = (Mat_<float>(3, 1) << row, col, 1.0);   // ��ȫ���о���˷�
				Point2f point = Point2f(Mat(invM * vec));         // ����ӳ��
				
				if (point.x >= 0 && point.y >= 0 && point.x < src.rows && point.y < src.cols)
				{
					int x = static_cast<int> (std::round(point.x)),
						y = static_cast<int> (std::round(point.y));  // ���������ȡ�������������

					if (src.channels() == 3)
					{
						dst.at<Vec3b>(col, row) = src.at<Vec3b>(y, x);
					}
					else if (src.channels() == 1)
					{
						dst.at<uchar>(col, row) = src.at<uchar>(y, x);
					}
				}
			}
	}
	else if (flags == BILINEAR)
	{
		for (int row = 0; row < dst.rows; row++)                   // ע�������һ�����
			for (int col = 0; col < dst.cols; col++)
			{
				Mat vec = (Mat_<float>(3, 1) << row, col, 1.0);   // ��ȫ�Խ��о���˷�
				Point2f point = Point2f(Mat(invM * vec));         // ����ӳ��
				// �����Ժ���ӳ�������ԭͼ��Χ�ڵ�Ŀ��ͼ�����ش����д���
				if (point.x >= 0 && point.y >= 0 && point.x < src.rows && point.y < src.cols)
				{
					int x0 = cvFloor(point.x), y0 = cvFloor(point.y),
						x1 = x0 + 1, y1 = y0 + 1;
					float w1 = point.x - x0, w2 = point.y - y0;


					// �ֽ�����CV_8UC3���ͺ�CV_8UC1����
					if (src.channels() == 3)						

					{   
						auto vec21 = src.at<Vec3b>(y0, x1);   auto vec22 = src.at<Vec3b>(y1, x1);
						auto vec11 = src.at<Vec3b>(y0, x0);   auto vec12 = src.at<Vec3b>(y1, x0);

						Vec3f Vec11 = Vec3f(vec11), Vec12 = Vec3f(vec12),
							  Vec21 = Vec3f(vec21), Vec22 = Vec3f(vec22),  // ת��ΪVec3f����
							  Vec1, Vec2, Vec;
						Vec1 = Vec11 + w1 * (Vec21 - Vec11);
						Vec2 = Vec12 + w1 * (Vec22 - Vec22);
						Vec = Vec1 + w2 * (Vec2 - Vec1);
						dst.at<Vec3b>(col, row) = Vec3b(Vec);
					}
					else if (src.channels() == 1)
					{
						auto vec11 = src.at<uchar>(y0, x0);   auto vec12 = src.at<uchar>(y1, x0);
						auto vec21 = src.at<uchar>(y0, x1);   auto vec22 = src.at<uchar>(y1, x1);

						float vec1, vec2, vec;
						vec1 = vec11 + w1 * (vec21 - vec11);
						vec2 = vec12 + w1 * (vec22 - vec22);
						vec = vec1 + w2 * (vec2 - vec1);
						dst.at<uchar>(col, row) = uchar(vec);
					}
				}
			}
	}
	else if (flags == BICUBIC)    // opencv����Mitchell-Netravali��ֵ
	{
		for (int row = 0; row < dst.rows; row++)                    
			for (int col = 0; col < dst.cols; col++)
			{
				Mat vec = (Mat_<float>(3, 1) << row, col, 1.0);    
				Point2f point = Point2f(Mat(invM * vec));     // ����ӳ��
                // ������ѡȡ���꣨x,y����ʮ�����������
				if (point.x >= 1 && point.y >= 1 && point.x < src.rows - 2 && point.y < src.cols - 2)    
				{
					int x0 = cvFloor(point.x),
						y0 = cvFloor(point.y);
				    
					if (src.channels() == 3)
					{
						Vec3f pixel = { 0.0, 0.0, 0.0 };
						for (int m = -1; m <= 2; ++m)
							for (int n = -1; n <= 2; ++n)
							{
								
								float wx = mitchell_netravali(point.x - (x0 + m), 0.3782, 0.3109),   // B��C��ѡȡ����opencv
									  wy = mitchell_netravali(point.y - (y0 + n), 0.3782, 0.3109),   // ˮƽȨ�غ���ֱȨ��
									  w  = wx * wy;
								pixel += w * Vec3f(src.at<Vec3b>(y0 + n, x0 + m));
							}
						dst.at<Vec3b>(col, row) = Vec3b(pixel);
					}
					else if (src.channels() == 1)
					{
						float pixel = 0.0;
						for (int m = -1; m <= 2; ++m)
							for (int n = -1; n <= 2; ++n)
							{
								float wx = mitchell_netravali(point.x - (x0 + m), 0.3782, 0.3109),   // B��C��ѡȡ����opencv
									  wy = mitchell_netravali(point.y - (y0 + n), 0.3782, 0.3109),
									  w  = wx * wy;
								pixel += w * src.at<uchar>(y0 + n, x0 + m);
							}
						dst.at<uchar>(col, row) = static_cast<uchar>(pixel);
					}
				}
			}
	}
}



// ��ֵ�������ṩ INTER_NEAREST  INTER_LINEAR INTER_CUBIC   
// �߽�ģʽ�� ��ʱ��BORDER_CONSTANT
void affine(const Mat& src, Mat& dst, Mat& M,Size dsize, InterpolationType flags = BILINEAR,int borderMode = BORDER_CONSTANT,Scalar borderValue = Scalar())
{
	dst = Mat::zeros(dsize, src.type()); // ��Ŀ��ͼ����г�ʼ��
	Mat invM;                            // Ԥ�ȶ������任�������
	invertTransformMatrix(M, invM);      // ��������
	interpolation(src, dst, invM, flags, borderMode, borderValue);   // ���ò�ֵ������ʵ������ӳ��

}



