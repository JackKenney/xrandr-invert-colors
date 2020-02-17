#include "stdint.h"
#include "invert_gamma_ramps.h"
#include "hsv_conversion.h"


double IntToDouble(uint16_t d)
{
    return (double)d;
}
uint16_t DoubleToInt(double d)
{
    return (uint16_t)d;
}

static uint16_t Min(uint16_t a, uint16_t b)
{
    return a <= b ? a : b;
}

static uint16_t Max(uint16_t a, uint16_t b)
{
    return a > b ? a : b;
}

void vibrance_shift(uint16_t *r, uint16_t *g, uint16_t *b, int ramp_size) {
    for (int i = 0; i < ramp_size; i++)
    {
        struct RGB rgb;
        rgb.R = IntToDouble(r[i]);
        rgb.G = IntToDouble(g[i]);
        rgb.B = IntToDouble(b[i]);
        struct HSV hsv = RGBToHSV(rgb);
        // invert vibrance:
        hsv.V = 1.0 - hsv.V;
        // convert and reassign
        rgb = HSVToRGB(hsv);
        r[i] = DoubleToInt(rgb.R);
        g[i] = DoubleToInt(rgb.G);
        b[i] = DoubleToInt(rgb.B);
    }
}

void shift_color(uint16_t *r, uint16_t *g, uint16_t *b, int ramp_size)
{
    for (int i = 0; i < ramp_size; i++)
    {
        uint16_t shift = 65535 - Min(r[i], Min(g[i], b[i])) - Max(r[i], Max(g[i], b[i]));
        r[i] = shift;
        g[i] = shift;
        b[i] = shift;
    }
}

void flip_gamma(uint16_t *r, uint16_t *g, uint16_t *b, int ramp_size)
{
    for (int i = 0; i <= (int)(ramp_size / 2); i++)
    {
        r[ramp_size - i] = r[i];
        g[ramp_size - i] = g[i];
        b[ramp_size - i] = b[i];
    }
}

const uint16_t I_MAX = (uint16_t)65536;

void undo_inversion(uint16_t *r, uint16_t *g, uint16_t *b, int ramp_size) {
    for (int i = 0; i < ramp_size; i++)
    {
        r[i] = I_MAX - r[i];
        g[i] = I_MAX - g[i];
        b[i] = I_MAX - b[i];
    }
}
