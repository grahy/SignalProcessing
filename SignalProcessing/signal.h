#pragma once
#include"image.h"


class Filter {
public:
	virtual float weighted(float x) const = 0;
	virtual float radius()const;
protected:
	Filter(float radius);
	float _radius;
};

class Discrete :public Filter {
public:
	Discrete();
	~Discrete();
	virtual float weighted(float x)const;
};

class Tent :public Filter {
public:
	Tent(float radius);
	~Tent();
	virtual float weighted(float x)const override;
};

class Box :public Filter {
public:
	Box(float radius);
	~Box();
	virtual float weighted(float x)const override;
};

class Gaussian : public Filter {
public:
	Gaussian(float radius);
	~Gaussian();
	virtual float weighted(float x)const override;
};

namespace Convolution {
	color Convolved2d(const image& img, Filter& f, int w, int h);
	color reConstruct(const image& img, Filter& f, float w, float h);
	image* reSample(const image& img, int nW, int nH, Filter& reconstructor);
	void blur(image& img, Filter& f);
	void sharp(image& img);
}