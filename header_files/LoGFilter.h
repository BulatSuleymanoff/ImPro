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

class LoGFilter : public LinearFilter
{
public:
	LoGFilter() : LinearFilter()
	{
		sigma_ = 0.5;
		kernel_[0][0] = 0;
		kernel_[0][1] = -1.;
		kernel_[0][2] = 0.;
		kernel_[1][0] = -1.;
		kernel_[1][1] = 5.;
		kernel_[1][2] = -1.;
		kernel_[2][0] = 0;
		kernel_[2][1] = -1.;
		kernel_[2][2] = 0;
	}
	LoGFilter(string input_path, bool mode) : LinearFilter(input_path, mode)
	{
		sigma_ = 0.5;
		if (!mode) {
			kernel_[0][0] = 0;
			kernel_[0][1] = -1.;
			kernel_[0][2] = 0.;
			kernel_[1][0] = -1.;
			kernel_[1][1] = 5.;
			kernel_[1][2] = -1.;
			kernel_[2][0] = 0;
			kernel_[2][1] = -1.;
			kernel_[2][2] = 0;
		}
		else {
			separable_kernel_x_[0] = 1.;
			separable_kernel_x_[1] = -2.;
			separable_kernel_x_[2] = 1.;
			separable_kernel_y_[0] = 1.;
			separable_kernel_y_[1] = -2.;
			separable_kernel_y_[2] = 1.;
		}
	}
	LoGFilter(int radius, bool mode) : LinearFilter(radius, mode)
	{
		sigma_ = radius / 5.;
		if (mode == NOT_SEPARABLE)
			GenerateKernel();
		else GenerateSeparableKernel();
	}
	LoGFilter(int radius, double sigma, bool mode) : LinearFilter(radius, mode)
	{
		sigma_ = sigma;
		if (mode == NOT_SEPARABLE)
			GenerateKernel();
		else GenerateSeparableKernel();
	}
	LoGFilter(string input_path, int radius, bool mode) : LinearFilter(input_path, radius, mode)
	{
		sigma_ = radius / 5.;
		if (mode == NOT_SEPARABLE)
			GenerateKernel();
		else GenerateSeparableKernel();
	}
	~LoGFilter() {};
	double Formula(int x, int y);
	double SeparableFormula(int x);
private:
	double sigma_;

};