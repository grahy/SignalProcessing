#include"image.h"

image::image(const texture2d& texture)
	:_w(texture._width),_h(texture._height)
{
	_mat = new color*[_h];
	for (int i = 0; i < _h; i++) {
		_mat[i] = new color[_w];
	}
	for (int i = 0; i < _h; i++) {
		for (int j = 0; j < _w; j++) {
			_mat[_h - i - 1][j] = texture._texc[_h - i - 1][j];
		}
	}
}

image::image(const image& img)
	:_w(img._w),_h(img._h)
{
	_mat = new color*[_h];
	for (int i = 0; i < _h; i++) {
		_mat[i] = new color[_w];
	}
	for (int i = 0; i < _h; i++) {
		for (int j = 0; j < _w; j++) {
			_mat[_h - i - 1][j] = img._mat[_h - i - 1][j];
		}
	}
}

image::image(int w, int h) 
	:_w(w),_h(h)
{
	_mat = new color*[_h];
	for (int i = 0; i < _h; i++) {
		_mat[i] = new color[_w];
	}
}

image::~image() {
	for (int i = 0; i < _h; i++) {
		delete[]_mat[i];
	}
	delete[]_mat;
}