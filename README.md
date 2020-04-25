# MFCC
Implementação do MFCC, Mel Frequency Cepstral Coefficients em C

# Compilação
Para compilar rode `gcc src/main.c lib/r4_fft.o -o mfcc -O3 -lm`. Note que é necessário ter `r4_fft.o` pré-compilado que pode ser compilado de https://github.com/labm1997/FFT-Radix4