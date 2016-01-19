#include "GaussianFilter.h"
#include <cmath>

#define PI 4. * atan(1.)

double GaussianFilter::Formula(int x, int y)
{
	double s = 2.0 * sigma_ * sigma_;
	double r = sqrt(x * x + y * y); 
	double result = (exp(-(r * r) / s)) / (PI * s);
	return result;
}

double GaussianFilter::SeparableFormula(int x)
{
	double s = 2.0 * sigma_ * sigma_;
	double r = x;
	double result = (exp(-(r * r) / s)) / sqrt(PI * s);
	return result;
}

void GaussianFilter::Print()
{
	std::cout << "sigma_ = " << sigma_
		<< " radius_ = " << radius_
		<< " kernel_ :\n";
	for (int i = 0; i < radius_; ++i) {
		for (int j = 0; j < radius_; ++j)
			std::cout << kernel_[i][j] << ' ';
		std::cout << '\n';
	}
}