#ifndef UTILFUNCS_H
#define UTILFUNCS_H

#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> matrix;

void printMatrix(matrix mat) {
    #pragma omp parallel for
    for (const auto& row : mat) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

matrix randomImage(int height, int width) {
    matrix image(height, std::vector<int>(width, 0));

    #pragma omp parallel for
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int num = static_cast<int>(rand() % 256);
            image[i][j] = num;
        }
    }
    return image;
}


#endif