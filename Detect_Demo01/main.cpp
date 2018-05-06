/************************************************************************
* Copyright(c) 2011  Yang Xian
* All rights reserved.
*
* File:	handGestureDetection.cpp
* Brief: 手势检测
* Version: 1.0
* Author: Yang Xian
* Email: xyang2011@sinano.ac.cn
* Date:	2011/12/01
* History:
************************************************************************/
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include<ctime>

#include <iostream>

using namespace std;
using namespace cv;

/** Function Headers */
Mat detectAndDisplay(Mat frame);
Mat Sign(Mat srcimage);
//Mat detectAndDisplay(string filename);

/** Global variables */
String face_cascade_name = "cars.xml";
string filename = "1.avi";
CascadeClassifier CHandCascade;
string window_name = "Car Detection";

bool a(false);
//定义感兴趣区域
//void SetROI(Mat srcimage)
//{
//	if (!a)
//	{
//		cout << "图像的宽度：" << srcimage.size().width << ",图像的高度：" << srcimage.size().height << endl;
//		a = true;
//	}
//	//rectangle(srcimage, Point(srcimage.size().width, (srcimage.size().height)/2 ), Point(0, srcimage.size().height), Scalar(0, 255, 255), 4, CV_AA);
//	//Mat imgROI = srcimage(Rect(Point(srcimage.size().width, (srcimage.size().height) / 2), Point(0, srcimage.size().height)));
//	rectangle(srcimage, Point(0, 540), Point(1920, 1080), Scalar(0, 255, 255), 4, CV_AA);
//	Mat imgROI = srcimage(Rect(Point(0, 540), Point(1920, 1080/5*4)));
//	vector<int> compression_params;
//	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
//	char image_name[201];
//}

bool cmp(double &num, const double &s, const double &l)
{
	if (num <= l && num >= s)
		return true;
	else
		return false;
}

int main(int argc, const char** argv)
{
	Mat frame;

	//-- 1. Load the cascades
	if (!CHandCascade.load(face_cascade_name))
	{
		printf("--(!)Error loading\n");
		return -1;
	}

	//-- 2. Read the video stream
	//CvCapture* capture = cvCaptureFromCAM( 0 );
	VideoCapture capture("..//Video 7.wmv");
	long totalframeNum = capture.get(CV_CAP_PROP_FRAME_COUNT);
	long ROIcol = (frame.cols) / 2;
	long ROIrow = (frame.rows) / 2;
	if (capture.isOpened())
	{
		for (size_t i = 0; i <= totalframeNum; i++)
		{
			size_t j = i;
			capture >> frame;
			//equalizeHist(frame, frame);
			//SetROI(frame);
			//Mat imgROI = frame(Rect(Point(frame.size().width, (frame.size().height) / 2), Point(0, frame.size().height)));
			if (frame.empty())
			{
				break;
			}
			else if (j != 0)
			{
				//double time0 = static_cast<double>(getTickCount());
				frame = detectAndDisplay(frame);
				frame = detectAndDisplay(frame);
				frame = Sign(frame);
				imshow("Detect", frame);
				//time0 = ((double)getTickCount() - time0) / getTickFrequency();
				//cout << "单次检测运行时间为：" << time0 << "秒" << endl;
			}
			
			int c = waitKey(10);
			if ((char)c == 27)
			{
				break;
			}

		}
	}
	return 0;
}

