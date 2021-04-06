#include "Filter.h"

QImage Filter::process(const QImage& photo) 
{
	QImage res(photo);
	for (int x = 0; x < photo.width() / 2; x++)
	{
		for (int y = 0; y < photo.height(); y++)
		{
			QColor color = calcNewPixelColor(photo, x, y);
			res.setPixelColor(x, y, color);
		}
	}
	return res;
}

QColor InvertFilter::calcNewPixelColor(const QImage& photo, int x, int y) 
{
	QColor color = photo.pixelColor(x, y);
	color.setRgb(255 - color.red(), 255 - color.green(), 255 - color.blue());
	return color;
}

QColor GreyScaleFilter::calcNewPixelColor(const QImage& photo, int x, int y) 
{
	QColor color = photo.pixelColor(x, y);
	float intensity = 0.299 * color.red() + 0.587 * color.green() + 0.144 * color.blue();
	color.setRgb(clamp(intensity,0.f,255.f), clamp( intensity,0.f, 255.f), clamp( intensity, 0.f, 255.f));
	return color;
}

QColor SepiaFilter::calcNewPixelColor(const QImage& photo, int x, int y) 
{
	QColor color = photo.pixelColor(x, y);
	float intensity = 0.299 * color.red() + 0.587 * color.green() + 0.144 * color.blue();
	int k = 20;
	float returnR = 0;
	returnR = intensity + 2 * k;
	float returnG = 0;
	returnG = intensity + 0.5 * k;
	float returnB = 0;
	returnB = intensity - 1 * k;
	color.setRgb(clamp(returnR, 0.f, 255.f), clamp(returnG, 0.f, 255.f), clamp(returnB, 0.f, 255.f));
	return color;
}

QColor IncreasedBrightnessFilter::calcNewPixelColor(const QImage& photo, int x, int y) 
{
	QColor color = photo.pixelColor(x, y);
	int k = 20;
	float returnR = 0;
	returnR = color.red() + k;
	float returnG = 0;
	returnG = color.green() + k;
	float returnB = 0;
	returnB = color.blue() + k;
	color.setRgb(clamp(returnR, 0.f, 255.f), clamp(returnG, 0.f, 255.f), clamp(returnB, 0.f, 255.f));
	return color;
}

IdealReflector::IdealReflector()
{
	MaxR = 0;
	MaxG = 0;
	MaxB = 0;
	flag = 1;
}

QColor IdealReflector::calcNewPixelColor(const QImage& photo, int x, int y) 
{
	if (flag)
	{
		for (int i = 0; i < photo.width() - 1; i++)
		{
			for (int j = 0; j < photo.height() - 1; j++)
			{
				QColor color = photo.pixelColor(i, j);
				if (color.red() > MaxR)
					MaxR = color.red();
				if (color.green() > MaxG)
					MaxG = color.green();
				if (color.blue() > MaxB)
					MaxB = color.blue();
			}
		} 
		flag = 0;
	}

	QColor color = photo.pixelColor(x, y);
	float returnR = 0;
	returnR = (photo.pixelColor(x, y).red() * 255) / MaxR;
	float returnG = 0;
	returnG = (photo.pixelColor(x, y).green() * 255) / MaxG;
	float returnB = 0;
	returnB = (photo.pixelColor(x, y).blue() * 255) / MaxB;
	color.setRgb(clamp(returnR, 0.f, 255.f), clamp(returnG, 0.f, 255.f), clamp(returnB, 0.f, 255.f));
	return color;
}

QColor HorizontalWaves::calcNewPixelColor(const QImage& photo, int x, int y) 
{
	int X = x + 20 * sin((2 * PI * y) / 60);
	int Y = y;
	QColor color = photo.pixelColor(x, y);
	color.setRgb(photo.pixelColor(clamp(X, 0, photo.width() - 1), Y).red(), photo.pixelColor(clamp(X, 0, photo.width() - 1), Y).green(), photo.pixelColor(clamp(X, 0, photo.width() - 1), Y).blue());
	return color;
}

QColor VerticalWaves::calcNewPixelColor(const QImage& photo, int x, int y) 
{
	int X = x + 20 * sin((2 * PI * x) / 30);
	int Y = y;
	QColor color = photo.pixelColor(x, y);
	color.setRgb(photo.pixelColor(clamp(X, 0, photo.width() - 1), Y).red(), photo.pixelColor(clamp(X, 0, photo.width() - 1), Y).green(), photo.pixelColor(clamp(X, 0, photo.width() - 1), Y).blue());
	return color;
}

