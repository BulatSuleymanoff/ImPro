#include "LoGFilter.h"
#include <cmath>

#define PI 4. * atan(1.)

double LoGFilter::Formula(int x, int y)
{
	double s = 2.0 * sigma_ * sigma_;
	double r = sqrt(x * x + y * y);
	double result = (exp(-(r * r) / s)) * (-4 / (PI * s * s) + (4 * r * r /(PI * s * s * s)));
	return result;
}

double LoGFilter::SeparableFormula(int x)
{
	double s = sigma_ * sigma_;
	double r = x;
	double result = (exp(-(r * r) / ( 2.0 * s))) * ((r * r) / (s * s) - 1 / s);
	return result;
}