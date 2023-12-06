#include<iostream>
#include <opencv2/opencv.hpp>
#include "../include/imgReader.h"

using namespace cv;
using namespace std;

vector<int> imgReader() {

	vector<int> identify_result = {0,0,0,0};

	cout << "OpenCV Version: " << CV_VERSION << endl;
	//Mat img = imread("C:\\workspace\\cppProject\\paper.jpg");
	Mat img = imread("C:\\workspace\\cppProject\\img\\paper1.jpg", IMREAD_GRAYSCALE); //读取图像，转为灰度图
	if (img.empty()) {
		return identify_result;
	}
	//imshow("展示灰度图", img);

	//使用 cv::Rect 指定矩形的左上角的坐标，以及它的宽和高，提取 ROI 区域。四个形参分别表示 x 坐标，y 坐标，宽，高
	// 单选区域
	Rect single_region(110, 520, 1450, 140);
	Mat img_roi_single_region = img(single_region);

	//第一题的四个选项区域
	vector<Rect> img_roi_single_region_option;
	img_roi_single_region_option.push_back(Rect(130, 25, 40, 20));
	img_roi_single_region_option.push_back(Rect(170, 25, 40, 20));
	img_roi_single_region_option.push_back(Rect(225, 25, 40, 20));
	img_roi_single_region_option.push_back(Rect(270, 25, 40, 20));

	for (size_t i = 0; i < img_roi_single_region_option.size(); ++i) {
		Mat current_identification_area = img_roi_single_region(img_roi_single_region_option[i]);
		//imshow("选项区域", roi_option); 
		
		// 二值化，阈值200(填涂越黑越接近0，没填涂部分接近255)，高于阈值的像素设置为255，否则设置为0
		threshold(current_identification_area, current_identification_area, 200, 255, cv::THRESH_BINARY);
		//imshow("填涂区域二值化", current_identification_area);

		vector<vector<Point>> contours;
		// 检测二值图像轮廓，RETR_EXTERNAL只检测最外层轮廓，并且保存轮廓上所有点集到contours
		// 如果图像中有多个并列的最外层轮廓，那么contours中就会保存多个轮廓。
		// contours向量是由多个向量组成的，这些子向量存放的都是代表轮廓的点集。
		// 每个子向量代表一个独立的轮廓，每个轮廓就是一组的点(x, y)，表示这个轮廓上的所有坐标点。
		// contours[轮廓索引][点索引] = cv::Point(x, y)
		findContours(current_identification_area, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		//boundingRect,返回包围轮廓的矩形的边界信息。左上角顶点的坐标值及矩形边界的宽和高
		//roi_option_0(boundingRect(contour))对区域提取
		// 像素总数就是宽度与高度的乘积
		//countNonZero给定图像中非0像素的数目
		for (const auto& contour : contours)
		{
			Mat temp = current_identification_area(boundingRect(contour));
			int totalPix = temp.cols * temp.rows;
			int nonZeroPix = countNonZero(temp);
			double result = static_cast<double>(nonZeroPix) / totalPix;
			cout << "像素总数" << totalPix << "；非0像素的数目/像素总数" << result << endl;

			if (totalPix > 700 && result < 0.4)
			{
				// 选项区域40*20=800，取大于700的轮廓，大于60%的区域为黑色区域，认为被填涂
				identify_result[i] = 1;
			}
		}	
	}
	cout << "第一题识别结果" << endl;
	for (int result : identify_result) {
		cout << result << endl;
	}
	imshow("Image ROI with Marks", img_roi_single_region);
	waitKey();
	return identify_result;
}