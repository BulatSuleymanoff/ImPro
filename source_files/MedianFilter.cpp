#include "MedianFilter.h"

void MedianFilter::Invoke()
{
	Mat src = original_image_;
	Mat dst = processed_image_;

	for (int y = radius_ / 2; y < src.rows - radius_ / 2; y++) {
		for (int x = radius_ / 2; x < src.cols - radius_ / 2; x++) {
			for (int i = 0; i < radius_; ++i)
				for (int j = 0; j < radius_; ++j)
					window_[i * radius_ + j] = src.at<uchar>(y + j - radius_ / 2, x + i - radius_ / 2);
			std::sort(window_, window_ + radius_ * radius_);
			dst.at<uchar>(y, x) = window_[radius_ * radius_ / 2];
		}
	}
}