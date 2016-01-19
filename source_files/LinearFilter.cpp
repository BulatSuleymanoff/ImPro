#include "LinearFilter.h"


void LinearFilter::set_kernel_radius(int radius)
{
	radius_ = radius;
	if (mode_ == false) {
		kernel_ = new double*[radius_];
		for (int i = 0; i < radius_; ++i)
			kernel_[i] = new double[radius_];
		GenerateKernel();
	}
	else {
		separable_kernel_x_ = new double[radius_];
		separable_kernel_y_ = new double[radius_];
		GenerateSeparableKernel();
	}
}

void LinearFilter::set_mode(bool mode)
{
	if (mode_ == false)
		delete kernel_;
	else {
		delete separable_kernel_x_;
		delete separable_kernel_y_;
	}
	mode_ = mode;
}

int LinearFilter::Reflect(int M, int x)
{
	if (x < 0)
		return -x - 1;

	if (x >= M)
		return 2 * M - x - 1;

	return x;
}

int LinearFilter::Circular(int M, int x)
{
	if (x < 0)
		return x + M;
	if (x >= M)
		return x - M;
	return x;
}

void LinearFilter::ReflectedIndexingConvolution()
{
	//Mat src = original_image_;
	//Mat dst = processed_image_;
	float sum, x1, y1;
	for (int y = 0; y < original_image_.rows; y++){
		for (int x = 0; x < original_image_.cols; x++){
			sum = 0.0;
			for (int k = -radius_ / 2; k <= radius_ / 2; k++){
				for (int j = -radius_ / 2; j <= radius_ / 2; j++){
					x1 = Reflect(original_image_.cols, x - j);
					y1 = Reflect(original_image_.rows, y - k);
					sum = sum + kernel_[j + radius_ / 2][k + radius_ / 2] * original_image_.at<uchar>(y1, x1);
				}
			}
			sum = (sum > 255) ? 255 : sum;
			sum = (sum < 0) ? 0 : sum;
			processed_image_.at<uchar>(y, x) = sum;
		}
	}
}
void LinearFilter::CircularIndexingConvolution()
{
	Mat src = original_image_;
	Mat dst = processed_image_;
	float sum, x1, y1;
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			sum = 0.0;
			for (int k = -radius_ / 2; k <= radius_ / 2; k++) {
				for (int j = -radius_ / 2; j <= radius_ / 2; j++) {
					x1 = Circular(src.cols, x - j);
					y1 = Circular(src.rows, y - k);
					sum = sum + kernel_[j + radius_ / 2][k + radius_ / 2] * src.at<uchar>(y1, x1);
				}
			}
			sum = (sum > 255) ? 255 : sum;
			sum = (sum < 0) ? 0 : sum;
			dst.at<uchar>(y, x) = sum;
		}
	}
}

void LinearFilter::NoBoarderConvolution()
{
	Mat src = original_image_;
	Mat dst = processed_image_;
	float sum;
	for (int y = radius_ / 2; y < src.rows - radius_ / 2; y++){
		for (int x = radius_ / 2; x < src.cols - radius_ / 2; x++){
			sum = 0.0;
			for (int i = -radius_ / 2; i <= radius_ / 2; i++){
				for (int j = -radius_ / 2; j <= radius_ / 2; j++){
					//x1 = Reflect(src.cols, x - i);
					//y1 = Reflect(src.rows, y - j);
					sum = sum + kernel_[j + radius_ / 2][i + radius_ / 2] * src.at<uchar>(y - j, x - i);
				}
			}
			sum = (sum > 255) ? 255 : sum;
			sum = (sum < 0) ? 0 : sum;
			dst.at<uchar>(y, x) = sum;
		}
	}
}

void LinearFilter::SeparableKernelConvolution()
{
	Mat src = original_image_;
	Mat dst = processed_image_;
	Mat temp = src.clone();
	float sum, x1, y1;

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			sum = 0.0;
			for (int i = -radius_ / 2; i <= radius_ / 2; i++) {
				y1 = Reflect(src.rows, y - i);
				sum = sum + separable_kernel_x_[i + radius_ / 2] * src.at<uchar>(y1, x);
			}
			sum = (sum > 255) ? 255 : sum;
			sum = (sum < 0) ? 0 : sum;
			temp.at<uchar>(y, x) = sum;
		}
	}

	// along x - direction
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			sum = 0.0;
			for (int i = -radius_ / 2; i <= radius_ / 2; i++) {
				x1 = Reflect(src.cols, x - i);
				sum = sum + separable_kernel_x_[i + radius_ / 2] * temp.at<uchar>(y, x1);
			}
			sum = (sum > 255) ? 255 : sum;
			sum = (sum < 0) ? 0 : sum;
			dst.at<uchar>(y, x) = sum;
		}
	}
}

void LinearFilter::Convolve()
{
	if (mode_ == SEPARABLE)
		SeparableKernelConvolution();
	else NoBoarderConvolution();
}

void LinearFilter::GenerateCorrectKernel()
{
	if (mode_ == SEPARABLE)
		GenerateSeparableKernel();
	else GenerateKernel();
}

void LinearFilter::GenerateSeparableKernel()
{
	double sum = 0.0;
	for (int x = -radius_ / 2; x <= radius_ / 2; x++) {
		separable_kernel_x_[x + radius_ / 2] = SeparableFormula(x);
		sum += separable_kernel_x_[x + radius_ / 2];
	}

	for (int i = 0; i < radius_; ++i)
		separable_kernel_x_[i] /= sum;

	for (int x = -radius_ / 2; x <= radius_ / 2; x++) {
		separable_kernel_y_[x + radius_ / 2] = SeparableFormula(x);
		sum += separable_kernel_y_[x + radius_ / 2];
	}
	
	for (int i = 0; i < radius_; ++i)
		separable_kernel_y_[i] /= sum;
}

void LinearFilter::Normalize(double sum)
{
	for (int i = 0; i < radius_; ++i)
		for (int j = 0; j < radius_; ++j)
			kernel_[i][j] /= sum;
}

void LinearFilter::GenerateKernel()
{
	double sum = 0.0;
	for (int x = -radius_ / 2; x <= radius_ / 2; x++) {
		for (int y = -radius_ / 2; y <= radius_ / 2; y++) {
			kernel_[x + radius_ / 2][y + radius_ / 2] = Formula(x, y);
			sum += kernel_[x + radius_ / 2][y + radius_ / 2];
		}
	}
	Normalize(sum);
}

void LinearFilter::Invoke()
{
	Convolve();
	//Display(1);
}