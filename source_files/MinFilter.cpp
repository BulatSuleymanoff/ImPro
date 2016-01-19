#include "MinFilter.h"

int MinFilter::Min()
{
	int min = 255;
	for (int i = 0; i < radius_ * radius_; ++i)
		if (min > window_[i])
			min = window_[i];
	return min;
}

void MinFilter::Invoke()
{
	Mat src = original_image_;
	Mat dst = processed_image_;

	for (int y = radius_ / 2; y < src.rows - radius_ / 2; y++) {
		for (int x = radius_ / 2; x < src.cols - radius_ / 2; x++) {
			for (int i = 0; i < radius_; ++i)
				for (int j = 0; j < radius_; ++j)
					window_[i * radius_ + j] = src.at<uchar>(y + j - radius_ / 2, x + i - radius_ / 2);
			dst.at<uchar>(y, x) = Min();
		}
	}
}