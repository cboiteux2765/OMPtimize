#include <iostream>
#include <omp.h>
#include <vector>
#include <cmath>
#include "utilfuncs.h"

typedef std::vector<std::vector<int>> matrix;

#define MAX_ITERATIONS 1000
#define TOLERANCE 1e-6

// EXAMPLE
void jacobi_iteration(std::vector<double>& x, const matrix& A, 
                      const std::vector<double>& b) {
    int n = A.size();
    std::vector<double> x_new(n);

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += A[i][j] * x[j];
            }
        }
        x_new[i] = (b[i] - sum) / A[i][i];
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        x[i] = x_new[i];
    }
}

matrix convolution(matrix image, matrix kernel) {
    int imageHeight = image.size();
    int imageWidth = image[0].size();
    int kernelHeight = kernel.size();
    int kernelWidth = kernel[0].size();
    
    int outputHeight = imageHeight - kernelHeight + 1;
    int outputWidth = imageWidth - kernelWidth + 1;
    
    matrix output(outputHeight, std::vector<int>(outputWidth, 0));
    
    #pragma omp parallel for
    for (int i = 0; i < outputHeight; i++) {
        for (int j = 0; j < outputWidth; j++) {
            int sum = 0;
            for (int m = 0; m < kernelHeight; ++m) {
                for (int n = 0; n < kernelWidth; ++n) {
                    sum += image[i + m][j + n] * kernel[m][n];
                }
            }
            output[i][j] = sum;
        }
    }
    
    return output;
}