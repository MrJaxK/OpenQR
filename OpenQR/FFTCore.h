//
// Created by DxxK on 2017/11/21.
//

#ifndef OPENQR_FFTCORE_H
#define OPENQR_FFTCORE_H

#include <complex>
enum fourier_transform_direction { ftdFunctionToSpectrum, ftdSpectrumToFunction };

#define INCORRECT_SPECTRUM_SIZE_FOR_FFT 			1
#define UNSUPPORTED_FTD								2

void DiscreteFourierFast(const std::complex<double>* f, int i_max, std::complex<double>* F, fourier_transform_direction ftd);
void DiscreteFourierFast2D(const std::complex<double>* f, int i_max, int j_max, std::complex<double>* F, fourier_transform_direction ftd);
void FastFourierTransform(const std::complex<double>* input, int inputNumber, std::complex<double>* output, fourier_transform_direction ftd);
#endif //OPENQR_FFTCORE_H
