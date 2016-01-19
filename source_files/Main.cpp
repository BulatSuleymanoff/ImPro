#include "GaussianFilter.h"
#include "BoxFilter.h"
#include "Sobel.h"
#include "Histogram.h"
#include "Prewitt.h"
#include "MedianFilter.h"
#include "MinFilter.h"
#include "MaxFilter.h"
#include "LoGFilter.h"
#include <string>
#include <direct.h>
//#include <windows.h> //create directory using CreateDirectory() 
#include <cstring> //convert std::string to null terminated string

using namespace std;
using namespace cv;


void ViewSmoothing()
{
	const int SIZE = 10;
	string original_path("../Assets/demo");
	_mkdir("../Assets/ViewSmoothing");
	string save_path("../Assets/ViewSmoothing/demo");
	string new_output = original_path + string(".jpg");
	Mat original_img = imread(new_output, CV_LOAD_IMAGE_GRAYSCALE);
	Mat image_array[SIZE];

	GaussianFilter box(new_output, 0);
	//MedianFilter box(new_output);
	//MinFilter box(new_output);
	//MaxFilter box(new_output);
	box.set_output_path(save_path + string(".jpg"));
	box.SaveProcessedImage();

	for (int i = 0; i < SIZE; ++i) {
		box.set_input_path(new_output);
		new_output = save_path + to_string(i) + string(".jpg");
		box.set_output_path(new_output);
		//box.NoBoarderConvolution();
		//box.SeparableKernelConvolution();
		box.Invoke();
		box.SaveProcessedImage();
		image_array[i] = imread(new_output, CV_LOAD_IMAGE_GRAYSCALE);
	}

	system("PAUSE");

	for (int i = 0; i < SIZE; ++i) {
		namedWindow("BLURRED IMAGE", WINDOW_AUTOSIZE);
		imshow("BLURRED IMAGE", image_array[i]);

		waitKey(700);
	}
}

void ViewSmoothingEdges()
{
	

	const int SIZE = 10;
	string original_path("../Assets/demo");
	_mkdir("../Assets/ViewSmoothingEdges");
	string save_path("../Assets/ViewSmoothingEdges/demo");
	string new_output = original_path + string(".jpg");
	Mat original_img = imread(new_output, CV_LOAD_IMAGE_GRAYSCALE);
	Mat blur_image_array[SIZE];
	Mat edges_image_array[SIZE];

	GaussianFilter box(new_output, 5, 0);
	//GaussianFilter box(new_output, 5, 1);
	//GaussianFilter box(new_output, 0);
	new_output = save_path + string(".jpg");
	box.set_output_path(new_output);
	box.SaveProcessedImage();

	box.set_input_path(new_output);

	for (int i = 0; i < SIZE; ++i) {
		box.set_input_path(new_output);

		new_output = save_path + to_string(i) + string(".jpg");
		box.set_output_path(new_output);
		box.NoBoarderConvolution();
		box.SaveProcessedImage();
		//box.SeparableKernelConvolution();
		blur_image_array[i] = imread(new_output, CV_LOAD_IMAGE_GRAYSCALE);

		new_output = save_path + "_edges" + to_string(i) + string(".jpg");
		box.set_output_path(new_output);
		box.set_input_path(original_path + string(".jpg"));
		box.Subtract();
		edges_image_array[i] = imread(new_output, CV_LOAD_IMAGE_GRAYSCALE);

		new_output = save_path + to_string(i) + string(".jpg");
	}

	system("PAUSE");

	for (int i = 0; i < SIZE; ++i) {
		namedWindow("BLURRED IMAGE", WINDOW_AUTOSIZE);
		imshow("BLURRED IMAGE", blur_image_array[i]);

		namedWindow("EDGES IMAGE", WINDOW_AUTOSIZE);
		imshow("EDGES IMAGE", edges_image_array[i]);

		waitKey(700);
	}
}

void ViewSmoothingSharpenEdges()
{
	const int SIZE = 10;
	string original_path("../Assets/demo");
	_mkdir("../Assets/ViewSmoothingSharpenEdges");
	string save_path("../Assets/ViewSmoothingSharpenEdges/demo");
	string new_output = original_path + string(".jpg");
	Mat original_img = imread(new_output, CV_LOAD_IMAGE_GRAYSCALE);
	Mat blur_image_array[SIZE];
	Mat edges_image_array[SIZE];
	Mat sharpen_image_array[SIZE];

	//GaussianFilter box(new_output, 5, 0);
	GaussianFilter box(new_output, 5, 1);
	//GaussianFilter box(new_output, 1);
	new_output = save_path + string(".jpg");
	box.set_output_path(new_output);
	box.SaveProcessedImage();

	box.set_input_path(new_output);

	for (int i = 0; i < SIZE; ++i) {
		box.set_input_path(new_output);

		new_output = save_path + to_string(i) + string(".jpg");
		box.set_output_path(new_output);
		//box.NoBoarderConvolution();
		box.SeparableKernelConvolution();
		box.SaveProcessedImage();
		blur_image_array[i] = imread(new_output, CV_LOAD_IMAGE_GRAYSCALE);

		new_output = save_path + "_edges" + to_string(i) + string(".jpg");
		box.set_output_path(new_output);
		box.set_input_path(original_path + string(".jpg"));
		box.Subtract();
		box.SaveProcessedImage();
		edges_image_array[i] = imread(new_output, CV_LOAD_IMAGE_GRAYSCALE);

		new_output = save_path + "_sharpen" + to_string(i) + string(".jpg");
		box.set_output_path(new_output);
		box.set_input_path(original_path + string(".jpg"));
		box.Add();
		box.SaveProcessedImage();
		sharpen_image_array[i] = imread(new_output, CV_LOAD_IMAGE_GRAYSCALE);

		new_output = save_path + to_string(i) + string(".jpg");
	}

	system("PAUSE");

	for (int i = 0; i < SIZE; ++i) {
		namedWindow("BLURRED IMAGE", WINDOW_AUTOSIZE);
		imshow("BLURRED IMAGE", blur_image_array[i]);

		namedWindow("EDGES IMAGE", WINDOW_AUTOSIZE);
		imshow("EDGES IMAGE", edges_image_array[i]);

		namedWindow("SHARPEN IMAGE", WINDOW_AUTOSIZE);
		imshow("SHARPEN IMAGE", sharpen_image_array[i]);

		waitKey(1200);
	}
}

int main()
{
	ViewSmoothing();
	destroyAllWindows();
	ViewSmoothingEdges();
	destroyAllWindows();
	ViewSmoothingSharpenEdges();
	LoGFilter sharpen_filter;
	sharpen_filter.Invoke();
	sharpen_filter.SaveProcessedImage();
	SobelFilter sobel;
	sobel.Invoke();
	sobel.set_output_path("../Assets/demo_sobel.jpg");
	sobel.SaveProcessedImage();
	PrewittFilter prewitt;
	prewitt.Invoke();
	prewitt.set_output_path("../Assets/demo_prewitt.jpg");
	prewitt.SaveProcessedImage();
	
	
	return 0;
}