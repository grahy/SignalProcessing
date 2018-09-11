#include"ioimages.h"
void generate_color_PPM(const char *filename, const int &w, const int &h,const image& img) {

	std::ofstream outfile;
	outfile.open(filename, std::ios::out);
	outfile << "P3\n" << w << " " << h << "\n" << "255\n";
	if (!outfile.is_open()) {
		std::cout << "failed to open file" << std::endl;
		return;
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			outfile << img._mat[i][j]._r << " " << img._mat[i][j]._g << " " << img._mat[i][j]._b << "\n";
		}
	}
	outfile.close();
}


bool getBmpData(const char *filepath, color **texc) {                                       //��֧��24λ �� ÿ������Ϊ4 �ı��� ��BMPͼƬ
	FILE *f;
	fopen_s(&f, filepath, "rb");
	if (!f) {
		std::cout << "fail to open" << std::endl;
		return false;
	}
	fseek(f, sizeof(BITMAPFILEHEADER), 0);
	BITMAPINFOHEADER info;
	fread_s(&info, sizeof(BITMAPINFOHEADER), sizeof(byte), sizeof(BITMAPINFOHEADER), f);
	if (info.biBitCount != 24) {
		return false;
	}
	int width = info.biWidth;
	int height = info.biHeight;

	byte *colorData = (byte*)malloc(info.biHeight*info.biWidth*info.biBitCount);

	int l_width = (width * info.biBitCount + 31) / 32 * 4;
	memset(colorData, 0, height*l_width);
	fread(colorData, 1, height*l_width, f);

	for (int h = 0; h < info.biHeight; h++) {
		for (int w = 0; w < info.biWidth; w++) {
			int k = h * l_width + w * 3;

			texc[height - h - 1][w]._r = colorData[k + 2];
			texc[height - h - 1][w]._g = colorData[k + 1];
			texc[height - h - 1][w]._b = colorData[k];
		}
	}
	fclose(f);
	free(colorData);
	colorData = NULL;
	return true;
}

texture2d readBmp(const char *filepath) {
	FILE *f;
	fopen_s(&f, filepath, "rb");
	if (!f) {
		std::cout << "failed to open file" << std::endl;
		std::exit(-1);
	}
	BITMAPINFOHEADER info;
	fseek(f, sizeof(BITMAPFILEHEADER), 0);
	fread(&info, sizeof(byte), sizeof(BITMAPINFOHEADER), f);

	color **texc = new color*[info.biHeight];
	for (int i = 0; i < info.biHeight; i++) {
		texc[i] = new color[info.biWidth];
	}
	if (!getBmpData(filepath, texc)) {
		std::cout << "the bitmap is not 24 depth feild" << std::endl;
		std::exit(-1);
	}
	return texture2d(texc, info.biWidth, info.biHeight);
}
