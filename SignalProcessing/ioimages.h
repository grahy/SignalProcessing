#pragma once
#include<Windows.h>
#include"color.h"
#include<fstream>
#include"texture.h"
#include"image.h"

void generate_color_PPM(const char *filename, const image& img);


bool getBmpData(const char *filepath, color **texc);

texture2d readBmp(const char *filepath);