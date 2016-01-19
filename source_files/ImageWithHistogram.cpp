#include "Header.h"
using namespace cvl;

void ImageWithHistogram::set_histogram()
{
	for (int i = 0; i < 256; i++){
		histogram_[i] = 0;
	}
	for (int y = 0; y < image_.get_image().rows; y++)
		for (int x = 0; x < image_.get_image().cols; x++)
			histogram_[(int)image_.get_image().at<uchar>(y, x)]++;
}

int* ImageWithHistogram::get_histogram()
{
	return histogram_;
}

void ImageWithHistogram::DisplayHist()
{
	int hist[256];
	for (int i = 0; i < 256; i++)
	{
		hist[i] = histogram_[i];
	}
	// draw the histograms
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat hist_image(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

	// find the maximum intensity element from histogram
	int max = hist[0];
	for (int i = 1; i < 256; i++){
		if (max < hist[i]){
			max = hist[i];
		}
	}

	// normalize the histogram between 0 and histImage.rows

	for (int i = 0; i < 256; i++){
		hist[i] = ((double)hist[i] / max)*hist_image.rows;
	}


	// draw the intensity line for histogram
	for (int i = 0; i < 256; i++)
	{
		line(hist_image, Point(bin_w*(i), hist_h),
			Point(bin_w*(i), hist_h - hist[i]),
			Scalar(0, 0, 0), 1, 8, 0);
	}

	// display histogram
	namedWindow(image_.get_name(), CV_WINDOW_AUTOSIZE);
	imshow(image_.get_name(), hist_image);
}

void 