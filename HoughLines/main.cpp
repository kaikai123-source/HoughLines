
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	cv::Mat src;
	cv::Mat mat_color;
	cv::Mat mat_gray;
	cv::Mat mat_binary;
	cv::Mat mat_canny;

	src= cv::imread("D:\\2.png", 1);
	mat_gray = cv::imread("D:\\2.png", 0);
	
	cv::Mat elementRect;
	elementRect = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));
	cv::morphologyEx(mat_gray, mat_gray, cv::MORPH_CLOSE, elementRect);
	
	
	cv::threshold(mat_gray, mat_binary, 125, 255.0, cv::THRESH_BINARY);


	cv::Canny(mat_binary, mat_canny, 50, 125, 3);

	
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(mat_canny, lines, 1, CV_PI / 180, 60);


	vector<cv::Vec2f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it) {
		float rho = (*it)[0], theta = (*it)[1];
		Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a*rho;
		double y0 = b*rho;
		pt1.x = saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = saturate_cast<int>(x0 -1000 * (-b));
		pt2.y = saturate_cast<int>(y0 - 1000 * (a));
		line(src, pt1, pt2, Scalar(0, 255,55), 1, CV_AA);
	}
	cv::imshow("src", src);
	cv::imshow("dst", mat_canny);
	cv::waitKey(0);

	return 0;
}

