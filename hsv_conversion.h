#include "stdint.h"

struct RGB
{
    double R;
    double G;
    double B;
};

struct HSV
{
    double H;
    double S;
    double V;
};

struct HSV RGBToHSV(struct RGB rgb);
struct RGB HSVToRGB(struct HSV hsv);