///**
//* @function detectAndDisplay
//*/
//Mat detectAndDisplay(string filename )
//{
//	Mat frame;
//	VideoCapture capture(filename);
//	vector<Rect> car;
//	Mat frame_gray;
//	Mat imgROI = frame(Rect(Point(0, 540), Point(1920, 1080 )));
//	cvtColor(frame, frame_gray, CV_BGR2GRAY);
//	equalizeHist(frame_gray, frame_gray);
//	//高斯滤波
//	//GaussianBlur(frame, frame, Size(5, 5), 1.5);
//
//	//拉普拉斯算子
//	//Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
//	//filter2D(frame_gray, frame_gray, CV_8UC3, kernel);
//
//	//对数Log变换增强
//	//Mat imageLog(frame.size(), CV_32FC3);
//	//for (int i = 0; i < frame.rows; i++)
//	//{
//	//	for (int j = 0; j < frame.cols; j++)
//	//	{
//	//		imageLog.at<Vec3f>(i, j)[0] = log(1 + frame.at<Vec3b>(i, j)[0]);
//	//		imageLog.at<Vec3f>(i, j)[1] = log(1 + frame.at<Vec3b>(i, j)[1]);
//	//		imageLog.at<Vec3f>(i, j)[2] = log(1 + frame.at<Vec3b>(i, j)[2]);
//	//	}
//	//}
//
//	////归一化到0~255    
//	//normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
//	////转换成8bit图像显示    
//	//convertScaleAbs(imageLog, frame);
//
//	////Gama变换增强
//	//Mat imageGamma(frame.size(), CV_32FC3);
//	//for (int i = 0; i < frame.rows; i++)
//	//{
//	//	for (int j = 0; j < frame.cols; j++)
//	//	{
//	//		imageGamma.at<Vec3f>(i, j)[0] = (frame.at<Vec3b>(i, j)[0])*(frame.at<Vec3b>(i, j)[0])*(frame.at<Vec3b>(i, j)[0]);
//	//		imageGamma.at<Vec3f>(i, j)[1] = (frame.at<Vec3b>(i, j)[1])*(frame.at<Vec3b>(i, j)[1])*(frame.at<Vec3b>(i, j)[1]);
//	//		imageGamma.at<Vec3f>(i, j)[2] = (frame.at<Vec3b>(i, j)[2])*(frame.at<Vec3b>(i, j)[2])*(frame.at<Vec3b>(i, j)[2]);
//	//	}
//	//}
//	////归一化到0~255    
//	//normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);
//	////转换成8bit图像显示    
//	//convertScaleAbs(imageGamma, frame);
//
//	long totalframeNum = capture.get(CV_CAP_PROP_FRAME_COUNT);
//	long ROIcol = (frame.cols) / 2;
//	long ROIrow = (frame.rows) / 2;
//
//	if (capture.isOpened())
//	{
//		//-- Detect faces
//
//		CHandCascade.detectMultiScale(imgROI, car, 1.1, 2, CV_HAAR_DO_CANNY_PRUNING, Size(22, 22));
//		//rectangle(frame, Point(0, 540), Point(1920, 1080/4*3), Scalar(0, 255, 255), 4, CV_AA);
//		for (size_t i = 0; i < car.size(); i++)
//		{
//			if ((car[i].height > 80) && (car[i].width > 80))
//			{
//				/*	cout << car[i].height << " " << car[i].width << endl;*/
//				rectangle(imgROI, car[i], Scalar(255, 0, 255));
//			}
//			else
//			{
//				continue;
//			}
//		}
//		//-- Show what you got
//	}
//	return frame;
//}



