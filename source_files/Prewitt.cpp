#include "Prewitt.h"

double PrewittFilter::Formula(int x, int y)
{
	return 0;
}

double PrewittFilter::SeparableFormula(int x)
{
	return 0;
}

void PrewittFilter::NoBoarderConvolution()
{
	int gx, gy, sum;
	for (int y = radius_ / 2; y < original_image_.rows - radius_ / 2; y++) {
		for (int x = radius_ / 2; x < original_image_.cols - radius_ / 2; x++) {
			gx = 0;
			gy = 0;
			/*for (int i = -radius_ / 2; i <= radius_ / 2; ++i) {
			for (int j = -radius_ / 2; j <= radius_ / 2; ++j) {
			gx += kernel_[j + radius_ / 2][i + radius_ / 2] * original_image_.at<uchar>(y - j, x - i);
			//gy += kernel_[j + radius_ / 2][i + radius_ / 2] * original_image_.at<uchar>(y - i, x - j);
			}
			}
			for (int i = -radius_ / 2; i <= radius_ / 2; ++i) {
			for (int j = -radius_ / 2; j <= radius_ / 2; ++j) {
			//gx += kernel_[j + radius_ / 2][i + radius_ / 2] * original_image_.at<uchar>(y - j, x - i);
			gy += kernel_[j + radius_ / 2][i + radius_ / 2] * original_image_.at<uchar>(y - i, x - j);
			}
			}*/
			for (int i = -radius_ / 2; i <= radius_ / 2; ++i) {
				for (int j = -radius_ / 2; j <= radius_ / 2; ++j) {
					gx += kernel_[j + radius_ / 2][i + radius_ / 2] * original_image_.at<uchar>(y - j, x - i);
					gy += kernel_[j + radius_ / 2][i + radius_ / 2] * original_image_.at<uchar>(y - i, x - j);
				}
			}
			gy = original_image_.at<uchar>(y - 1, x - 1) +
				2 * original_image_.at<uchar>(y - 1, x) +
				original_image_.at<uchar>(y - 1, x + 1) -
				original_image_.at<uchar>(y + 1, x - 1) -
				2 * original_image_.at<uchar>(y + 1, x) -
				original_image_.at<uchar>(y + 1, x + 1);
			gx = original_image_.at<uchar>(y - 1, x - 1) +
				2 * original_image_.at<uchar>(y, x - 1) +
				original_image_.at<uchar>(y + 1, x - 1) -
				original_image_.at<uchar>(y - 1, x + 1) -
				2 * original_image_.at<uchar>(y, x + 1) -
				original_image_.at<uchar>(y + 1, x + 1);
			gx = (gx < 0) ? -gx : gx;
			gy = (gy < 0) ? -gy : gy;
			sum = gx + gy;
			sum = sum > 255 ? 255 : sum;
			sum = sum < 0 ? 0 : sum;
			processed_image_.at<uchar>(y, x) = sum;
		}
	}
	SaveProcessedImage();
}

void PrewittFilter::SeparableConvolution()
{
	int gx, gy, sum, y1, x1;
	Mat temp = original_image_.clone();
	for (int y = radius_ / 2; y < original_image_.rows - radius_ / 2; y++) {
		for (int x = radius_ / 2; x < original_image_.cols - radius_ / 2; x++) {
			gx = 0;
			gy = 0;
			sum = 0.0;
			for (int i = -radius_ / 2; i <= radius_ / 2; ++i) {
				//y1 = Reflect(original_image_.rows, y - i);
				//x1 = Reflect(original_image_.rows, x - i);
				gx += separable_kernel_x_[i + radius_ / 2] * original_image_.at<uchar>(y, x - i);
				gy += separable_kernel_y_[i + radius_ / 2] * original_image_.at<uchar>(y - i, x);
			}
			gx = (gx < 0) ? -gx : gx;
			gy = (gy < 0) ? -gy : gy;
			sum = gx + gy;
			sum = sum > 255 ? 255 : sum;
			sum = sum < 0 ? 0 : sum;
			temp.at<uchar>(y, x) = sum;
		}
	}

	for (int y = radius_ / 2; y < original_image_.rows - radius_ / 2; y++) {
		for (int x = radius_ / 2; x < original_image_.cols - radius_ / 2; x++) {
			gx = 0;
			gy = 0;
			sum = 0.0;
			for (int i = -radius_ / 2; i <= radius_ / 2; ++i) {
				//y1 = Reflect(original_image_.rows, y - i);
				//x1 = Reflect(original_image_.rows, x - i);
				gx += separable_kernel_x_[i + radius_ / 2] * temp.at<uchar>(y - i, x);
				gy += separable_kernel_y_[i + radius_ / 2] * temp.at<uchar>(y, x - i);
			}
			gx = (gx < 0) ? -gx : gx;
			gy = (gy < 0) ? -gy : gy;
			sum = gx + gy;
			sum = sum > 255 ? 255 : sum;
			sum = sum < 0 ? 0 : sum;
			processed_image_.at<uchar>(y, x) = sum;
		}
	}
	SaveProcessedImage();
}
