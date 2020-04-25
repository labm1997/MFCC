#include "r4_fft.h"
#include "r4_halves.h"

/*
 * Faz a inversão de bits radix-4 do valor de 10 bits passado
 */
uint16_t r4_bit_reverse_1024(uint16_t index){
    return bit(index, 8) >> 8 |
           bit(index, 9) >> 8 | 
           bit(index, 6) >> 4 |
           bit(index, 7) >> 4 | 
           bit(index, 4) >> 0 | 
           bit(index, 5) >> 0 |
           bit(index, 2) << 4 | 
           bit(index, 3) << 4 | 
           bit(index, 0) << 8 |
           bit(index, 1) << 8;
}

/*
 * Copia um array input para a output mudando a ordem usando o bitreverse radix-4
 */
void r4_bit_reverse_1024_copy(complex *input, complex *output){
    for(uint16_t i=0 ; i<SAMPLES_SIZE ; i++){
        output[r4_bit_reverse_1024(i)] = input[i];
    }
}

/*
 * Computa a fft de input em output usando o algorítmo de fft radix-4
 */
void r4_fft(complex *input, complex *output){
    r4_bit_reverse_1024_copy(input, output);

    // Representa a altura na árvore de recursão, começando por baixo em N=4
    for(uint16_t N=4 ; N<=SAMPLES_SIZE ; N *= 4){
        // Posição inicial nos halves
        uint16_t p = (N/4-1)/3;

        // k máximo desse nível
        uint16_t Kmax = N/4;

        // Representa o índice inicial do superarray
        for(uint16_t s=0 ; s<SAMPLES_SIZE ; s+=N){
            
            // Preenche o superarray com o subarray
            for(uint16_t k=0 ; k<Kmax ; k++){
                // Elementos do subarray
                complex m0 = output[s+0*Kmax+k];
                complex m1 = output[s+1*Kmax+k];
                complex m2 = output[s+2*Kmax+k];
                complex m3 = output[s+3*Kmax+k];

                // Exponenciais complexas
                complex h1 = r4_fft_h1[p+k];
                complex h2 = r4_fft_h2[p+k];
                complex h3 = r4_fft_h3[p+k];

                // Contas
                float m1r = m1.real * h1.real - m1.imag * h1.imag;
                float m1i = m1.real * h1.imag + m1.imag * h1.real;

                float m2r = m2.real * h2.real - m2.imag * h2.imag;
                float m2i = m2.real * h2.imag + m2.imag * h2.real;

                float m3r = m3.real * h3.real - m3.imag * h3.imag;
                float m3i = m3.real * h3.imag + m3.imag * h3.real;

                output[s+0*Kmax+k].real = m0.real + m1r + m2r + m3r;
                output[s+0*Kmax+k].imag = m0.imag + m1i + m2i + m3i;

                output[s+1*Kmax+k].real = m0.real + m1i - m2r - m3i;
                output[s+1*Kmax+k].imag = m0.imag - m1r - m2i + m3r;

                output[s+2*Kmax+k].real = m0.real - m1r + m2r - m3r;
                output[s+2*Kmax+k].imag = m0.imag - m1i + m2i - m3i;

                output[s+3*Kmax+k].real = m0.real - m1i - m2r + m3i;
                output[s+3*Kmax+k].imag = m0.imag + m1r - m2i - m3r;

            }

        }

    }

}

/*
 * Computa o quadrado do espectro de magnitude de uma entrada.
 * @params signal: Tem tamanho SAMPLES_SIZE
 * @params magnitude: Tem tamanho SAMPLES_SIZE/2
 */
void r4_fft_mag2(complex *signal, float *magnitude){
    // Saída da FFT
    complex output[SAMPLES_SIZE];

    // Computa FFT
    r4_fft(signal, output);

    // Faz o computo da magnitude
    for(uint16_t i=0 ; i<SAMPLES_SIZE/2 ; i++){
        magnitude[i] = (output[i].real*output[i].real + output[i].imag*output[i].imag) / (SAMPLES_SIZE*SAMPLES_SIZE);
    }
}