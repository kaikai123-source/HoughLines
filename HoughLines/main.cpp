
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
int main()
{
	std::string img_path;
	cv::Mat mat_color;
	cv::Mat mat_gray;
	cv::Mat mat_binary;
	cv::Mat mat_canny;

	mat_color = cv::imread(img_path, 1);
	mat_gray = cv::imread("D:\\2.png", 0);
	
	cv::Mat elementRect;
	elementRect = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));
	cv::morphologyEx(mat_gray, mat_gray, cv::MORPH_CLOSE, elementRect);
	
	
	cv::threshold(mat_gray, mat_binary, 125, 255.0, cv::THRESH_BINARY);


	cv::Canny(mat_binary, mat_canny, 50, 125, 3);

	
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(mat_canny, lines, 1, CV_PI / 180, 150, 0, 0);

	
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(mat_color, pt1, pt2, cv::Scalar(255, 0, 0), 1);
	}
	cv::imshow("gray", mat_gray);
	cv::imshow("dst", mat_canny);
	cv::waitKey(0);

	return 0;
}

