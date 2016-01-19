#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include "LinearFilter.h"

using namespace cv;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class BoxFilter : public LinearFilter
{
public:
	BoxFilter() : LinearFilter() 
	{
		GenerateKernel();
	}
	BoxFilter(string input_path, bool mode) : LinearFilter(input_path, mode) 
	{
		GenerateKernel();
	}
	BoxFilter(int radius, bool mode) : LinearFilter(radius, mode)
	{
		GenerateKernel();
	}
	BoxFilter(string input_path, int radius, bool mode) : LinearFilter(input_path, radius, mode)
	{
		GenerateKernel();
	}
	~BoxFilter() {};
	double Formula(int x, int y);
	double SeparableFormula(int x);
};