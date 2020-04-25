#ifndef HEADER_R4_FFT
#define HEADER_R4_FFT

#include <stdint.h>
#include <math.h>
#include "complex_float.h"

#define SAMPLES_SIZE 1024
#define SAMPLES_RATE 4000
#define HALVES_SIZE(N) ((N)-1)/3
#define bit(N,i) ((N) & (1 << (i)))

void r4_fft(complex *);
void r4_fft_mag2(complex *, float *);

#endif