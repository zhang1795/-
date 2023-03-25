#include <highgui.hpp>
#include <imgproc.hpp>
#include <imgcodecs.hpp>
#include <iostream>
#include <vector>
#include <chrono>

using namespace cv;

int main()
{
	namedWindow("天气之子");
	std::string filepath1 = "C:\\Users\\34148\\Pictures\\weathering with you.jpg";
	Mat img1 = imread(filepath1);
	resize(img1, img1, Size(),0.5, 0.5,INTER_AREA);
	imshow("天气之子", img1);
	moveWindow("天气之子", 0, 0);
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

	 // 像素操作
	 for (int i = 0; i < matrix2.rows; i++)
	 {
		 for (int j = 0; j < matrix2.cols; j++)
		 {
			 matrix2.at<Vec3b>(i, j)[1] = -127;
		 }
	 }
	 imshow("figure4", matrix2);
	  
	 std::string filepath2 = "C:\\Users\\34148\\Pictures\\铃芽之旅.jpg";
	 Mat img2 = imread(filepath2);
	 resize(img2, img2, Size(700,500),0,0,INTER_AREA);
	 imshow("铃芽之旅(侧)", img2);
	 flip(img2.t(),img2,1);  // Mat::t()方法进行转置
	 imshow("铃芽之旅(正)", img2);

	 // 添加噪声并对像素不同访问方式的效率进行比较
	 auto t1 = std::chrono::high_resolution_clock::now();
	 for (int i = 0; i < img2.rows; i++)
	 {
		 for (int j = 0; j < img2.cols; j++)
		 {
			 img2.at<Vec3b>(i, j)[2] +=  rand();    // img.at<type>（i,j）方法
		 }
	 }
	 auto t2 = std::chrono::high_resolution_clock::now();
	 auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	 std::cout << "img.at<type>（i,j）方法的运行时间为：" << duration1 << " ms." << std::endl;
	 imshow("铃芽之旅(含噪声1)", img2);

	 auto t3 = std::chrono::high_resolution_clock::now();
	 for (auto it = img2.begin<Vec3b>(); it != img2.begin<Vec3b>(); it++)
	 {
		 Vec3b  pixel = *it;                    // 迭代器方法，效率较高
		 pixel[2] += rand();
	 }
	 auto t4 = std::chrono::high_resolution_clock::now();
	 auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
	 std::cout << "迭代器方法的运行时间为：" << duration2 << " us." << std::endl;
	 imshow("铃芽之旅(含噪声2)", img2);

	 auto t5 = std::chrono::high_resolution_clock::now();
	 for (int row = 0; row < img2.rows; row++)
	 {
		 Vec3b* ptr = img2.ptr<Vec3b>(row);
		 for (int col = 0; col < img2.cols; col++)
		 {
			 ptr[col][2] += rand();   // 采用img.ptr的方法
		 }
	 }
	 auto t6 = std::chrono::high_resolution_clock::now();
	 auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t5).count();
	 std::cout << "img.ptr方法的运行时间为：" << duration3 << " ms." << std::endl;
	 imshow("铃芽之旅(含噪声3)", img2);

	 auto t7 = std::chrono::high_resolution_clock::now();
	 img2.forEach<cv::Vec3b>([](Vec3b & pixel, const int* position){
		 pixel[2] += rand();         // 采用img.forEach的方法
		 }
	 );
	 auto t8 = std::chrono::high_resolution_clock::now();
	 auto duration4 = std::chrono::duration_cast<std::chrono::milliseconds>(t8 - t7).count();
	 std::cout << "img.forEach方法的运行时间为：" << duration4 << " ms." << std::endl;
	 imshow("铃芽之旅(含噪声4)", img2);
	 waitKey();

