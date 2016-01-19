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


class ImageFilter: public ImageProcessor
{
public:
	ImageFilter() : ImageProcessor() {}
	ImageFilter(string input_path) : ImageProcessor(input_path) {}
	virtual ~ImageFilter() {};
protected:
	virtual void Invoke() {};
};
