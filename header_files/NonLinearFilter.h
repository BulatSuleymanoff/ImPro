#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include "ImageFilter.h"

using namespace cv;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class NonLinearFilter : public ImageProcessor
{
public:
	NonLinearFilter() : ImageProcessor() 
	{
		radius_ = 3;
	}
	NonLinearFilter(string input_path) : ImageProcessor(input_path) 
	{
		radius_ = 3;
	}
	NonLinearFilter(int radius) : ImageProcessor() 
	{
		radius_ = radius;
	}
	NonLinearFilter(string input_path, int radius) : ImageProcessor(input_path) 
	{
		radius_ = radius;
	}
	virtual ~NonLinearFilter() {};
	virtual void Invoke() = 0;
protected:
	int radius_;
};