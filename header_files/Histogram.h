#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include "ImageProcessor.h"

using namespace cv;
using std::string;
using std::cout;
using std::cin;
using std::endl;

	class Histogram : public ImageProcessor
	{
	public:
		Histogram() : ImageProcessor() {}
		Histogram(string input_path) : ImageProcessor(input_path){}
		int* get_histogram();
		int* get_final();
		void Invoke();
		void CalculateHistogram();
		void DisplayHistogram(int *hist, bool v = 0);
		int* Equalize();
		void Normalize(float factor);
	private:
		int histogram_[256];
		int final_[256];
	};