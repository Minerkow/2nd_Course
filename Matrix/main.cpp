#include <iostream>
#include "Matrix.hpp"

int main() {
    size_t n;
    std::cin >> n;
    mtrx::Matrix_t<double> matrix{n, n};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double input = 0.0;
            std::cin >> input;
            matrix[i][j] = input;
        }
    }
    std::cout << matrix.Determinant();
    return 0;
}
