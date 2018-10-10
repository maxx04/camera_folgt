#pragma once

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

using namespace std;
using namespace cv;

struct point_satz
{
	int n;
	float v;
};

class histogram
{
private:
	Mat plotResult;
	int window_width;
	int windows_high;
	int windows_h_offset; //base Histogramm


public:
	int dims;
	float range_max;
	float range_min;
	int bins;
	vector<point_satz> values;
	vector<int> bins_counters;
	vector<float> bins_borders;
	vector<point_satz>* bins_group; //punkt nummer in bin
	int values_index;

	histogram();
	histogram(int bins, int dims = 1);
	~histogram();

	void plot_result(Point p);
	
	int collect(point_satz v);
	int sort();
	double get_background_move_direction();
	void clear();


};