QColor GlassEffect::calcNewPixelColor(const QImage& photo, int x, int y)
{
	int X = x + ((double)rand() / RAND_MAX - 0.5) * 10;
	int Y = y + ((double)rand() / RAND_MAX - 0.5) * 10;
	QColor color = photo.pixelColor(x, y);
	color.setRgb(photo.pixelColor(clamp(X, 0, photo.width() - 1), clamp(Y, 0, photo.height() - 1)).red(), photo.pixelColor(clamp(X, 0, photo.width() - 1), clamp(Y, 0, photo.height() - 1)).green(), photo.pixelColor(clamp(X, 0, photo.width() - 1), clamp(Y, 0, photo.height() - 1)).blue());
	return color;
}

QColor LinearStretching::calcNewPixelColor(const QImage& photo, int x, int y) 
{
	if (flag)
	{
		for (int i = 0; i < photo.width(); i++)
		{
			for (int j = 0; j < photo.height(); j++)
			{
				QColor color = photo.pixelColor(i, j);
				if (color.red() > MaxR)
					MaxR = color.red();
				if (color.red() < MinR)
					MinR = color.red();
				if (color.green() > MaxG)
					MaxG = color.green();
				if (color.green() < MinG)
					MinG = color.green();
				if (color.blue() > MaxB)
					MaxB = color.blue();
				if (color.blue() < MinB)
					MinB = color.blue();
			}
		}
		flag = 0;
	}
	QColor color = photo.pixelColor(x, y);
	float returnR = 0;
	returnR = (photo.pixelColor(x, y).red() - MinR) * 255 / (MaxR - MinR);
	float returnG = 0;
	returnG = (photo.pixelColor(x, y).green() - MinG) * 255 / (MaxG - MinG);
	float returnB = 0;
	returnB = (photo.pixelColor(x, y).blue() - MinB) * 255 / (MaxB - MinB);
	color.setRgb(clamp(returnR, 0.f, 255.f), clamp(returnG, 0.f, 255.f), clamp(returnB, 0.f, 255.f));
	return color;
}

QColor MedianFilter::calcNewPixelColor(const QImage& photo, int x, int y)
{
	const int KernelSize = SizeM * SizeM;
	int red[KernelSize], green[KernelSize], blue[KernelSize];
	int X = clamp(x - SizeM / 2, 0, photo.width() - 1);
	int Y = clamp(y - SizeM / 2, 0, photo.height() - 1);
	int a = 0;
	for (int i = 0; i < SizeM; i++)
	{
		for (int j = 0; j < SizeM; j++)
		{
			red[a] = photo.pixelColor(clamp(x - SizeM / 2 + j, 0, photo.width() - 1), clamp(y - SizeM / 2 + i, 0, photo.height() - 1)).red();
			green[a] = photo.pixelColor(clamp(x - SizeM / 2 + j, 0, photo.width() - 1), clamp(y - SizeM / 2 + i, 0, photo.height() - 1)).green();
			blue[a] = photo.pixelColor(clamp(x - SizeM / 2 + j, 0, photo.width() - 1), clamp(y - SizeM / 2 + i, 0, photo.height() - 1)).blue();
			a++;
		}
	}
	sort(red, red + KernelSize);
	sort(green, green + KernelSize);
	sort(blue, blue + KernelSize);
	QColor color = photo.pixelColor(x, y);
	color.setRgb(red[KernelSize/2], green[KernelSize / 2], blue[KernelSize / 2]);
	return color;
}

MatrixFilter::MatrixFilter(char* fn)
{
	char Buff[MaxLength];
	ifstream istr(fn);
	istr.getline(Buff, MaxLength, '\n');
	kernelSize = Buff[0] - '0';
	kernel = new float* [kernelSize];
	float norm = 0;
	for (int i = 0; i < kernelSize; i++)
	{
		kernel[i] = new float[kernelSize];
		for (int j = 0; j < kernelSize; j++)
		{
			istr.getline(Buff, MaxLength, ' ');
			kernel[i][j] = atof(Buff);
			norm += kernel[i][j];
		}
	}
	if (norm)
	{
		for (int i = 0; i < kernelSize; i++)
		{
			for (int j = 0; j < kernelSize; j++)
			{
				kernel[i][j] /= norm;
			}
		}
	}
}

