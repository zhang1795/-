#include <highgui.hpp>
#include <imgproc.hpp>
#include <imgcodecs.hpp>
#include <iostream>
#include <vector>
#include <chrono>

using namespace cv;

int main()
{
	namedWindow("����֮��");
	std::string filepath1 = "C:\\Users\\34148\\Pictures\\weathering with you.jpg";
	Mat img1 = imread(filepath1);
	resize(img1, img1, Size(),0.5, 0.5,INTER_AREA);
	imshow("����֮��", img1);
	moveWindow("����֮��", 0, 0);
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

//**************************************************************************************************************************//

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
	 resize(img2, img2, Size(700,500),0,0,INTER_AREA);
	 imshow("��ѿ֮��(��)", img2);
	 flip(img2.t(),img2,1);  // Mat::t()��������ת��
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
		 pixel[2] += rand();         // ����img.forEach�ķ���
		 }
	 );
	 auto t8 = std::chrono::high_resolution_clock::now();
	 auto duration4 = std::chrono::duration_cast<std::chrono::milliseconds>(t8 - t7).count();
	 std::cout << "img.forEach����������ʱ��Ϊ��" << duration4 << " ms." << std::endl;
	 imshow("��ѿ֮��(������4)", img2);
	 waitKey();

//**************************************************************************************************************************//
     // mat���󷽷�ʹ��
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
	 std::cout << img2.elemSize() << "," << img2.elemSize1() << "," << img2.size() << ", " << img2.type() << std::endl;

	 // Mat::create����
	 Mat matrix4;
	 matrix4.create(400, 400, CV_8UC3);  // ����ָ���ض�����ɫ
	 imshow("Ĭ�ϻ�ɫ", matrix4);
	 std::cout << matrix4.col(1) << std::endl;
     // ���Բ���setTo������"="���������ʵ��
	 matrix4 = Scalar(0, 0, 0);

	 imshow("����=���������Ϊ��ɫ", matrix4);
	 matrix4.setTo(Scalar(255, 255, 255));
	 imshow("����setTo��������Ϊ��ɫ", matrix4);
	 // setTo���õ����룬���ԶԲ���������ֵ���иı�
	 Mat mask = Mat::diag(Mat(400, 1, CV_8UC1, Scalar(1)));   // �����Խ��ߵľ���
	 matrix4.setTo(Scalar(0, 0, 0), mask);
	 imshow("����setTo������������������Խ�������Ϊ��ɫ", matrix4);
	 // setTo�Ծ����Ӿ���ֵ���Ӷ��ı�ԭ�����ֵ
	 Mat subMatrix4_1 = matrix4.colRange(200,205);  // ���õ��е���ʱ����col��row��ָ��   ���з�Χʱ����colRange��rowRange
	 subMatrix4_1.setTo(Scalar(0, 0, 255));  
	 // Ҳ������Rect��ָ��������ɵľ���������иı�
	 //Rect roi(300, 300, 320, 320);
	// Mat subMatrix4_2 = matrix4(roi);
	//subMatrix4_2.setTo(Scalar(0, 255, 0));
	 imshow("����setTo������ֵ�Ӿ��󣬽�200-204��������Ϊ��ɫ,300-310�к�300-320����ɵ���ɫ����", matrix4);
	  
	 // Mat::ones �� Mat::zeros
	 Mat matrix5 = Mat::zeros(400, 400, CV_8UC3);
	 Mat matrix6 = Mat::ones(400, 400, CV_8UC3); 
	 imshow("����5", matrix5);
	 imshow("����6", matrix6);         //������ΪCV_8UC3ʱ����������ʾ��ɫ
	 waitKey();
	 
//**************************************************************************************************************************//
	 Mat img3 = imread("c:/users/34148/pictures/lena.jpg");  // lenaԭͼ��
	 Mat M = (Mat_<float>(2, 3) << 1.5, 0, 50, 0, 1.5, 50);  // ����任���� ͼ��Ŵ�1.5����x��y����λ��Ϊ50��50
	 std::cout << M << std::endl;
	 Mat dst1, dst2, dst3;                                         // �������
	 warpAffine(img3, dst1, M, Size(700, 700), INTER_CUBIC);   // ѡ���ֵ����Ϊ˫���β�ֵ
	 imshow("��������λ�任", dst1);     
	  

	 // Mat figure = Mat::zeros(800, 800, CV_8UC3);   // ���崿�ڻ�������С: 800 X 800
	 //imshow("��ת�任", figure);
	 Mat img4 = img3.clone();
	 Mat M2 = (Mat_<float>(2, 3) << sqrt(2)/2, sqrt(2)/2, 0, -sqrt(2)/2, sqrt(2)/2, 250);  // ���ն��壬������ؼ���
	 warpAffine(img4, dst2, M2, Size(500, 500),INTER_LINEAR, BORDER_CONSTANT,Scalar(127,127,127)); //bordervalue���ڳ������ֵ���޾��ǣ�0��0��0��
	 //Ĭ�ϵ�bordermode��BORDER_CONSTANT(�޶��崦��ɫ)BORDER_REPLICATE(������չ)��BORDER_WRAP(�հײ���)
	 imshow("��ת�任", dst2); 
     
	 // opencv������ת�任����
	 Point2f center(img4.cols / 2.0f, img4.rows / 2.0f);   // ����������
	 double angle = 45.0, scale = -1.0;    //   
	 Mat M3 = getRotationMatrix2D(center, angle, scale);
	 warpAffine(img4, dst3, M3, Size(350, 350), INTER_LINEAR, BORDER_CONSTANT, Scalar(127, 127, 127));
	 imshow("��λ�Ƶ���ת�任", dst3);

	 
	 waitKey();
} 


