#include "hsv_conversion.h"
#include "stdint.h"
#include <math.h>

static double Min(double a, double b)
{
    return a <= b ? a : b;
}

static double Max(double a, double b)
{
    return a > b ? a : b;
}

struct HSV RGBToHSV(struct RGB rgb)
{
    double delta, min;
    double h = 0, s, v;

    min = Min(Min(rgb.R, rgb.G), rgb.B);
    v = Max(Max(rgb.R, rgb.G), rgb.B);
    delta = v - min;

    if (v == 0.0)
        s = 0;
    else
        s = delta / v;

    if (s == 0)
        h = 0.0;

    else
    {
        if (rgb.R == v)
            h = (rgb.G - rgb.B) / delta;
        else if (rgb.G == v)
            h = 2 + (rgb.B - rgb.R) / delta;
        else if (rgb.B == v)
            h = 4 + (rgb.R - rgb.G) / delta;

        h *= 60;

        if (h < 0.0)
            h = h + 360;
    }

    struct HSV hsv;
    hsv.H = h;
    hsv.S = s;
    hsv.V = v / 255;

    return hsv;
}

struct RGB HSVToRGB(struct HSV hsv)
{
    double r = 0, g = 0, b = 0;

    if (hsv.S == 0)
    {
        r = hsv.V;
        g = hsv.V;
        b = hsv.V;
    }
    else
    {
        int i;
        double f, p, q, t;

        if (hsv.H == 360)
            hsv.H = 0;
        else
            hsv.H = hsv.H / 60;

        i = (int)trunc(hsv.H);
        f = hsv.H - i;

        p = hsv.V * (1.0 - hsv.S);
        q = hsv.V * (1.0 - (hsv.S * f));
        t = hsv.V * (1.0 - (hsv.S * (1.0 - f)));

        switch (i)
        {
        case 0:
            r = hsv.V;
            g = t;
            b = p;
            break;

        case 1:
            r = q;
            g = hsv.V;
            b = p;
            break;

        case 2:
            r = p;
            g = hsv.V;
            b = t;
            break;

        case 3:
            r = p;
            g = q;
            b = hsv.V;
            break;

        case 4:
            r = t;
            g = p;
            b = hsv.V;
            break;

        default:
            r = hsv.V;
            g = p;
            b = q;
            break;
        }
    }

    struct RGB rgb;
    rgb.R = r / 255;
    rgb.G = g / 255;
    rgb.B = b / 255;

    return rgb;
}
