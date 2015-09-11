#include <opencv2/opencv.hpp>
#include <iostream>
#include "..\Headers\ocmu_functions.h"

extern std::string projectPath;

void demo_ocmu_maxconnecteddomain()
{
	std::string imgPathStr = projectPath + "images\\opencv-logo2.png";
	cv::Mat_<uchar> img = cv::imread(imgPathStr, CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat_<uchar> binImg = img < 128;
	cv::imshow("binImg 1", binImg);

	// ������������Ӧ��ͨ�� 
	cv::Mat_<uchar> contourImg;
	binImg.copyTo(contourImg);
	std::vector<std::vector<cv::Point>> contourVecs;  
	cv::findContours(contourImg, contourVecs,CV_RETR_EXTERNAL, \
		CV_CHAIN_APPROX_NONE);  

	// Ѱ�������ͨ��  
	double maxArea = 0;  
	std::vector<cv::Point> maxContour;  
	for(size_t i = 0; i < contourVecs.size(); i++) {  
		double area = cv::contourArea(contourVecs[i]);  
		if (area > maxArea) {  
			maxArea = area;  
			maxContour = contourVecs[i];  
		}  
	}  

	// ������תΪ���ο�  
	cv::Rect maxRect = cv::boundingRect(maxContour);  	

	// ��ʾ��ͨ��  
	cv::Mat result1, result2;  
	binImg.copyTo(result1);  
	binImg.copyTo(result2);  
	for (size_t i = 0; i < contourVecs.size(); i++) {  
		cv::Rect r = cv::boundingRect(contourVecs[i]);  
		cv::rectangle(result1, r, cv::Scalar(255));  
	}  

	cv::rectangle(result2, maxRect, cv::Scalar(255));  

	cv::Mat_<uchar> maxRegion = ocmu_maxconnecteddomain(binImg);

	if (!maxRegion.data) {
		std::cout<<"Maximum connected region does not exist."<<std::endl;		
	} else {
		std::cout<<"Maximum connected region exists."<<std::endl;
	}

	cv::imshow("all regions", result1) ;  
	cv::imshow("largest region", result2) ;  
	cv::imshow("maxRegion by ocmu_maxconnecteddomain", maxRegion) ;  	 
	cv::waitKey();  
}