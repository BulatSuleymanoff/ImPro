#include "ImageProcessor.h"

void ImageProcessor::read_image()
{
	original_image_ = imread(input_path_, CV_LOAD_IMAGE_GRAYSCALE);
}

void ImageProcessor::set_input_path(string input_path)
{
	input_path_ = input_path;
	read_image();
}

string ImageProcessor::get_input_path()
{
	return input_path_;
}

void ImageProcessor::set_output_path(string output_path)
{
	output_path_ = output_path;
}

string ImageProcessor::get_output_path()
{
	return output_path_;
}

void ImageProcessor::set_names(string image_name)
{
	image_name_ = image_name;
}

string ImageProcessor::get_name(unsigned int version = 0)
{
	if (version == 1)
		return image_name_ + "_processed";
	return image_name_;
}

void ImageProcessor::Add(Mat add_mat)
{
	double temp;
	Mat src = original_image_;
	Mat dst = processed_image_;
	for (int i = 0; i < src.rows; ++i)
		for (int j = 0; j < src.cols; ++j) {
			temp = src.at<uchar>(i, j) + add_mat.at<uchar>(i, j);
			temp = (temp > 255) ? 255 : temp;
			
			dst.at<uchar>(i, j) = temp;
		}
	SaveProcessedImage();
}

void ImageProcessor::Add()
{
	double temp;
	Mat src = original_image_;
	Mat dst = processed_image_;
	for (int i = 0; i < src.rows; ++i)
		for (int j = 0; j < src.cols; ++j) {
			temp = src.at<uchar>(i, j) + dst.at<uchar>(i, j);
			temp = (temp > 255) ? 255 : temp;

			dst.at<uchar>(i, j) = temp;
		}
	SaveProcessedImage();
}

void ImageProcessor::Subtract(const Mat sub_mat)
{
	double temp;
	Mat src = original_image_;
	Mat dst = processed_image_;
	for (int i = 0; i < src.rows; ++i)
		for (int j = 0; j < src.cols; ++j) {
			temp = src.at<uchar>(i, j) - sub_mat.at<uchar>(i, j);
			temp = (temp < 0) ? 0 : temp;
			dst.at<uchar>(i, j) = temp;
		}
	SaveProcessedImage();
}

void ImageProcessor::Subtract()
{
	double temp;
	Mat src = original_image_;
	Mat dst = processed_image_;
	for (int i = 0; i < src.rows; ++i)
		for (int j = 0; j < src.cols; ++j) {
			temp = src.at<uchar>(i, j) - dst.at<uchar>(i, j);
			temp = (temp < 0) ? 0 : temp;
			dst.at<uchar>(i, j) = temp;
		}
	SaveProcessedImage();
}

void ImageProcessor::SaveProcessedImage()
{
	imwrite(output_path_, processed_image_);
}

void ImageProcessor::Display(bool v)
{
	//resize(original_image_, original_image_, Size(original_image_.cols, original_image_.rows));
	//resize(processed_image_, processed_image_, Size(processed_image_.cols, processed_image_.rows));
	if (v == 0) {
		namedWindow(get_name(), WINDOW_AUTOSIZE);
		imshow(get_name(), original_image_);
	}
	else {
		namedWindow(get_name(), WINDOW_AUTOSIZE);
		namedWindow(get_name(1), WINDOW_AUTOSIZE);

		imshow(get_name(), original_image_);
		imshow(get_name(1), processed_image_);
	}
	waitKey(0);
}

int ImageProcessor::get_size()
{
	return original_image_.cols * original_image_.rows;
}