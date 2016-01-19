#include "Histogram.h"

int *Histogram::get_histogram()
{
	return histogram_;
}

int *Histogram::get_final()
{
	return final_;
}

void Histogram::Invoke()
{
	Equalize();
	Display(1);
	DisplayHistogram(histogram_);
	DisplayHistogram(final_, 1);
}

void Histogram::CalculateHistogram()
{
	// initialize all intensity values to 0
	for (int i = 0; i < 256; i++)
	{
		histogram_[i] = 0;
	}

	// calculate the # of pixels for each intensity values
	for (int y = 0; y < original_image_.rows; y++)
		for (int x = 0; x < original_image_.cols; x++)
			histogram_[(int)original_image_.at<uchar>(y, x)]++;
}

void Histogram::DisplayHistogram(int *hist, bool v)
{
	/*int hist[256];
	for (int i = 0; i < 256; i++)
	{
		hist[i] = histogram_[i];
	}*/
	// draw the histograms
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

	// find the maximum intensity element from histogram
	int max = hist[0];
	for (int i = 1; i < 256; i++){
		if (max < hist[i]){
			max = hist[i];
		}
	}

	// normalize the histogram between 0 and histImage.rows

	for (int i = 0; i < 256; i++){
		hist[i] = ((double)hist[i] / max)*histImage.rows;
	}


	// draw the intensity line for histogram
	for (int i = 0; i < 256; i++)
	{
		line(histImage, Point(bin_w*(i), hist_h),
			Point(bin_w*(i), hist_h - hist[i]),
			Scalar(0, 0, 0), 1, 8, 0);
	}

	// display histogram
	namedWindow(get_name(v) + " hist", CV_WINDOW_AUTOSIZE);
	imshow(get_name(v) + " hist", histImage);
	waitKey(0);
}

void Histogram::Normalize(float factor)
{
	int size = original_image_.rows * original_image_.cols;
	float alpha = factor / size;
	for (int i = 0; i < 256; i++)
	{
		histogram_[i] = cvRound((double)histogram_[i] / alpha);
	}
}

int* Histogram::Equalize()
{
	CalculateHistogram();

	// Caluculate the size of image
	int size = original_image_.rows * original_image_.cols;
	float alpha = 255.0 / size;

	// Calculate the probability of each intensity
	float probability[256];
	for (int i = 0; i < 256; i++)
	{
		probability[i] = (float)histogram_[i] / size;
	}

	// Generate cumulative frequency histogram
	int cumulative_histogram[256];
	cumulative_histogram[0] = histogram_[0];

	for (int i = 1; i < 256; i++)
	{
		cumulative_histogram[i] = histogram_[i] + cumulative_histogram[i - 1];
	}

	// Scale the histogram
	int scaled_histogram[256];
	for (int i = 0; i < 256; i++)
	{
		scaled_histogram[i] = cvRound((double)cumulative_histogram[i] * alpha);
	}


	// Generate the equlized histogram
	float equalized_histogram[256] = {0};

	for (int i = 0; i < 256; i++)
	{
		equalized_histogram[scaled_histogram[i]] += probability[i];
	}

	for (int i = 0; i < 256; i++)
		final_[i] = cvRound(equalized_histogram[i] * 255);


	// Generate the equlized image
	processed_image_ = original_image_.clone();
	for (int y = 0; y < original_image_.rows; y++)
		for (int x = 0; x < original_image_.cols; x++)
			processed_image_.at<uchar>(y, x) = saturate_cast<uchar>(scaled_histogram[original_image_.at<uchar>(y, x)]);

	return final_;
}


