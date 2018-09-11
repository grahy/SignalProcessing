#pragma once
#include"texture.h"
#include"color.h"
class image {
public:
	image(const texture2d& texture);
	image(const image& img);
	image(int w, int h);
	~image();
	int _w, _h;
	color **_mat;
};