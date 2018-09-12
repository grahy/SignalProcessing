#include"signal.h"
#include<math.h>

Filter::Filter(float radius) 
	:_radius(radius)
{

}

float Filter::radius() const{
	return _radius;
}

Discrete::Discrete()
	:Filter(0)
{

}

Discrete::~Discrete() {

}

float Discrete::weighted(float x) const{
	return 1;
}

Tent::Tent(float radius)
	:Filter(radius)
{

}

Tent::~Tent() {

}

float Tent::weighted(float x) const {
	x = abs(x);
	if (x < _radius) {
		return 1 - x;
	}
	return 0;
}

Box::Box(float radius)
	:Filter(radius)
{

}

Box::~Box() {

}

float Box::weighted(float x) const {
	x = abs(x);
	if (x <= _radius) {
		return 1.0f / (2 * _radius + 1);
	}
	return 0;
}

Gaussian::Gaussian(float radius)
	:Filter(radius)
{

}

Gaussian::~Gaussian() {

}

float Gaussian::weighted(float x) const{
	x = abs(x);
	if (x <= _radius) {
		float coefficient = 1.0f / (1 * sqrt(2 * 3.14f));
		float var = pow(2.71828f, -x * x / 2);
		return coefficient * var;
	}
	return 0;
}

bool isInteger(float num) {
	int temp = num;
	return num > temp ? false : true;
}

color Convolution::Convolved2d(const image& img, Filter& f, int w, int h) { // discrete - discrete
	color s = 0;
	float r = f.radius();
	for (int m = w - r; m <= w + r; m++) {
		for (int n = h - r; n <= h + r; n++) {
			if ( (m<0) || (m>=img._w) || (n<0) || (n>=img._h))continue;
			s = s + img._mat[n][m] * f.weighted(w - m)*f.weighted(h - n);
		}
	}
	return s;
}

color Convolution::reConstruct(const image& img, Filter& f, float w, float h) { //discrete - constant
	float r = f.radius();
	color s;
	for (int m = w - r - 1; m <= w + r; m++) {
		for (int n = h - r - 1; n <= h + r; n++) {
			if ((m < 0) || (m >= img._w) || (n < 0) || (n >= img._h))continue;
			s = s + img._mat[n][m] * f.weighted(w - m)*f.weighted(h - n);
		}
	}
	return s;
}

std::shared_ptr<image> Convolution::reSample(const image& img, int nW,int nH, Filter& reconstructor) {
	std::shared_ptr<image> nImg(new image(nW, nH));
	std::shared_ptr<image> transX(new image(nW, img._h));
	int x0 = 0, y0 = 0;
	float deltaX = float(img._w) / float(nW);
	float deltaY = float(img._h) / float(nH);
	for (int h = 0; h < img._h; h++) {
		for (int w = 0; w < nW; w++) {
			transX->_mat[h][w] = reConstruct(img, reconstructor, x0 + deltaX / 2.0f + w * deltaX, h);
		}
	}
	for (int w = 0; w < nW; w++) {
		for (int h = 0; h < nH; h++) {
			nImg->_mat[h][w] = reConstruct(*transX, reconstructor, w, y0 + deltaY / 2.0f + h * deltaY);
		}
	}
	return nImg;
}

void Convolution::blur(image& img, Filter& f) {
	image temp(img._w, img._h);
	for (int w = 0; w < img._w; w++) {
		for (int h = 0; h < img._h; h++) {
			temp._mat[h][w] = Convolution::Convolved2d(img, f, w, h);
		}
	}
	for (int w = 0; w < img._w; w++) {
		for (int h = 0; h < img._h; h++) {
			img._mat[h][w] = temp._mat[h][w];
		}
	}
}

void Convolution::sharp(image& img) {
	Discrete d;
	Gaussian g(1);
	float a = 0.3f;
	image temp(img);
	for (int w = 0; w < img._w; w++) {
		for (int h = 0; h < img._h; h++) {
			color tempc= Convolved2d(img, d, w, h)*(1 + a) - Convolved2d(img, g, w, h)*a;
			if (tempc._r < 0 || tempc._g < 0 || tempc._b < 0) {
				temp._mat[h][w] = color(0);
			}
			else {
				temp._mat[h][w] = tempc;
			}
		}
	}
	for (int w = 0; w < img._w; w++) {
		for (int h = 0; h < img._h; h++) {
			img._mat[h][w] = temp._mat[h][w];
		}
	}
}