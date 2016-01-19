#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include "NonLinearFilter.h"

using namespace cv;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class MaxFilter : public NonLinearFilter
{
public:
	MaxFilter() : NonLinearFilter()
	{
		window_ = new int[radius_ * radius_];
	}
	MaxFilter(string input_path) : NonLinearFilter(input_path)
	{
		window_ = new int[radius_ * radius_];
	}
	MaxFilter(int radius) : NonLinearFilter(radius)
	{
		window_ = new int[radius_ * radius_];
	}
	MaxFilter(string input_path, int radius) : NonLinearFilter(input_path, radius)
	{
		window_ = new int[radius_ * radius_];
	}
	int Max();
	void Invoke();
private:
	int *window_;
};
