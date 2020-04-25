#ifndef HEADER_MFCC
#define HEADER_MFCC

#include "r4_fft.h"

// Número de coeficientes a serem calculados
#define MFCC_N 40

// Fator de escala que faz com que para o último coeficiente de mel tenhamos metade da frequência de amostragem
#define MFCC_FACTOR 2595*log10(1+(double)(SAMPLES_RATE/2)/700)/MFCC_N

// Pega um inteiro do coeficiente de mel e converte para a frequência (Hz) equivalente
#define MFCC_F(m) 700*(pow(10, (double)(m)*(MFCC_FACTOR)/2595)-1)

// Pega um inteiro e converte para a frequência (Hz) equivalente no espaço contínuo
#define MFCC_FREQ(k) ((double)(k)*SAMPLES_RATE/SAMPLES_SIZE)

// Pega uma frequência (Hz) e converte para o inteiro equivalente no espaço discretizado
#define MFCC_K(f) ((double)(f)*SAMPLES_SIZE/SAMPLES_RATE)

void mfcc(float *, float *);

#endif