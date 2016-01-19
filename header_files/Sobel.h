#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include "LinearFilter.h"

#define X_AXIS 1
#define Y_AXIS 0

using namespace cv;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class SobelFilter : public LinearFilter
{
public:
	SobelFilter() : LinearFilter()
	{
		axis_ = X_AXIS;
		kernel_[0][0] = -1.;
		kernel_[0][1] = 0.;
		kernel_[0][2] = 1.;
		kernel_[1][0] = -2.;
		kernel_[1][1] = 0.;
		kernel_[1][2] = 2.;
		kernel_[2][0] = -1.;
		kernel_[2][1] = 0.;
		kernel_[2][2] = 1.;
	}
	SobelFilter(string input_path, bool mode) : LinearFilter(input_path, mode)
	{
		axis_ = 1;
		if (mode == NOT_SEPARABLE) {
			kernel_[0][0] = -1;
			kernel_[0][1] = 0;
			kernel_[0][2] = 1;
			kernel_[1][0] = -2;
			kernel_[1][1] = -0;
			kernel_[1][2] = 2;
			kernel_[2][0] = -1;
			kernel_[2][1] = 0;
			kernel_[2][2] = 1;
		}
		else {
			separable_kernel_x_[0] = -1.;
			separable_kernel_x_[1] = 0.;
			separable_kernel_x_[2] = 1.;
			separable_kernel_y_[0] = 1.;
			separable_kernel_y_[1] = 2.;
			separable_kernel_y_[2] = 1.;
		}
	}
	SobelFilter(bool axis) : LinearFilter()
	{
		axis_ = axis;
		if (axis == X_AXIS) {
			kernel_[0][0] = -1;
			kernel_[0][1] = 0;
			kernel_[0][2] = 1;
			kernel_[1][0] = -2;
			kernel_[1][1] = -0;
			kernel_[1][2] = 2;
			kernel_[2][0] = -1;
			kernel_[2][1] = 0;
			kernel_[2][2] = 1;
		}
		else {
			kernel_[0][0] = -1;
			kernel_[0][1] = -2;
			kernel_[0][2] = -1;
			kernel_[1][0] = 0;
			kernel_[1][1] = 0;
			kernel_[1][2] = 0;
			kernel_[2][0] = 1;
			kernel_[2][1] = 2;
			kernel_[2][2] = 1;
		}
	}
	SobelFilter(string input_path, bool axis, bool mode) : LinearFilter(input_path, mode)
	{
		axis_ = axis;
		if (mode == NOT_SEPARABLE) {
			if (axis == X_AXIS) {
				kernel_[0][0] = -1;
				kernel_[0][1] = 0;
				kernel_[0][2] = 1;
				kernel_[1][0] = -2;
				kernel_[1][1] = -0;
				kernel_[1][2] = 2;
				kernel_[2][0] = -1;
				kernel_[2][1] = 0;
				kernel_[2][2] = 1;
			}
			else {
				kernel_[0][0] = -1;
				kernel_[0][1] = -2;
				kernel_[0][2] = -1;
				kernel_[1][0] = 0;
				kernel_[1][1] = 0;
				kernel_[1][2] = 0;
				kernel_[2][0] = 1;
				kernel_[2][1] = 2;
				kernel_[2][2] = 1;
			}
		}
		else {
			if (axis == X_AXIS) {
				separable_kernel_x_[0] = -1.;
				separable_kernel_x_[1] = 0.;
				separable_kernel_x_[2] = 1.;
				separable_kernel_y_[0] = -1.;
				separable_kernel_y_[1] = -2.;
				separable_kernel_y_[2] = -1.;
			}
			else {
				separable_kernel_x_[0] = -1.;
				separable_kernel_x_[1] = -2.;
				separable_kernel_x_[2] = -1.;
				separable_kernel_y_[0] = -1.;
				separable_kernel_y_[1] = 0.;
				separable_kernel_y_[2] = 1.;
			}
		}
	}
	double Formula(int x, int y);
	double SeparableFormula(int x);
	void NoBoarderConvolution();
	void SeparableConvolution();
private:
	bool axis_;
};
