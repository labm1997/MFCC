#include <stdint.h>
#include <stdio.h>
#include "r4_fft.h"
#include "mfcc.h"

void init_samples(complex *samples){
    for(uint16_t i=0; i<SAMPLES_SIZE ; i++){
        double t = ((double)i/SAMPLES_RATE);
        // samples[i].real = cos(2*PI*t*1)+2*cos(2*PI*t*10)+3*cos(2*PI*t*20)+3*cos(2*PI*t*30)+2*cos(2*PI*t*40)+cos(2*PI*t*50);
        // samples[i].imag = 0;
        samples[i].real = 3*cos(2*PI*t*1000);
        samples[i].imag = 0;
        // samples[i].real = (i%64 > 32) ? 1 : -1;
        // samples[i].imag = 0;
    }
}

int main(){
    complex samples[SAMPLES_SIZE];
    float mag[SAMPLES_SIZE/2];
    float mfccs[MFCC_N];
    init_samples(samples);
    r4_fft_mag2(samples, mag);
    mfcc(mag, mfccs);
    for(uint16_t i=1 ; i<MFCC_N ; i++){
        printf("%lf\n", mfccs[i]);
    }
    return 0;
}