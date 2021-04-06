#include <QtCore/QCoreApplication>
#include "Filter.h"

void main(int argc, char* argv[])
{
    string s;
    QImage photo;

    for (int i = 0; i < argc; i++)
    {
        if (!std::strcmp(argv[i], "-p") && (i + 1 < argc))
        {
            s = argv[i + 1];
        }
    }

    photo.load(QString(s.c_str()));

    InvertFilter invert;
    invert.process(photo).save("Invert1.jpg");

    GreyScaleFilter GreyScale;
    GreyScale.process(photo).save("GreyScale.jpg");

    SepiaFilter sepia;
    sepia.process(photo).save("Sepia.jpg");

    IncreasedBrightnessFilter brightness;
    brightness.process(photo).save("IncreasedBrightness.jpg");

    IdealReflector ir;
    ir.process(photo).save("IdealReflecor.jpg");

    HorizontalWaves wave1;
    wave1.process(photo).save("HorizontalWaves.jpg");

    VerticalWaves wave2;
    wave2.process(photo).save("VerticalWaves.jpg");

    GlassEffect glassEffect;
    glassEffect.process(photo).save("GlassEffect.jpg");

    LinearStretching LS;
    LS.process(photo).save("LinearStretching.jpg");

    MedianFilter median;
    median.process(photo).save("MedianFilter.jpg");

    BlurKernel("Blur.txt");
    MatrixFilter blur("Blur.txt");
    blur.process(photo).save("Blur.jpg");

    GaussianKernel("Gauss.txt");
    MatrixFilter gauss("Gauss.txt");
    gauss.process(photo).save("Gauss.jpg");

    MatrixFilter sharpness("Sharpness.txt");
    sharpness.process(photo).save("Sharpness.jpg");

    Dilation dilation("DilationErosion.txt");
    QImage dil=dilation.process(photo);
    dil.save("Dilation.jpg");

    Erosion erosion("DilationErosion.txt");
    QImage eros=erosion.process(photo);
    eros.save("Erosion.jpg");

    dilation.process(eros).save("Opening.jpg");

    erosion.process(dil).save("Closing.jpg");

    Grad grad("DilationErosion.txt");
    grad.process(photo).save("Grad.jpg");

    MatrixFilterTwoKernels sobel("sobel_x.txt", "sobel_y.txt");
    sobel.process(photo).save("Sobel.jpg");

    MatrixFilterTwoKernels oper_sharr("oper_sharr_x.txt", "oper_sharr_y.txt");
    oper_sharr.process(photo).save("OperatorSharr.jpg");

}
