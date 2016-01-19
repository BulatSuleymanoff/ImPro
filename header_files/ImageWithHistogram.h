#pragma once
#include "Header.h"

namespace cvl {

	class ImageWithHistogram : public Image, public Histogram
	{
	public:
		ImageWithHistogram() {
			Image image_;
		}
		ImageWithHistogram(Image image) : image_(image) {};
		~ImageWithHistogram() {};
		void set_histogram();
		int* get_histogram();
		void DisplayHist();
		void Equalize();
	private:
		int histogram_[256];
		Image image_;
	};
}

