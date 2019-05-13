#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define PI 3.14159

using namespace cv;
using namespace std;

struct Cnum {
	float real;
	float irreal;
};
//定义复数结构
Cnum Mult(Cnum a, Cnum b) {
	return { a.real*b.real - a.irreal*b.irreal, a.real*b.irreal + a.irreal * b.real };
}
//复数乘法
Cnum Add(Cnum a, Cnum b) {
	return { a.real + b.real, a.irreal + b.irreal };
}
//复数加法
int check_Binary(int length) {
	int i = 0;
	while (length != 1) {
		if (length % 2 == 0) {
			length = length / 2;
			i++;
		}
		else {
			return -1;
		}
	}
	return i;
}
//检查是否为2的倍数

int reverse_Bit(int num, int len) {
	int bit;
	unsigned new_num = 0;
	for (int i = 0; i < len; i++) {
		bit = num & 1;
		new_num <<= 1;
		new_num = new_num | bit;
		num >>= 1;
	}
	return new_num;
}
//逆序置换
Mat image_Binary(Mat im) {
	float c = im.cols, r = im.rows;
	int cn = 0, rn = 0, cnew = 2, rnew = 2;
	while (c / 2 > 1) {
		c = c / 2;
		cn++;
	}
	while (r / 2 > 1) {
		r = r / 2;
		rn++;
	}
	while (cn > 0) {
		cnew = cnew * 2;
		cn--;
	}
	while (rn > 0) {
		rnew = rnew * 2;
		rn--;
	}
	resize(im, im, Size(cnew, rnew));
	return im;
}
//将图片转换为2的幂次大小

void FFT(Mat im) {
	int width = im.cols;
	int height = im.rows;
	int Bin_width, Bin_Height;
	vector<Cnum> result_Temp;

	vector<int>map_Width;
	vector<int>map_Height;
	//映射表
	vector<Cnum>map_Wwidth;
	vector<Cnum>map_Wheight;
	//w值表
	Bin_width = check_Binary(width);
	Bin_Height = check_Binary(height);
	if (Bin_width == -1 || Bin_Height == -1) {
		FFT(image_Binary(im));
		return;
	}

	for (int i = 0; i < im.cols; i++) {
		map_Width.push_back(0);
	}
	for (int j = 0; j < im.rows; j++) {
		map_Height.push_back(0);
	}
	for (int i = 0; i < im.cols; i++) {
		map_Width.at(reverse_Bit(i, Bin_width)) = i;
	}
	for (int j = 0; j < im.rows; j++) {
		map_Height.at(reverse_Bit(j, Bin_Height)) = j;
	}
	//映射表的构造
	for (int i = 0; i < width / 2; i++) {
		Cnum w = { cosf(2 * PI / width*i),-1 * sinf(2 * PI / width*i) };
		map_Wwidth.push_back(w);
	}
	for (int j = 0; j < height / 2; j++) {
		Cnum w = { cosf(2 * PI / height*j),-1 * sinf(2 * PI / height*j) };
		map_Wheight.push_back(w);
	}
	//w表的构造
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			Cnum w = { (float)im.at<uchar>(map_Height.at(r),map_Width.at(c)) / 255,0 };
			result_Temp.push_back(w);
		}
	}
	//初始化
	for (int r = 0; r < height; r++) {
		for (int i = 0; i < Bin_width; i++) {
			int com_Size = 2 << i;
			vector<Cnum>newRow;
			for (int j = 0; j < width; j = j + com_Size) {
				int n;
				for (int k = 0; k < com_Size; k++) {
					if (k < com_Size >> 1) {
						int w = k*width / com_Size;
						n = k + j + r*width;
						newRow.push_back(Add(result_Temp.at(n), Mult(result_Temp.at(n + (com_Size >> 1)), map_Wwidth.at(w))));
					}
					else {
						int w = (k - (com_Size >> 1)) * width / com_Size;
						n = k + j - (com_Size >> 1) + r*width;
						newRow.push_back(Add(result_Temp.at(n), Mult({ -1, 0 }, Mult(result_Temp.at(n + (com_Size >> 1)), map_Wwidth.at(w)))));
					}
				}
			}

			for (int j = 0; j < width; j++) {
				int n = j + r*width;
				result_Temp.at(n) = newRow.at(j);
			}
			newRow.clear();
		}
	}
	//计算行
	for (int c = 0; c < width; c++) {
		for (int i = 0; i < Bin_Height; i++) {
			int combineSize = 2 << i;
			vector <Cnum> newColum;
			for (int j = 0; j < height; j = j + combineSize) {
				int n;
				for (int k = 0; k < combineSize; k++) {
					if (k < (combineSize >> 1)) {
						int w = k * height / combineSize;
						n = (j + k) * width + c;
						newColum.push_back(Add(result_Temp.at(n), Mult(result_Temp.at(n + (combineSize >> 1)*width), map_Wheight.at(w))));
					}
					else {
						int w = (k - (combineSize >> 1)) * height / combineSize;
						n = (j + k - (combineSize >> 1)) * width + c;
						newColum.push_back(Add(result_Temp.at(n), Mult({ -1, 0 }, Mult(result_Temp.at(n + (combineSize >> 1)*width), map_Wheight.at(w)))));
					}
				}
			}
			//用newColum来更新result_Temp中的值
			for (int j = 0; j < height; j++) {
				int n = j*width + c;
				result_Temp.at(n) = newColum.at(j);
			}
			newColum.clear();
		}
	}
	//计算列

	float Max, Min;
	vector<float>ampl;
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			Cnum e = result_Temp.at(r*width + c);
			float val = sqrt(e.real*e.real + e.irreal*e.irreal) + 1;
			val = log(val);
			ampl.push_back(val);
			if (c == 0 && r == 0) {
				Max = val;
				Min = val;
			}
			else {
				if (Max < val)
					Max = val;
				if (Min > val)
					Min = val;
			}
		}
	}
	Mat result_Final = Mat(width, height, CV_8UC1);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int val = (int)((ampl.at(i*width + j) - Min) * 255 / (Max - Min));
			result_Final.at<uchar>(i, j) = val;
		}
	}

	int cx = result_Final.cols / 2;
	int cy = result_Final.rows / 2;
	Mat q0(result_Final, Rect(0, 0, cx, cy));
	Mat q1(result_Final, Rect(cx, 0, cx, cy));
	Mat q2(result_Final, Rect(0, cy, cx, cy));
	Mat q3(result_Final, Rect(cx, cy, cx, cy));

	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	//平移相位图

	imshow("FFT", result_Final);
	waitKey();

}

int main(void) {
	string path;
	cout << "Please input file path." << endl;
	cin >> path;
	Mat Image = imread(path);
	cvtColor(Image, Image, COLOR_BGR2GRAY);
	
	FFT(Image);

	return 0;
}