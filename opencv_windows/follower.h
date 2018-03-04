#pragma once
#pragma warning(disable : 4996)

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <string.h>

using namespace cv;
using namespace std;

class follower
{

	TermCriteria termcrit;
	Size subPixWinSize, winSize;
	const int MAX_COUNT = 500;
	bool needToInit = false;
	bool nightMode = false;

	Mat gray, prevGray, image;

	Mat Affine;

	vector<Point2f> points[2];
	vector<Point2f> calc[2];

public:
	follower();
	~follower();
	void init_points();
	void take_picture(Mat* frame);
	void calcOptFlow();
	void transform_Affine();
	void draw();
	void show();
	void swap();
	bool key();

};

