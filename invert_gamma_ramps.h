#include "stdint.h"

void shift_color(uint16_t* r, uint16_t* g, uint16_t* b, int ramp_size);
void vibrance_shift(uint16_t *r, uint16_t *g, uint16_t *b, int ramp_size);
void flip_gamma(uint16_t *r, uint16_t *g, uint16_t *b, int ramp_size);
void undo_inversion(uint16_t *r, uint16_t *g, uint16_t *b, int ramp_size);