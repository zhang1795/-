// --------------------------------------添加椒盐噪声------------------------------------------------
//#include <highgui.hpp>
//#include <imgproc.hpp>
//#include <imgcodecs.hpp>
//#include <iostream>
//#include <vector>
//#include <chrono>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//    Mat image = imread("C:\\Users\\34148\\Pictures\\铃芽之旅.jpg");
//    if (image.empty())
//    {
//        cout << "Could not open or find the image" << endl;
//        return -1;
//    }
//
//    Mat noisyImage = image.clone();
//    randu(noisyImage, 0, 255);
//
//    Mat saltpepper = Mat::zeros(image.size(), CV_8U);
//    randu(saltpepper, 0, 255);
//
//    Mat black = saltpepper < 30;
//    Mat white = saltpepper > 225;
//
//    noisyImage.setTo(255, white);
//    noisyImage.setTo(0, black);
//
//    imwrite("C:\\Users\\34148\\Pictures\\noisyImage.jpg", noisyImage);
//
//    return 0;
//}

// -----------------------------------------------图片通道分离----------------------------------------
//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//    Mat img = imread("C:\\Users\\34148\\Pictures\\weathering with you.jpg");
//    if (img.empty())
//    {
//        cout << "Could not read the image" << endl;
//        return 1;
//    }
//
//    vector<Mat> channels;
//    split(img, channels);
//
//    imwrite("C:\\Users\\34148\\Pictures\\red.jpg", channels[2]);
//    imwrite("C:\\Users\\34148\\Pictures\\green.jpg", channels[1]);
//    imwrite("C:\\Users\\34148\\Pictures\\blue.jpg", channels[0]);
//
//    return 0;
//}

// --------------------------------图像对比度增强------------------------------
//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//    Mat img = imread("C:\\Users\\34148\\Pictures\\加藤惠.jpg");
//    if (img.empty())
//    {
//        cout << "Could not read the image: " << endl;
//        return 1;
//    }
//
//    Mat imgContrastHigh2;
//    img.convertTo(imgContrastHigh2, -1, 2, 0); //increase the contrast by a factor of 2
//
//    namedWindow("Original Image", WINDOW_NORMAL);
//    namedWindow("New Image", WINDOW_NORMAL);
//
//    imshow("Original Image", img);
//    imshow("New Image", imgContrastHigh2);
//
//    waitKey(0);
//
//    destroyAllWindows();
//
//    return 0;
//}

// ----------------------------------------图像饱和度增强------------------------------------
#include <opencv2/opencv.hpp>
 

int main() {
    // 读取图片
    cv::Mat img = cv::imread("C:\\Users\\34148\\Pictures\\bless bloom.png");

    // 将图片转化为HSV颜色空间
    cv::Mat hsv_img;
    cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);

    // 分离出HSV三个通道
    std::vector<cv::Mat> channels;
    cv::split(hsv_img, channels);

    // 对S通道进行增加
    double scale = 1.2;  // 饱和度增加倍数
    channels[1] *= scale;

    // 合并三个通道，得到增加饱和度后的图像
    cv::Mat saturated_img;
    cv::merge(channels, hsv_img);
    cv::cvtColor(hsv_img, saturated_img, cv::COLOR_HSV2BGR);

    // 显示增加饱和度后的图像
    cv::imshow("Saturated Image", saturated_img);
    cv::imwrite("C:\\Users\\34148\\Pictures\\1.png", saturated_img);
    cv::waitKey(0);

    return 0;
}

