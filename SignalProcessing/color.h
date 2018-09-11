#pragma once
#include<iostream>

class color {
public:
	color();
	color(float n);
	color(float _r, float g, float b);
	color(const color &c);

	color operator+(const color &c);
	color operator-(const color &c);
	color& operator=(const color &c);
	color operator*(float n) const;
	bool operator!=(const color &c);
	friend std::ostream& operator<<(std::ostream &os, const color &c);

	float _r, _g, _b;
};