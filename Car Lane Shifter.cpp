//
//  main.cpp
//  finalVisionProject
//
//  Created by Mai Abdul-Maqsoud on 12/7/16.
//  Copyright © 2016 Mai. All rights reserved.
//
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>
#include <iostream>
#include <iostream>
#include<opencv2/opencv.hpp>
#include<fstream>
#include <cmath>

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>
#include <iostream>
using namespace cv;
using namespace std;


CascadeClassifier face_cascade;
Mat blackAndWhiteImage, gray, halfFrame, canny, equalized, roadLines, frame;


void mouseHandler(int event, int x, int y, int flags, void* param) {
	if (event == CV_EVENT_LBUTTONDOWN) {
		cout << x << " " << y << "\n";
	}
}
/**
ROIPoint obj;
setMouseCallback("lines", obj.mouseHandler, &p);

cout << p << endl;
**/

//-------------------------------------------------------------------------------------
Point p1(114, 179), p2(257, 83), p3(576, 179), p4(406, 83);

void detectAndDisplay(Mat frame) {
	std::vector<Rect> cars;
	Mat frame_gray;
	vector<Point> p;
	p.push_back(p3);
	p.push_back(p4);
	p.push_back(p2);
	p.push_back(p1);

	fillConvexPoly(frame, &p[0], 4, Scalar(0, 255, 0));

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	bool result = false;

	face_cascade.detectMultiScale(frame_gray, cars, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (int i = 0; i < cars.size(); i++) {
		Point center(cars[i].x + cars[i].width*0.5, cars[i].y + cars[i].height*0.5);
		int radius = 20;


		//ellipse(frame, center, Size(cars[i].width*0.5, cars[i].height*0.5), 0, 0, 360, Scalar(0, 0, 0), 4, 8, 0);
		if ((center.x <= 431) && (center.x >= 87))
		{
			circle(frame, center, radius, Scalar(0, 0, 0), 1, 8, 0);
			if (radius + cars[i].y + cars[i].height*0.5 >= 70)
			{
				result = true;
			}
		}

		Mat carROI = frame_gray(cars[i]);
		CvRect r(cars[i]);

		if (result) {
			fillConvexPoly(frame, &p[0], 4, Scalar(0, 0, 255));
			result = false;
		}


	}
	//-- Show what you got

	imshow("detect the cars please!!!", frame);
}

//-------------------------------------------------------------------------------------

int main(int argc, const char * argv[]) {
	VideoCapture cap("roadsMod3.mp4");
	Mat smallImg;
	namedWindow("detect the cars please!!!", 1);
	setMouseCallback("detect the cars please!!!", mouseHandler);

	if (!cap.isOpened()) {
		cout << "Could not open the Source  video for Read" << endl;
		return -1;
	}

	CascadeClassifier cascade;
	if (!face_cascade.load("haarcascade_cars3.xml")) {
		printf("--(!)Error loading\n"); return -1;
	}

	imshow("frame", cap.read(frame));

	while (cap.read(frame)) {
		cap >> frame;
		Mat roads(cap.get(CV_CAP_PROP_FRAME_HEIGHT), cap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC1, Scalar(0));
		Mat colouredHalfFrame = frame(Rect(0, frame.rows / 2, frame.cols, frame.rows / 2));

		Mat cdst = colouredHalfFrame.clone();
		cvtColor(frame, gray, CV_BGR2GRAY);
		equalizeHist(gray, equalized);
		GaussianBlur(equalized, gray, Size(5, 5), 0);
		threshold(gray, blackAndWhiteImage, 127, 255, THRESH_BINARY);

		//we only need the bottom half
		//halfFrame = blackAndWhiteImage(Rect(0, blackAndWhiteImage.rows/2, blackAndWhiteImage.cols, blackAndWhiteImage.rows/2));


		line(colouredHalfFrame, Point(114, 179), Point(257, 83), Scalar(0, 255, 0)); //far left
		line(colouredHalfFrame, Point(576, 179), Point(406, 83), Scalar(0, 255, 0)); //far right
		line(colouredHalfFrame, Point(257, 83), Point(406, 83), Scalar(0, 255, 0));


		detectAndDisplay(colouredHalfFrame);
		waitKey(10);
	}

	return 0;
}