Mat detectAndDisplay(Mat frame)
{
	vector<Rect> car;
	Mat frame_gray;
	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//高斯滤波
	//GaussianBlur(frame, frame, Size(5, 5), 1.5);

	////拉普拉斯算子
	//Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
	//filter2D(frame_gray, frame_gray, CV_8UC3, kernel);

	////对数Log变换增强
	//Mat imageLog(frame.size(), CV_32FC3);
	//for (int i = 0; i < frame_gray.rows; i++)
	//{
	//	for (int j = 0; j < frame.cols; j++)
	//	{
	//		imageLog.at<Vec3f>(i, j)[0] = log(1 + frame.at<Vec3b>(i, j)[0]);
	//		imageLog.at<Vec3f>(i, j)[1] = log(1 + frame.at<Vec3b>(i, j)[1]);
	//		imageLog.at<Vec3f>(i, j)[2] = log(1 + frame.at<Vec3b>(i, j)[2]);
	//	}
	//}

	////归一化到0~255 
	//normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
	////转换成8bit图像显示    
	//Mat frame1;
	//convertScaleAbs(imageLog, frame1);

	//Gama变换增强
	//Mat imageGamma(frame.size(), CV_32FC3);
	//for (int i = 0; i < frame.rows; i++)
	//{
	//	for (int j = 0; j < frame.cols; j++)
	//	{
	//		imageGamma.at<Vec3f>(i, j)[0] = (frame.at<Vec3b>(i, j)[0])*(frame.at<Vec3b>(i, j)[0])*(frame.at<Vec3b>(i, j)[0]);
	//		imageGamma.at<Vec3f>(i, j)[1] = (frame.at<Vec3b>(i, j)[1])*(frame.at<Vec3b>(i, j)[1])*(frame.at<Vec3b>(i, j)[1]);
	//		imageGamma.at<Vec3f>(i, j)[2] = (frame.at<Vec3b>(i, j)[2])*(frame.at<Vec3b>(i, j)[2])*(frame.at<Vec3b>(i, j)[2]);
	//	}
	//}
	////归一化到0~255    
	//normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);
	////转换成8bit图像显示    
	//convertScaleAbs(imageGamma, frame);
	

	int _height = frame.rows;
	int _width = frame.cols;

	//-- Detect faces
	Mat imgROI = frame(Rect(Point(0, _height/2), Point(_width, _height)));
	Mat imgROI1 = frame_gray(Rect(Point(0, _height / 2), Point(_width, _height)));
	CHandCascade.detectMultiScale(imgROI1, car, 1.1, 2, CV_HAAR_DO_CANNY_PRUNING, Size(22, 22));
	//rectangle(frame, Point(0, 540), Point(1920, 1080/4*3), Scalar(0, 255, 255), 4, CV_AA);
	for (size_t i = 0; i<car.size(); i++)
	{
		if ((car[i].height > 80) && (car[i].width > 80))
		{
			/*	cout << car[i].height << " " << car[i].width << endl;*/
			rectangle(imgROI, car[i], Scalar(0, 0, 255),2);
		}
		else
		{
			continue;
		}


		//int ran_x, ran_y, ran_w, ran_h;
		//srand((unsigned)time(NULL));
		//ran_x = rand() % 1920;
		//ran_y = rand() % 1080;
		//ran_w = rand() % 150+150;
		//ran_h = rand() % 150+150;
		//rectangle(imgROI, Rect(ran_x, ran_y, ran_w, ran_h), Scalar(0, 0, 255), 2);


	}
	//imshow("【Dect】", frame);
	//-- Show what you got
	return frame;
}



