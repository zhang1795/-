#include <iostream>
#include <imgproc.hpp>
#include <highgui.hpp>
#include <imgcodecs.hpp>

int main()
{
	// 基本图片读取操作
	std::string img_path = "c:/users/34148/pictures/lena.jpg";
	cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
	cv::imshow("lena", img);
	int key = cv::waitKey(0);
	if (key == 'd') 
	{
		cv::imwrite("lena.png", img);
	}


	/*
	// 视频效果
	cv::VideoCapture cap(0);
	cv::Mat image1;
	while (true)
	{
		cap.read(image1);
		cv::imshow("Image", image1);
		cv::waitKey(1);
	}
	*/

	// 基础函数练习
	cv::Mat imgGray, imgRGB, imgBlur, imgCanny, imgDil, imgErode;
	// cv::cvtColor()
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);  // 灰度化
	cv::cvtColor(img, imgRGB, cv::COLOR_BGR2RGB);    // 转为RGB
	// cv::GaussianBlur()
	cv::GaussianBlur(img, imgBlur, cv::Size(7, 7), 10, 10);  // 高斯模糊
	//cv::Canny()
	cv::Canny(img, imgCanny, 50, 150);  // 边缘检测
	// cv::dilate()  cv::erode() 
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel); // 特定膨胀
	cv::erode(imgDil, imgErode, kernel);  // 图像腐蚀

	cv::imshow("ImageGray", imgGray);
	cv::imshow("ImageRGB", imgRGB);
	cv::imshow("ImageBlur", imgBlur);
	cv::imshow("ImageCanny", imgCanny);
	cv::imshow("ImageDilation", imgDil);
    cv::imshow("ImageErode", imgErode);
	cv::waitKey(0);

	// 调整和裁剪
	std::cout << img.size() << std::endl;
	cv::Mat imgResize, imgCrop;
	cv::resize(img, imgResize, cv::Size(), 0.5, 0.5);

	cv::Rect area(40, 100, 250, 250);
	imgCrop = img(area);

	cv::imshow("ImageResize", imgResize);
	cv::imshow("ImageCrop", imgCrop);
	cv::waitKey(0);
	
	// 绘制形状和文字
	cv::Mat img1(512,512,CV_8UC3,cv::Scalar(255, 255, 255));  // CV_8SC3代表3通道uchar类型，Scalar对应的是三通道中的值，img1为纯白方形
	cv::circle(img1, cv::Point(256, 256), 155, cv::Scalar(0, 0, 255),cv::FILLED); //绘制红色圆形
	cv::rectangle(img1, cv::Point(130, 226), cv::Point(382, 286), cv::Scalar(255, 255, 255), cv::FILLED);
	cv::line(img1, cv::Point(130, 296), cv::Point(382, 296), cv::Scalar(255, 255, 255),2);
	cv::putText(img1, "MEGUMI KATO", cv::Point(137, 262), cv::FONT_HERSHEY_COMPLEX, 0.95, cv::Scalar(0, 0, 255),2);
	cv::imshow("图片1", img1);

	int w = 400;
	cv::Mat img2 = cv::Mat::zeros(w, w, CV_8UC3);
	cv::ellipse(img2, cv::Point(w / 2, w / 2), cv::Size(w / 4, w / 16), 0, 0, 360, cv::Scalar(255, 0, 0), 2);
	cv::ellipse(img2, cv::Point(w / 2, w / 2), cv::Size(w / 4, w / 16), 45, 0, 360, cv::Scalar(255, 0, 0), 2);
	cv::ellipse(img2, cv::Point(w / 2, w / 2), cv::Size(w / 4, w / 16), -45, 0, 360, cv::Scalar(255, 0, 0), 2);
	cv::ellipse(img2, cv::Point(w / 2, w / 2), cv::Size(w / 4, w / 16), 90, 0, 360, cv::Scalar(255, 0, 0), 2);
	cv::circle(img2, cv::Point(w / 2, w / 2), w / 32, cv::Scalar(0, 0, 255), cv::FILLED);
	cv::imshow("图片2", img2);
	cv::waitKey(0);
}