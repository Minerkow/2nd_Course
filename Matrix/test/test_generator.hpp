#include "../Matrix.hpp"
#include <random>

namespace matrixgen {

    enum {MAX_VALUE_L = 1, MAX_VALUE_U = 2};
    class MatrixGenerator_t {
    public:
        MatrixGenerator_t(size_t size);

        friend std::ostream& operator<<(std::ostream& os, MatrixGenerator_t& matrixGenerator);

        mtrx::Matrix_t<int> matrix_;
        double determinant_;
    };

    MatrixGenerator_t::MatrixGenerator_t(size_t size) {
        mtrx::Matrix_t<int> L{size, size};
        mtrx::Matrix_t<int> U{size, size};
        std::random_device rd;
        std::mt19937 mersenne(rd());
        double detL = 1.0;
        for (size_t n = 0; n < L.Num_Rows(); ++n) {
            for (size_t m = n; m < L.Num_Columns(); ++m) {
                L[n][m] = mersenne() % MAX_VALUE_L + 1;
                if (n == m) {
                    L[n][m] = mersenne() % MAX_VALUE_L + 1;
                    detL *= L[n][m];
                }
            }
        }

        for (size_t n = 0; n < L.Num_Rows(); ++n) {
            for (size_t m = 0; m <= n; ++m) {
                U[n][m] = mersenne() % MAX_VALUE_U;
                if (n == m) {
                    U[n][m] = 1.0;
                }
            }
        }

        matrix_ = L.Matrix_Mult(U);

        determinant_ = detL;
    }

    std::ostream &operator<<(std::ostream &os, MatrixGenerator_t &matrixGenerator) {
        os << matrixGenerator.matrix_;
        return os;
    }

}
