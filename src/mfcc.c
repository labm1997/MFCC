#include "mfcc.h"

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