//**************************************************************************************************************************//
     // mat对象方法使用
	 //Vec<uchar,3>* pointer = img2.ptr<Vec<uchar, 3>>(0);
  	 Vec3b* pointer = img2.ptr<Vec3b>(0);
	 std::cout << *pointer << std::endl;
	 std::cout <<  pointer[1] << std::endl;
	 pointer[2] = { 208,158,145 };
	 *(img2.data) = 208;  // 矩阵的[0][0]位置
	 std::cout << img2.row(0) << std::endl;
	 std::cout << img2.step[0] <<"," << img2.step[1] << std::endl;  // [0]表示该矩阵一行中内占用的字节总数   
                                                                    // [1]表示单个像素的三个通道占用的字节数
 	 std::cout << img2.step1(0) << "," << img2.step1(1) << std::endl;
	 std::cout << img2.elemSize() << "," << img2.elemSize1() << "," << img2.size() << ", " << img2.type() << std::endl;

	 // Mat::create方法
	 Mat matrix4;
	 matrix4.create(400, 400, CV_8UC3);  // 不能指定特定的颜色
	 imshow("默认灰色", matrix4);
	 std::cout << matrix4.col(1) << std::endl;
     // 可以采用setTo方法和"="运算符号来实现
	 matrix4 = Scalar(0, 0, 0);

	 imshow("采用=运算符，置为黑色", matrix4);
	 matrix4.setTo(Scalar(255, 255, 255));
	 imshow("采用setTo方法，置为白色", matrix4);
	 // setTo设置的掩码，可以对部分区域数值进行改变
	 Mat mask = Mat::diag(Mat(400, 1, CV_8UC1, Scalar(1)));   // 创立对角线的矩阵
	 matrix4.setTo(Scalar(0, 0, 0), mask);
	 imshow("采用setTo方法及掩码参数，将对角线设置为黑色", matrix4);
	 // setTo对矩阵子矩阵赋值，从而改变原矩阵的值
	 Mat subMatrix4_1 = matrix4.colRange(200,205);  // 设置单列单行时可用col和row来指定   行列范围时可用colRange和rowRange
	 subMatrix4_1.setTo(Scalar(0, 0, 255));  
	 // 也可以用Rect对指定行列组成的矩形区域进行改变
	 //Rect roi(300, 300, 320, 320);
	// Mat subMatrix4_2 = matrix4(roi);
	//subMatrix4_2.setTo(Scalar(0, 255, 0));
	 imshow("采用setTo方法赋值子矩阵，将200-204列线设置为红色,300-310列和300-320列组成的绿色矩形", matrix4);
	  
	 // Mat::ones 及 Mat::zeros
	 Mat matrix5 = Mat::zeros(400, 400, CV_8UC3);
	 Mat matrix6 = Mat::ones(400, 400, CV_8UC3); 
	 imshow("矩阵5", matrix5);
	 imshow("矩阵6", matrix6);         //在类型为CV_8UC3时，两个均显示黑色
	 waitKey();
	 
//**************************************************************************************************************************//
	 Mat img3 = imread("c:/users/34148/pictures/lena.jpg");  // lena原图像
	 Mat M = (Mat_<float>(2, 3) << 1.5, 0, 50, 0, 1.5, 50);  // 仿射变换矩阵 图像放大1.5倍，x，y附加位移为50，50
	 std::cout << M << std::endl;
	 Mat dst1, dst2, dst3;                                         // 输出矩阵
	 warpAffine(img3, dst1, M, Size(700, 700), INTER_CUBIC);   // 选择插值方法为双三次插值
	 imshow("放缩及移位变换", dst1);     
	  

	 // Mat figure = Mat::zeros(800, 800, CV_8UC3);   // 定义纯黑画布，大小: 800 X 800
	 //imshow("旋转变换", figure);
	 Mat img4 = img3.clone();
	 Mat M2 = (Mat_<float>(2, 3) << sqrt(2)/2, sqrt(2)/2, 0, -sqrt(2)/2, sqrt(2)/2, 250);  // 按照定义，进行相关计算
	 warpAffine(img4, dst2, M2, Size(500, 500),INTER_LINEAR, BORDER_CONSTANT,Scalar(127,127,127)); //bordervalue用于常数填充值，无就是（0，0，0）
	 //默认的bordermode是BORDER_CONSTANT(无定义处黑色)BORDER_REPLICATE(边沿扩展)、BORDER_WRAP(空白补充)
	 imshow("旋转变换", dst2); 
     
	 // opencv计算旋转变换矩阵
	 Point2f center(img4.cols / 2.0f, img4.rows / 2.0f);   // 浮点数类型
	 double angle = 45.0, scale = -1.0;    //   
	 Mat M3 = getRotationMatrix2D(center, angle, scale);
	 warpAffine(img4, dst3, M3, Size(350, 350), INTER_LINEAR, BORDER_CONSTANT, Scalar(127, 127, 127));
	 imshow("无位移的旋转变换", dst3);

	 
	 waitKey();
} 


