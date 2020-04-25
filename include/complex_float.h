#ifndef HEADER_COMPLEX
#define HEADER_COMPLEX

typedef struct {
    float real;
    float imag;
} complex;

#define cmr(x,y) (((x).real * (y).real - (x).imag * (y).imag))
#define cmi(x,y) (((x).real * (y).imag + (x).imag * (y).real))
#define cmul(x,y,u) (u).real = cmr((x),(y)); (u).imag = cmi((x),(y));
#define csum(x,y,u) (u).real = (x).real + (y).real; (u).imag = (x).imag + (y).imag;
#define csub(x,y,u) (u).real = (x).real - (y).real; (u).imag = (x).imag - (y).imag;

#define PI 3.14159265358979323846264338327950288

#endif