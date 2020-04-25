#include <stdint.h>
#include "r4_fft.h"

#define PI 3.14159265358979323846264338327950288

#define MFCC_N 40
#define SAMPLE_SIZE 1024
#define SAMPLE_RATE 4000

// Fator de escala que faz com que para o último coeficiente de mel tenhamos metade da frequência de amostragem
#define MFCC_FACTOR 2595*log10(1+(double)(SAMPLE_RATE/2)/700)/MFCC_N

// Pega um inteiro do coeficiente de mel e converte para a frequência (Hz) equivalente
#define MFCC_F(m) 700*(pow(10, (double)(m)*(MFCC_FACTOR)/2595)-1)

// Pega um inteiro e converte para a frequência (Hz) equivalente no espaço contínuo
#define MFCC_FREQ(k) ((double)(k)*SAMPLE_RATE/SAMPLE_SIZE)

// Pega uma frequência (Hz) e converte para o inteiro equivalente no espaço discretizado
#define MFCC_K(f) ((double)(f)*SAMPLE_SIZE/SAMPLE_RATE)

/*
 * Função que computa a MFCC do espectro de magnitude fft_magnitude
 */
void mfcc(float *fft_magnitude, float *mfcc){
    float filtered[MFCC_N] = {0};

    // Percorre o banco de filtros
    for(uint16_t l=1 ; l<MFCC_N ; l++){
        // Frequência inicial do filtro
        float fa = MFCC_F(l-1);

        // Frequência central do filtro
        float fb = MFCC_F(l);

        // Frequência final do filtro
        float fc = MFCC_F(l+1);

        // Valor do sinal de magnitude multiplicado pelo filtro
        float filterSum = 0;

        // Parte crescente do filtro
        for(uint16_t k=(uint16_t)ceil(MFCC_K(fa)) ; k<=(uint16_t)floor(MFCC_K(fb)) ; k++){
            filterSum += fft_magnitude[k] * (MFCC_FREQ(k) - fa) / (fb - fa);
        }
        
        // Parte decrescente do filtro
        for(uint16_t k=(uint16_t)ceil(MFCC_K(fb)) ; k<=(uint16_t)floor(MFCC_K(fc)) ; k++){
            filterSum += fft_magnitude[k] * (fc - MFCC_FREQ(k)) / (fc - fb);
        }
        filtered[l] = (filterSum != 0) ? log10(filterSum) : 0;
    }

    // DCT não otimizada
    for(uint16_t m=0 ; m<MFCC_N ; m++){
        mfcc[m] = 0;
        // m-esimo coeficiente
        for(uint16_t l=0 ; l<MFCC_N ; l++){
            mfcc[m] += filtered[l] * cos((double)m*PI/MFCC_N*(l+(double)0.5));
        }

        mfcc[m] *= (m == 0) ? sqrt((double)1/MFCC_N) : sqrt((double)2/MFCC_N);
    }
}

void init_samples(complex *samples){
    for(uint16_t i=0; i<SAMPLES_SIZE ; i++){
        double t = ((double)i/SAMPLE_RATE);
        // samples[i].real = cos(2*PI*t*1)+2*cos(2*PI*t*10)+3*cos(2*PI*t*20)+3*cos(2*PI*t*30)+2*cos(2*PI*t*40)+cos(2*PI*t*50);
        // samples[i].imag = 0;
        samples[i].real = 3*cos(2*PI*t*1000);
        samples[i].imag = 0;
        // samples[i].real = (i%64 > 32) ? 1 : -1;
        // samples[i].imag = 0;
    }
}

int main(){
    complex samples[SAMPLE_SIZE];
    float mag[SAMPLE_SIZE/2];
    float mfccs[MFCC_N];
    init_samples(samples);
    r4_fft_mag2(samples, mag);
    mfcc(mag, mfccs);
    for(uint16_t i=1 ; i<MFCC_N ; i++){
        printf("%lf\n", mfccs[i]);
    }
    return 0;
}