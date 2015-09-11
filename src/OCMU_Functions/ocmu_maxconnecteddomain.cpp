#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat_<uchar> ocmu_maxconnecteddomain(cv::Mat_<uchar> binImg)
{	
	cv::Mat_<uchar> maxRegion; // Returned matrix;

	// ������������Ӧ��ͨ�� 
	cv::Mat_<uchar> contourImg;
	binImg.copyTo(contourImg);
	std::vector<std::vector<cv::Point>> contourVecs;  
	cv::findContours(contourImg, contourVecs,CV_RETR_EXTERNAL, \
		CV_CHAIN_APPROX_NONE);
		 
	if (contourVecs.size() > 0) { // ���ڶ����ͨ��Ѱ�������ͨ�� 
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
		int xBegPos = maxRect.y;
		int yBegPos = maxRect.x;
		int xEndPos = xBegPos + maxRect.height;
		int yEndPos = yBegPos + maxRect.width;

		maxRegion = binImg(cv::Range(xBegPos, xEndPos), \
			cv::Range(yBegPos, yEndPos));
	}

	return maxRegion;
}