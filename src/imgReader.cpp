#include<iostream>
#include <opencv2/opencv.hpp>
#include "../include/imgReader.h"

using namespace cv;
using namespace std;

vector<int> imgReader() {

	vector<int> identify_result = {0,0,0,0};

	cout << "OpenCV Version: " << CV_VERSION << endl;
	//Mat img = imread("C:\\workspace\\cppProject\\paper.jpg");
	Mat img = imread("C:\\workspace\\cppProject\\img\\paper1.jpg", IMREAD_GRAYSCALE); //��ȡͼ��תΪ�Ҷ�ͼ
	if (img.empty()) {
		return identify_result;
	}
	//imshow("չʾ�Ҷ�ͼ", img);

	//ʹ�� cv::Rect ָ�����ε����Ͻǵ����꣬�Լ����Ŀ�͸ߣ���ȡ ROI �����ĸ��βηֱ��ʾ x ���꣬y ���꣬����
	// ��ѡ����
	Rect single_region(110, 520, 1450, 140);
	Mat img_roi_single_region = img(single_region);

	//��һ����ĸ�ѡ������
	vector<Rect> img_roi_single_region_option;
	img_roi_single_region_option.push_back(Rect(130, 25, 40, 20));
	img_roi_single_region_option.push_back(Rect(170, 25, 40, 20));
	img_roi_single_region_option.push_back(Rect(225, 25, 40, 20));
	img_roi_single_region_option.push_back(Rect(270, 25, 40, 20));

	for (size_t i = 0; i < img_roi_single_region_option.size(); ++i) {
		Mat current_identification_area = img_roi_single_region(img_roi_single_region_option[i]);
		//imshow("ѡ������", roi_option); 
		
		// ��ֵ������ֵ200(��ͿԽ��Խ�ӽ�0��û��Ϳ���ֽӽ�255)��������ֵ����������Ϊ255����������Ϊ0
		threshold(current_identification_area, current_identification_area, 200, 255, cv::THRESH_BINARY);
		//imshow("��Ϳ�����ֵ��", current_identification_area);

		vector<vector<Point>> contours;
		// ����ֵͼ��������RETR_EXTERNALֻ�����������������ұ������������е㼯��contours
		// ���ͼ�����ж�����е��������������ôcontours�оͻᱣ����������
		// contours�������ɶ��������ɵģ���Щ��������ŵĶ��Ǵ��������ĵ㼯��
		// ÿ������������һ��������������ÿ����������һ��ĵ�(x, y)����ʾ��������ϵ���������㡣
		// contours[��������][������] = cv::Point(x, y)
		findContours(current_identification_area, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		//boundingRect,���ذ�Χ�����ľ��εı߽���Ϣ�����ϽǶ��������ֵ�����α߽�Ŀ�͸�
		//roi_option_0(boundingRect(contour))��������ȡ
		// �����������ǿ����߶ȵĳ˻�
		//countNonZero����ͼ���з�0���ص���Ŀ
		for (const auto& contour : contours)
		{
			Mat temp = current_identification_area(boundingRect(contour));
			int totalPix = temp.cols * temp.rows;
			int nonZeroPix = countNonZero(temp);
			double result = static_cast<double>(nonZeroPix) / totalPix;
			cout << "��������" << totalPix << "����0���ص���Ŀ/��������" << result << endl;

			if (totalPix > 700 && result < 0.4)
			{
				// ѡ������40*20=800��ȡ����700������������60%������Ϊ��ɫ������Ϊ����Ϳ
				identify_result[i] = 1;
			}
		}	
	}
	cout << "��һ��ʶ����" << endl;
	for (int result : identify_result) {
		cout << result << endl;
	}
	imshow("Image ROI with Marks", img_roi_single_region);
	waitKey();
	return identify_result;
}