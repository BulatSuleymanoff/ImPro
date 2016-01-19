#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>


using namespace cv;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class ImageProcessor
{
public:
	ImageProcessor() {
		input_path_ = "../Assets/demo.jpg";
		output_path_ = "../Assets/demo_processed.jpg";
		image_name_ = "demo";
		original_image_ = imread(input_path_, CV_LOAD_IMAGE_GRAYSCALE);
		processed_image_ = original_image_.clone();
	}
	ImageProcessor(string input_path) { 
		input_path_ = input_path;
		output_path_ = input_path.erase(input_path.size() - 4, 4) + "_processed.jpg";
		image_name_ = input_path.substr(input_path.find_last_of("/") + 1);
		original_image_ = imread(input_path_, CV_LOAD_IMAGE_GRAYSCALE);
		processed_image_ = original_image_.clone();
	}
	virtual ~ImageProcessor(){}
	void read_image();
	void set_input_path(string input_path);
	string get_input_path();
	void set_output_path(string output_path);
	string get_output_path();
	void set_names(string image_name);
	string get_name(unsigned int version);
	void Add(Mat add_mat);
	void Add();
	void Subtract(Mat add_mat);
	void Subtract();
	virtual void SaveProcessedImage();
	virtual void Display(bool v = 0);
	virtual void Invoke() = 0;
	int get_size();
protected:
	Mat original_image_;
	Mat processed_image_;
	//Mat src_;
	//Mat dst_;
	string input_path_;
	string output_path_;
	string image_name_;
};