MatrixFilter::~MatrixFilter()
{
	for (int i = 0; i < kernelSize; i++)
	{
		delete[]kernel[i];
	}
	delete[] kernel;
}

QColor MatrixFilter::calcNewPixelColor(const QImage& photo, int x, int y) 
{
	float returnR = 0;
	float returnG = 0;
	float returnB = 0;
	int X = clamp(x - kernelSize /2, 0, photo.width() - 1);
	int Y = clamp(y - kernelSize /2, 0, photo.height() - 1);
	for (int i = 0; i < kernelSize; i++)
	{
		for (int j = 0; j < kernelSize; j++)
		{
			QColor color = photo.pixelColor(clamp(x - kernelSize / 2 + j, 0, photo.width() - 1), clamp(y - kernelSize / 2 + i, 0, photo.height() - 1));
			returnR += color.red() * kernel[i][j];
			returnG += color.green() * kernel[i][j];
			returnB += color.blue() * kernel[i][j];
		}
	}
	return QColor(clamp(returnR, 0.f, 255.f), clamp(returnG, 0.f, 255.f), clamp(returnB, 0.f, 255.f));
}

void BlurKernel(char* fn)
{
	ofstream ostr(fn);
	ostr << SizeB << endl;
	float b = 1.f / (SizeB * SizeB);
	for (int i = 0; i < SizeB; i++)
	{
		for (int j = 0; j < SizeB; j++)
		{
			ostr << b << ' ';
		}
		ostr << endl;
	}
}

void GaussianKernel(char* fn)
{
	ofstream ostr(fn);
	ostr << SizeG << endl;
	float** m = new float* [SizeG];
	float norm = 0;
	for (int i = 0; i < SizeG; i++)
	{
		m[i] = new float[SizeG];
		for (int j = 0; j < SizeG; j++)
		{
			int t = SizeG / 2;
			m[i][j] = exp(-(i - t * i - t + j - t * j - t) / (2 * sigma * sigma));
			norm += m[i][j];
		}
	}

	for (int i = 0; i < SizeG; i++)
	{
		for (int j = 0; j < SizeG; j++)
		{
			if (norm != 0)
				m[i][j] /= norm;
			ostr << m[i][j] << " ";
		}
		ostr << endl;
	}
}

QColor Dilation::calcNewPixelColor(const QImage& photo, int x, int y)
{
	int MaxR = 0;
	int MaxG = 0;
	int MaxB = 0;
	int X = clamp(x - kernelSize / 2, 0, photo.width() - 1);
	int Y = clamp(y - kernelSize / 2, 0, photo.height() - 1);
	for (int i = 0; i < kernelSize; i++)
	{
		for (int j = 0; j < kernelSize; j++)
		{
			QColor color = photo.pixelColor(clamp(x - kernelSize / 2 + j, 0, photo.width() - 1), clamp(y - kernelSize / 2 + i, 0, photo.height() - 1));
			if (color.red() > MaxR)
				MaxR = color.red();
			if (color.green() > MaxG)
				MaxG = color.green();
			if (color.blue() > MaxB)
				MaxB = color.blue();
		}
	}
	QColor color = photo.pixelColor(x, y);
	color.setRgb(MaxR, MaxG, MaxB);
	return color;
}

QColor Erosion::calcNewPixelColor(const QImage& photo, int x, int y)
{
	int MinR = 255;
	int MinG = 255;
	int MinB = 255;
	int X = clamp(x - kernelSize / 2, 0, photo.width() - 1);
	int Y = clamp(y - kernelSize / 2, 0, photo.height() - 1);
	for (int i = 0; i < kernelSize; i++)
	{
		for (int j = 0; j < kernelSize; j++)
		{
			QColor color = photo.pixelColor(clamp(x - kernelSize / 2 + j, 0, photo.width() - 1), clamp(y - kernelSize / 2 + i, 0, photo.height() - 1));
			if (color.red() < MinR)
				MinR = color.red();
			if (color.green() < MinG)
				MinG = color.green();
			if (color.blue() < MinB)
				MinB = color.blue();
		}
	}
	QColor color = photo.pixelColor(x, y);
	color.setRgb(MinR, MinG, MinB);
	return color;
}

