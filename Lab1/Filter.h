#pragma once
#include <QImage>
#include <iostream>
#include <fstream>
#include <cmath>

#define NOMINMAX
#include <windows.h>

const double PI = 3.14159265;
const int MaxLength = 80;
const int sigma = 2;
const int SizeG = 7; 
const int SizeB = 5;
const int SizeM = 5;
using namespace std;

template <class T, class T1>
T clamp(T value, T1 min, T1 max)
{
	if (value > max)
		return max;
	if (value < min)
		return min;
	return value;
}

class Filter
{
protected:
	virtual QColor calcNewPixelColor(const QImage& photo, int x, int y) = 0;
public:
	virtual QImage process(const QImage& photo) ;
};

class InvertFilter :public Filter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y) override;
};

class GreyScaleFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y) override;
};

class SepiaFilter :public Filter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
};

class IncreasedBrightnessFilter :public Filter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
};

class IdealReflector : public Filter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
protected:
	int MaxR, MaxG, MaxB, flag;
public:
	IdealReflector();
};


class HorizontalWaves :public Filter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
};

class VerticalWaves : public Filter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
};

class GlassEffect : public Filter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
};

class LinearStretching : public Filter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y) override;
protected:
	int MaxR = 0, MinR = 255;
	 int MaxG = 0, MinG = 255;
	int MaxB = 0, MinB = 255;
	int flag = 1;
};

class MedianFilter : public Filter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
};

class MatrixFilter :public Filter
{
protected:
	int kernelSize;
	float** kernel;
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
public:
	MatrixFilter(char* fn);
	~MatrixFilter();
};

void BlurKernel(char* fn);
void GaussianKernel(char* file_name);

class Dilation : public MatrixFilter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
public:
	Dilation(char* fn) : MatrixFilter(fn) {}
};

class Erosion : public MatrixFilter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
public:
	Erosion(char* fn) : MatrixFilter(fn) {}
};

class Grad : public MatrixFilter
{
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
public:
	Grad(char* fn) : MatrixFilter(fn) {}
};

class MatrixFilterTwoKernels :public Filter
{
	int kernelSize;
	float** kernelX, ** kernelY;
	QColor calcNewPixelColor(const QImage& photo, int x, int y)  override;
public:
	MatrixFilterTwoKernels(char* fnX, char* fnY);
	~MatrixFilterTwoKernels();
};


