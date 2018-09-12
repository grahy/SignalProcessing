#include"ioimages.h"
#include"image.h"
#include"signal.h"
void modifyImage() {

}

void demo_blur(const char* filepath) {
	texture2d texture(readBmp("D:/images/cat.bmp"));
	image img(texture);
	Gaussian t(2);
	Convolution::blur(img, t);
	generate_color_PPM(filepath, img);
}

void demo_sharp(const char* filepath) {
	texture2d texture(readBmp("D:/images/cat.bmp"));
	image img(texture);
	Gaussian t(2);
	Convolution::blur(img, t);
	Convolution::sharp(img);
	generate_color_PPM(filepath, img);
}

void demo_UpSample(const char* filepath) {
	texture2d texture(readBmp("D:/images/cat.bmp"));
	image img(texture);
	Gaussian f(2);
	std::shared_ptr<image> nImg(Convolution::reSample(img, 213, 194, f));
	generate_color_PPM(filepath, *nImg);
}

void demo_DownSample(const char* filepath) {
	texture2d texture(readBmp("D:/images/cat.bmp"));
	image img(texture);
	Gaussian f(2);
	std::shared_ptr<image> nImg(Convolution::reSample(img, 960, 890, f));
	generate_color_PPM(filepath, *nImg);
}

int main() {
	//demo_blur("D:/github/SignalProcessing/SignalProcessing/images/GaussianFilter.ppm");
	//demo_sharp("D:/github/SignalProcessing/SignalProcessing/images/SharpImage.ppm");
	//demo_UpSample("D:/github/SignalProcessing/SignalProcessing/images/UpSample.ppm");
	//demo_DownSample("D:/github/SignalProcessing/SignalProcessing/images/DownSample.ppm");
	system("pause");
	return 0;
}