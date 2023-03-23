#include <highgui.hpp>
#include <imgproc.hpp>
#include <imgcodecs.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <core/mat.inl.hpp>

using namespace cv;

int main()
{
	namedWindow("����֮��");
	std::string filepath1 = "C:\\Users\\34148\\Pictures\\weathering with you.jpg";
	Mat img1 = imread(filepath1);
	resize(img1, img1, Size(),0.5, 0.5);
	imshow("����֮��", img1);
	waitKey(0);

	 const int array[] = { 300,500 }, n = 2;
	 std::vector<int> vector1 = { 300,500 };
	 Mat matrix1(Size(300, 500), CV_8UC3, Scalar(255, 255, 255)), 
		 matrix2(n, array, CV_8SC3, Scalar(-127,  127, -127)), 
		 matrix3(vector1, CV_8UC3, Scalar(0, 0, 255));
	 imshow("figure1", matrix1);
	 imshow("figure2", matrix2);
     imshow("figure3", matrix3);
	 
	 std::cout << matrix1.size().height<< matrix2.cols << matrix3.rows << std::endl;
	 std::cout << matrix1.col(100) << std::endl;
 	 std::cout << matrix2.colRange(100, 102) << std::endl << matrix3.rowRange(3, 5) << std::endl;
	 std::cout << matrix1.at<Vec3b>(10, 10) << std::endl;
	 std::cout << matrix1.channels() << std::endl;

	 // ���ز���
	 for (int i = 0; i < matrix2.rows; i++)
	 {
		 for (int j = 0; j < matrix2.cols; j++)
		 {
			 matrix2.at<Vec3b>(i, j)[1] = -127;
		 }
	 }
	 imshow("figure4", matrix2);
	  
	 std::string filepath2 = "C:\\Users\\34148\\Pictures\\��ѿ֮��.jpg";
	 Mat img2 = imread(filepath2);
	 resize(img2, img2, Size(700,500));
	 imshow("��ѿ֮��(��)", img2);
	 flip(img2.t(),img2,1);
	 imshow("��ѿ֮��(��)", img2);


	 // ��������������ز�ͬ���ʷ�ʽ��Ч�ʽ��бȽ�
	 
	 auto t1 = std::chrono::high_resolution_clock::now();
	 for (int i = 0; i < img2.rows; i++)
	 {
		 for (int j = 0; j < img2.cols; j++)
		 {
			 img2.at<Vec3b>(i, j)[2] +=  rand();    // img.at<type>��i,j������
		 }
	 }
	 auto t2 = std::chrono::high_resolution_clock::now();
	 auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	 std::cout << "img.at<type>��i,j������������ʱ��Ϊ��" << duration1 << " ms." << std::endl;
	 imshow("��ѿ֮��(������1)", img2);

	 auto t3 = std::chrono::high_resolution_clock::now();
	 for (auto it = img2.begin<Vec3b>(); it != img2.begin<Vec3b>(); it++)
	 {
		 Vec3b  pixel = *it;                    // ������������Ч�ʽϸ�
		 pixel[2] += rand();
	 }
	 auto t4 = std::chrono::high_resolution_clock::now();
	 auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
	 std::cout << "����������������ʱ��Ϊ��" << duration2 << " us." << std::endl;
	 imshow("��ѿ֮��(������2)", img2);

	 auto t5 = std::chrono::high_resolution_clock::now();
	 for (int row = 0; row < img2.rows; row++)
	 {
		 Vec3b* ptr = img2.ptr<Vec3b>(row);
		 for (int col = 0; col < img2.cols; col++)
		 {
			 ptr[col][2] += rand();   // ����img.ptr�ķ���
		 }
	 }
	 auto t6 = std::chrono::high_resolution_clock::now();
	 auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t5).count();
	 std::cout << "img.ptr����������ʱ��Ϊ��" << duration3 << " ms." << std::endl;
	 imshow("��ѿ֮��(������3)", img2);

	 auto t7 = std::chrono::high_resolution_clock::now();
	 img2.forEach<cv::Vec3b>([](Vec3b & pixel, const int* position){
		 pixel[2] += rand();
		 }
	 );
	 auto t8 = std::chrono::high_resolution_clock::now();
	 auto duration4 = std::chrono::duration_cast<std::chrono::milliseconds>(t8 - t7).count();
	 std::cout << "img.forEach����������ʱ��Ϊ��" << duration4 << " ms." << std::endl;
	 imshow("��ѿ֮��(������4)", img2);

 
	 //Vec<uchar,3>* pointer = img2.ptr<Vec<uchar, 3>>(0);
  	 Vec3b* pointer = img2.ptr<Vec3b>(0);
	 std::cout << *pointer << std::endl;
	 std::cout <<  pointer[1] << std::endl;
	 pointer[2] = { 208,158,145 };
	 *(img2.data) = 208;  // �����[0][0]λ��
	 std::cout << img2.row(0) << std::endl;
	 std::cout << img2.step[0] <<"," << img2.step[1] << std::endl;  // [0]��ʾ�þ���һ������ռ�õ��ֽ�����   
                                                                    // [1]��ʾ�������ص�����ͨ��ռ�õ��ֽ���
 	 std::cout << img2.step1(0) << "," << img2.step1(1) << std::endl;
	 std::cout << img2.elemSize() << "," << img2.elemSize1() << "," << img2.size() << std::endl;

	 Mat matrix4;
	 matrix4.create(400, 400, CV_8UC1);
	 
	 waitKey();
	 
	 
} 