QColor Grad::calcNewPixelColor(const QImage& photo, int x, int y)
{
	int MaxR = 0;
	int MaxG = 0;
	int MaxB = 0;
	int MinR = 255;
	int MinG = 255;
	int MinB = 255;
	int X = clamp(x - kernelSize / 2, 0, photo.width() - 1);
	int Y = clamp(y - kernelSize / 2, 0, photo.height() - 1);
	for (int i = 0; i < kernelSize; i++)
	{
		for (int j = 0; j < kernelSize; j++)
		{
			QColor color = photo.pixelColor(clamp(x - kernelSize / 2 + j, 0, photo.width() - 1), clamp(y - kernelSize / 2 + i, 0, photo.height() - 1));
			if (color.red() > MaxR)
				MaxR = color.red();
			if (color.green() > MaxG)
				MaxG = color.green();
			if (color.blue() > MaxB)
				MaxB = color.blue();
			if (color.red() < MinR)
				MinR = color.red();
			if (color.green() < MinG)
				MinG = color.green();
			if (color.blue() < MinB)
				MinB = color.blue();
		
		}
	}
	QColor color = photo.pixelColor(x, y);
	color.setRgb(255-(MaxR-MinR), 255-(MaxG- MinG), 255-(MaxB-MinB));
	return color;
}

MatrixFilterTwoKernels::MatrixFilterTwoKernels(char* fnX, char* fnY)
{
	char buff[MaxLength];
	ifstream istrX(fnX), istrY(fnY);
	istrX.getline(buff, MaxLength, '\n');
	istrY.getline(buff, MaxLength, '\n');
	kernelSize = buff[0] - '0';
	kernelX = new float* [kernelSize];
	kernelY = new float* [kernelSize];
	float normX = 0, normY = 0;
	for (int i = 0; i < kernelSize; i++)
	{
		kernelX[i] = new float[kernelSize];
		kernelY[i] = new float[kernelSize];
		for (int j = 0; j < kernelSize; j++)
		{
			istrX.getline(buff, MaxLength, ' ');
			kernelX[i][j] = atof(buff);
			istrY.getline(buff, MaxLength, ' ');
			kernelY[i][j] = atof(buff);
			normX += kernelX[i][j];
			normY += kernelY[i][j];
		}
	}
	if ((normX && normX != 1) || (normY && normY != 1))
	{
		for (int i = 0; i < kernelSize; i++)
		{
			for (int j = 0; j < kernelSize; j++)
			{
				if (normX)
					kernelX[i][j] /= normX;
				if (normY)
					kernelY[i][j] /= normY;
			}
		}
	}
}

MatrixFilterTwoKernels::~MatrixFilterTwoKernels()
{
	for (int i = 0; i < kernelSize; i++)
	{
		delete[]kernelX[i];
		delete[]kernelY[i];
	}
	delete[] kernelX;
	delete[] kernelY;
}

QColor MatrixFilterTwoKernels::calcNewPixelColor(const QImage& photo, int x, int y) 
{
	float returnRX = 0;
	float returnGX = 0;
	float returnBX = 0;
	float returnRY = 0;
	float returnGY = 0;
	float returnBY = 0;
	int X = clamp(x - kernelSize /2, 0, photo.width() - 1);
	int Y = clamp(y - kernelSize /2, 0, photo.height() - 1);
	for (int i = 0; i < kernelSize; i++)
	{
		for (int j = 0; j < kernelSize; j++)
		{
			QColor color = photo.pixelColor(clamp(x - kernelSize / 2 + j, 0, photo.width() - 1), clamp(y - kernelSize + i / 2 + i, 0, photo.height() - 1));
			returnRX += color.red() * kernelX[i][j];
			returnGX += color.green() * kernelX[i][j];
			returnBX += color.blue() * kernelX[i][j];
			returnRY += color.red() * kernelY[i][j];
			returnGY += color.green() * kernelY[i][j];
			returnBY += color.blue() * kernelY[i][j];
		}
	}
	QColor color;
	color.setRgb(clamp(sqrt(returnRX * returnRX + returnRY * returnRY), 0.f, 255.f), clamp(sqrt(returnGX * returnGX + returnGY * returnGY), 0.f, 255.f), clamp(sqrt(returnBX * returnBX + returnBY * returnBY), 0.f, 255.f));
	return color;
}