Mat Sign(Mat srcImage)
{
	Mat ROI = srcImage(Rect(Point(srcImage.cols / 3, 0), Point(srcImage.cols, srcImage.rows / 2)));
	Mat HSVImage;
	Mat imageRGB[3];
	split(srcImage, imageRGB);
	for (int i = 0; i < 3; i++)
	{
		equalizeHist(imageRGB[i], imageRGB[i]);
	}
	merge(imageRGB, 3, srcImage);
	cvtColor(srcImage, HSVImage, COLOR_BGR2HSV);
	//imshow("【HSV】", HSVImage);
	Mat resultGray = Mat(HSVImage.rows, HSVImage.cols, CV_8U, cv::Scalar(0));
	//imshow("[2]", resultGray);
	Mat resultColor = Mat(HSVImage.rows, HSVImage.cols, CV_8UC3, cv::Scalar(255, 255, 255));
	double H = 0.0, S = 0.0, V = 0.0;
	int S_Min1 = 120,
		S_Max1 = 255,
		S_Min2 = 50,
		S_Max2 = 60,
		H_Min1 = 0,
		H_Min2 = 145,
		H_Max1 = 5,
		H_Max2 = 149,
		V_Min = 90,
		V_Max = 250;
	for (int i = 0; i < HSVImage.rows / 2; i++)
	{
		for (int j = HSVImage.cols / 3; j < HSVImage.cols; j++)
		{
			H = HSVImage.at<Vec3b>(i, j)[0];
			V = HSVImage.at<Vec3b>(i, j)[1];
			S = HSVImage.at<Vec3b>(i, j)[2];

			/*if (V==255)*/
			/*if ((S >= 70 && S<155) || (S >= 35 && S<65))*/
			/*if ((H >= H_Min1 && H <= H_Max1) || (H >= H_Min2 && H <= H_Max2))*/
			if ((H >= 170) || (H <= 10 && S >= 40 && V >= 30))
			{
				/*if ((H >= 0 && H < 24) && V >= 215)*/
				/*if ((S >= S_Min1 && S <= S_Max1) || (S >= S_Min2 && S <= S_Max2))*/
				{
					/*if (V >= V_Min && V <= V_Max)*/
					{
						resultGray.at<uchar>(i, j) = 255;
						resultColor.at<Vec3b>(i, j)[0] = srcImage.at<Vec3b>(i, j)[0];
						resultColor.at<Vec3b>(i, j)[1] = srcImage.at<Vec3b>(i, j)[1];
						resultColor.at<Vec3b>(i, j)[2] = srcImage.at<Vec3b>(i, j)[2];
					}
				}

			}
		}
	}
	//Mat after_inrange;
	//inRange(HSVImage, Scalar(0, 200, 0), Scalar(5, 254, 5), after_inrange);
	//imshow("【提取后】", resultGray);
	Mat Bin_img;
	threshold(resultGray, Bin_img, 0, 255, CV_THRESH_OTSU);
	//imshow("【二值化】", Bin_img);
	Mat Blured_img;
	GaussianBlur(Bin_img, Blured_img, Size(7, 7), 2, 2);
	//imshow("【滤波后】", Blured_img);
	Mat Morph_img;
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(5, 5), Point(2, 2));
	morphologyEx(Bin_img, Morph_img, CV_MOP_OPEN, element);
	//imshow("【开运算】", Morph_img);
	vector<Vec4i>hierarchy(10000);
	vector<Mat>contours(10000);//手动分配内存空间大小
	findContours(Morph_img, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point());
	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(Morph_img, contours, i, Scalar::all(255), CV_FILLED, 8);
	}
	//imshow("【绘制后】", Morph_img);
	Mat Split_img = Mat(8, 8, CV_8U, cv::Scalar(0));
	//imshow("[3]", Split_img);
	int rows_start, cols_start, N = 0;
	double R, Rt;
	R = 0.65;
	for (int n = 0; n < ROI.rows / 8; n++)
	{
		rows_start = n * 8;
		for (int m = 0; m < ROI.cols / 8; m++)
		{
			cols_start = m * 8 + srcImage.cols / 3;
			//cout << n+1 << "*" << m+1 << "times" << endl;
			Mat Morph_ROI = Morph_img(Rect(Point(cols_start, rows_start), Point(cols_start + Split_img.cols, rows_start + Split_img.rows)));
			for (int i = 0; i < Split_img.rows; i++)
			{
				for (int j = 0; j < Split_img.cols; j++)
				{
					Split_img.at<uchar>(i, j) = Morph_img.at<uchar>(i + rows_start, j + cols_start);
					Morph_img.at<uchar>(i + rows_start, j + cols_start) = 0;
					if (Split_img.at<uchar>(i, j) == 255)
					{
						N++;
						//cout << N << endl;
					}
				}
			}
			Rt = (double)N / (Split_img.rows * Split_img.cols);
			N = 0;
			if (Rt > R)
			{
				for (int i = 0; i < Split_img.rows; i++)
				{
					for (int j = 0; j < Split_img.cols; j++)
					{
						Morph_ROI.at<uchar>(i, j) = 255;
					}
				}
				/*rectangle(ROI, Point( m * Split_img.cols, n * Split_img.rows), Point( (m+1) * Split_img.cols, (n+1)* Split_img.rows), Scalar(0, 255, 255),2);*/
				//cout << 1 << endl;
			}
			//cout << Rt << endl;
		}
		//imwrite(file_name, Split_img);
	}
	int width = 0;
	int height = 0;
	int x = 0;
	int y = 0;
	findContours(Morph_img, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point());
	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(Mat(contours[i]));
		double area = contourArea(contours[i]);
		if (area > 500 && area < 3000)
		{
			/*RotatedRect rect = minAreaRect(contours[i]);*/
			//Point2f P[4];
			//rect.points(P);
			//for (int j = 0; j <= 3; j++)
			//{
			//	line(srcImage, P[j], P[(j + 1) % 4], Scalar(255), 2);
			//}
			boundRect[i] = boundingRect(Mat(contours[i]));
			width = boundRect[i].width;
			height = boundRect[i].height;
			x = boundRect[i].x;
			y = boundRect[i].y;
			//if ( (width/height >0.8) && (width/height < 1.2))
			//{
			rectangle(srcImage, Rect(x, y, width, height), Scalar(0, 255, 255), 3, 8);
			//}


		}
	}
	imshow("1", srcImage);


	return srcImage;
}