#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include "ImageFilter.h"

#define SEPARABLE true
#define NOT_SEPARABLE false

using namespace cv;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class LinearFilter : public ImageFilter
{
public:
	LinearFilter() : ImageFilter()
	{
		radius_ = 3;
		kernel_ = new double*[radius_];
		for (int i = 0; i < radius_; ++i)
			kernel_[i] = new double[radius_];
	}
	LinearFilter(string input_path, bool mode) : ImageFilter(input_path)
	{
		radius_ = 3;
		mode_ = mode;
		if (!mode) {
			kernel_ = new double*[radius_];
			for (int i = 0; i < radius_; ++i)
				kernel_[i] = new double[radius_];
		}
		else {
			separable_kernel_x_ = new double[radius_];
			separable_kernel_y_ = new double[radius_];
		}
	}
	LinearFilter(int radius, bool mode) : ImageFilter()
	{
		radius_ = radius - (radius % 2) + 1;
		mode_ = mode;
		if (mode == NOT_SEPARABLE) {
			kernel_ = new double*[radius_];
			for (int i = 0; i < radius_; ++i)
				kernel_[i] = new double[radius_];
		}
		else {
			separable_kernel_x_ = new double[radius_];
			separable_kernel_y_ = new double[radius_];
		}
	}
	LinearFilter(string input_path, int radius, bool mode) : ImageFilter(input_path)
	{
		radius_ = radius + !(radius % 2);
		mode_ = mode;
		if (mode == NOT_SEPARABLE) {
			kernel_ = new double*[radius_];
			for (int i = 0; i < radius_; ++i)
				kernel_[i] = new double[radius_];
		}
		else {
			separable_kernel_x_ = new double[radius_];
			separable_kernel_y_ = new double[radius_];
		}
	}

	virtual ~LinearFilter() {};
	virtual void set_kernel_radius(int radius);
	virtual void set_mode(bool mode);
	virtual void NoBoarderConvolution();
	void ReflectedIndexingConvolution();
	void CircularIndexingConvolution();
	virtual void SeparableKernelConvolution();
	virtual void Normalize(double sum);
	virtual double Formula(int x, int y) = 0;
	virtual double SeparableFormula(int x) = 0;
	virtual void GenerateKernel();
	virtual void GenerateSeparableKernel();
	virtual void Convolve();
	virtual void GenerateCorrectKernel();
	virtual void Invoke();
	int Reflect(int M, int x);
	int Circular(int M, int x);
protected:
	int radius_;
	double **kernel_;
	double *separable_kernel_x_;
	double *separable_kernel_y_;
	bool mode_;
};
