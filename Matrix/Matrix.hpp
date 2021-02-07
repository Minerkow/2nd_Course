#pragma once

#include <vector>
#include <iostream>
#include <future>
#include <exception>
#include <cmath>
#include <cassert>

namespace mtrx {

    const double PRESISION = 0.00001;

    enum {NUM_ELEM_SMALL_MATRIX = 10000};

    template <typename T>
    struct ProxyRow_t {
        T* row_;
        size_t len_;
        const T& operator[](const size_t index) const;
        T& operator[](const size_t index);
        T* operator*() {return row_;}
    };

    template<typename T>
    class Matrix_t {
    public:
        using rows_t = std::vector<T>;

        Matrix_t() : data_(nullptr), rows_(nullptr),
                     numRows_(0), numColumns_(0) {}
        Matrix_t(size_t numRows, size_t numColumns);

        template<typename T2>
        Matrix_t(const Matrix_t<T2>& matrix);

        Matrix_t(const Matrix_t<T>& matrix);


        Matrix_t(size_t size) : Matrix_t{size, size} {}
        explicit Matrix_t(const std::vector<rows_t>& rows);

        size_t Num_Rows() const {return numRows_;}
        size_t Num_Columns() const {return numColumns_;}

        Matrix_t<T> Transposition();

        double Determinant();
        double Determinant2();

        Matrix_t<T> Matrix_Mult(Matrix_t<T>& other);

        void Swap_Rows(size_t rowNum1, size_t rowNum2);

        Matrix_t<T>& operator=(const Matrix_t<T>& rhs) ;
        Matrix_t<T>& operator+=(const Matrix_t<T>& rhs);
        Matrix_t<T> operator-();

        template<typename coefficientT>
        Matrix_t<T>& operator*=(coefficientT coeff);

        ProxyRow_t<T>& operator[](const size_t index);
        const ProxyRow_t<T>& operator[](const size_t index) const;

        bool empty();

        Matrix_t<T> Add_Column(Matrix_t<T>& column);

        ~Matrix_t();
    private:
        T* data_;
        ProxyRow_t<T>* rows_;
        size_t numRows_;
        size_t numColumns_;
    };

    template <typename T>
    bool operator==(const Matrix_t<T>& lhs, const Matrix_t<T>& rhs);

    template<typename T, typename coefficientT>
    Matrix_t<T> operator*(coefficientT coeff, const Matrix_t<T>& matrix);

    template <typename T>
    std::ostream& operator<<(std::ostream& os, Matrix_t<T>& matrix);

    template<typename first, typename second>
    std::ostream& operator<<(std::ostream& os, std::pair<first, second> pair);

    template <typename first, typename second>
    std::ostream& operator<<(std::ostream& os, std::vector<std::pair<first, second>> vec);

    template<typename T>
    Matrix_t<T> operator+(Matrix_t<T>& lhs, Matrix_t<T>& rhs);

    bool Double_Equal(double rhs, double lhs);

    template <typename T>
    Matrix_t<T> IdentityMatrix(size_t size);
    }

//--------------------------------------------------------------------------------------------------------------------

namespace mtrx {
    template<typename T>
    Matrix_t<T>::Matrix_t(size_t numRows, size_t numColumns) : numColumns_(numColumns),
                                                               numRows_(numRows)
    {
        data_ = new T[numRows * numColumns]{};
        T* beginRow = data_;
        rows_ = new ProxyRow_t<T>[numRows];
        for (int i = 0; i < numRows; ++i) {
            rows_[i].row_ = beginRow;
            rows_[i].len_ = numColumns;
            beginRow += numColumns;
        }
    }


    template<typename T>
    Matrix_t<T> Matrix_t<T>::Transposition() {
        Matrix_t<T> res{numColumns_, numRows_};
        for (size_t row = 0; row < res.numRows_; ++row) {
            for (size_t column = 0; column < res.numColumns_; ++column) {
                res[row][column] = rows_[column][row];
            }
        }
        return res;
    }

    template<typename T>
    double Matrix_t<T>::Determinant2() {
        if (numColumns_ != numRows_) {
            return 0;
        }

        double det = 1.0;

        if (rows_[0][0] == 0) {
            return 0.0;
        }

        size_t n = numRows_;
        Matrix_t<double> LU_Matrix{n, n};
        for (size_t j = 0; j < n; ++j) {
            LU_Matrix[0][j] = static_cast<double>(rows_[0][j]);
            if (j == 0) {
                LU_Matrix[j][0] *= static_cast<double>(rows_[j][0]) / LU_Matrix[0][0];
            } else {
                LU_Matrix[j][0] = static_cast<double>(rows_[j][0]) / LU_Matrix[0][0];
            }
        }


        for (size_t i = 1; i < n; ++i) {
            for (size_t j = i; j < n; ++j) {
                double sum = 0.0;
                for (size_t k = 0; k <= i - 1; ++k) {
                    sum += LU_Matrix[i][k] * LU_Matrix[k][j];
                }


                LU_Matrix[i][j] = static_cast<double>(rows_[i][j]) - sum;

                sum = 0.0;
                for (size_t k = 0; k <= i - 1; ++k) {
                    sum += LU_Matrix[j][k] * LU_Matrix[k][i];
                }

                if (j == i) {
                    LU_Matrix[j][i] *= 1 / LU_Matrix[i][i] * (static_cast<double>(rows_[j][i]) - sum);
                } else {
                    LU_Matrix[j][i] = 1 / LU_Matrix[i][i] * (static_cast<double>(rows_[j][i]) - sum);
                }
            }
        }

        std::cout << "LU:" << LU_Matrix << std::endl;

        for (size_t i = 0; i < n; ++i){
            det *= LU_Matrix[i][i];
        }
        if (std::isnan(det)) {
            return 0;
        }
        return det;
    }

    template <typename T>
    double Matrix_t<T>::Determinant() {
        if (numRows_ != numColumns_) {
            return 0.0;
        }
        double det = 1.0;
        const size_t n = numRows_;
        Matrix_t<double> C(*this);

        std::vector<size_t> P;
        for (size_t i = 0; i < n; ++i) {
            P.push_back(i);
        }

        for( size_t i = 0; i < n; i++ ) {
            double pivotValue = 0.0;
            int pivot = -1;
            for( size_t row = i; row < n; ++row ) {
                if( fabs(C[row][i]) > pivotValue ) {
                    pivotValue = fabs(C[row][i]);
                    pivot = row;
                }
            }



            if(pivot != i && !Double_Equal(pivotValue, 0.0)) {
                size_t  tmp = P[i];
                P[i] = P[pivot];
                P[pivot] = tmp;
                det *= -1;

                C.Swap_Rows(i, pivot);
                P[n]++;
            }

            for(int j = i + 1; j < n; ++j) {
                C[j][i] /= C[i][i];

                for (int k = i + 1; k < n; ++k) {
                    C[j][k] -= C[j][i] * C[i][k];
                }
            }
        }

        for (size_t i = 0; i < n; ++i) {
            det *= C[i][i];
        }
        if (std::isnan(det)) {
            return 0.0;
        }
        return det;
    }

    template<typename T>
    Matrix_t<T> Matrix_t<T>::Matrix_Mult(Matrix_t<T> &other) {
        if (other.numRows_ != numColumns_) {
            std::cerr << "Matrix_Mult ERROR!\n";
            exit(EXIT_FAILURE);
        }

        /* [m*n] * [n*k] = [m*k] */

        Matrix_t<T> res{numRows_, other.numColumns_};
            Matrix_t<T> othT = other.Transposition();
            for (size_t m = 0; m < numRows_; ++m) {
                const ProxyRow_t<T>& row = rows_[m];
                for (size_t k = 0; k < othT.numRows_; ++k) {
                    for (size_t n = 0; n < othT.numColumns_; ++n) {
                        res[m][k] += row[n] * othT[k][n];
                    }
                }
            }
            return res;
    }

    template<typename T>
    Matrix_t<T>::Matrix_t(const std::vector<rows_t>& rows) : Matrix_t{rows.size(), rows.data()->size()}
    {
        for (size_t row = 0; row < numRows_; ++row) {
            if (rows[row].size() != numColumns_) {
                std::cerr << "Error construct Matrix -" << rows[row].size() << " != " << numColumns_;
                exit(EXIT_FAILURE);
            }
            for(int column = 0; column < numColumns_; ++column) {
                rows_[row][column] = rows[row][column];
            }
        }
    }

    template<typename T>
    Matrix_t<T>::~Matrix_t() {
        delete [] rows_;
        delete [] data_;
    }

    template<typename T>
    ProxyRow_t<T>& Matrix_t<T>::operator[](const size_t index) {
        if (index >= numRows_) {
            std::cerr << "Sigm error Matrix!\n";
            exit(EXIT_FAILURE);
        }
        return rows_[index];
    }

    template<typename T>
    const ProxyRow_t<T>& Matrix_t<T>::operator[](const size_t index) const {
        if (index >= numRows_) {
            std::cerr << "Sigm error Matrix!\n";
            exit(EXIT_FAILURE);
        }
        return rows_[index];
    }

    template<typename T>
    Matrix_t<T> &Matrix_t<T>::operator+=(const Matrix_t<T> &rhs) {
        if (rhs.numColumns_ != numColumns_ ||
            rhs.numRows_ != numRows_) {
            std::cerr << "Error matrix SUM!\n";
            exit(EXIT_FAILURE);
        }
        for (size_t row = 0; row < numRows_; ++row) {
            for (size_t column = 0; column < numColumns_; ++column) {
                rows_[row][column] += rhs[row][column];
            }
        }
        return *this;
    }

    template<typename T>
    template<typename coefficientT>
    Matrix_t<T> &Matrix_t<T>::operator*=(coefficientT coeff) {
        for (size_t row = 0; row < numRows_; ++row) {
            for (size_t column = 0; column < numColumns_; ++column) {
                rows_[row][column] *= coeff;
            }
        }
        return *this;
    }

    template<typename T>
    Matrix_t<T> &Matrix_t<T>::operator=(const Matrix_t<T> &rhs) {
        if (&rhs == this) {
            return *this;
        }

        delete [] data_;
        delete [] rows_;
        numRows_ = rhs.numRows_;
        numColumns_ = rhs.numColumns_;
        data_ = new T[numRows_ * numColumns_]{};
        T* beginRow = data_;
        rows_ = new ProxyRow_t<T>[numRows_];
        for (int i = 0; i < numRows_; ++i) {
            rows_[i].row_ = beginRow;
            rows_[i].len_ = numColumns_;
            beginRow += numColumns_;
        }
        for (size_t i = 0; i < numColumns_*numRows_; ++i) {
            data_[i] = rhs.data_[i];
        }
        return *this;
    }

    template<typename T>
    void Matrix_t<T>::Swap_Rows(size_t rowNum1, size_t rowNum2) {
        T* tmp = rows_[rowNum1].row_;
        rows_[rowNum1].row_ = rows_[rowNum2].row_;
        rows_[rowNum2].row_ = tmp;
    }

    template<typename T>
    template<typename T2>
    Matrix_t<T>::Matrix_t(const Matrix_t<T2> &matrix) : Matrix_t{matrix.Num_Rows(), matrix.Num_Columns()} {
            for (size_t i = 0; i < numRows_; ++i) {
                for (size_t j = 0; j < numColumns_; ++j) {
                    rows_[i][j] = static_cast<T>(matrix[i][j]);
                }
            }
    }

    template<typename T>
    bool Matrix_t<T>::empty() {
        return numColumns_ == 0 && numRows_ == 0;
    }

    template<typename T>
    Matrix_t<T> Matrix_t<T>::Add_Column(Matrix_t<T> &column) {
        if (numRows_ != column.numRows_ && !column.empty()) {
            //TODO::error
        }
        Matrix_t<T> res{numRows_, numColumns_ + column.numColumns_};

        for (size_t i = 0; i < res.Num_Rows(); ++i) {
            for (size_t j = 0; j < numColumns_; ++j) {
                res[i][j] = rows_[i][j];
            }
            for (size_t j = 0; j < column.Num_Columns(); ++j) {
                res[i][numColumns_ + j] = column[i][j];
            }
        }
        return res;
    }

    template<typename T>
    Matrix_t<T> Matrix_t<T>::operator-() {
        Matrix_t<T> res(*this);
        for (size_t i = 0; i < res.Num_Rows(); ++i) {
            for(size_t j = 0; j < res.Num_Columns(); ++j) {
                res[i][j] *= -1;
            }
        }
        return res;
    }

    template<typename T>
    Matrix_t<T>::Matrix_t(const Matrix_t<T> &matrix) : Matrix_t{matrix.Num_Rows(), matrix.Num_Columns()} {
        for (size_t i = 0; i < numRows_; ++i) {
            for (size_t j = 0; j < numColumns_; ++j) {
                rows_[i][j] = static_cast<T>(matrix[i][j]);
            }
        }
    }


    template <typename T>
    bool operator==(const Matrix_t<T>& lhs, const Matrix_t<T>& rhs)  {
        if (rhs.Num_Rows() != lhs.Num_Rows() ||
            rhs.Num_Columns() != lhs.Num_Columns()) {
            return false;
        }
        for (int i = 0; i < rhs.Num_Rows(); ++i) {
            for (int j = 0; j < rhs.Num_Columns(); ++j) {
                if (!Double_Equal(rhs[i][j], lhs[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    template<typename T, typename coefficientT>
    Matrix_t<T> operator*(coefficientT coeff, const Matrix_t<T>& matrix) {
        Matrix_t<T> res{matrix.Num_Rows(), matrix.Num_Columns()};
        for (int row = 0; row < matrix.Num_Rows(); ++row) {
            for (int column = 0; column < matrix.Num_Columns(); ++column) {
                res[row][column] = matrix[row][column] * static_cast<T>(coeff);
            }
        }
        return res;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, Matrix_t<T>& matrix) {
        for (size_t row = 0; row < matrix.Num_Rows(); ++row) {
            //os << "( ";
            for (size_t column = 0; column < matrix.Num_Columns(); ++column) {
                os << matrix[row][column] << " ";
            }
            os << "\n";
        }
        return os;
    }

    template<typename T, typename coefficientT>
    Matrix_t<T> operator*( const Matrix_t<T>& matrix, coefficientT coeff) {
        return coeff*matrix;
    }

    template<typename T>
    Matrix_t<T> operator+(Matrix_t<T>& lhs, Matrix_t<T>& rhs) {
        if (lhs.Num_Columns() != rhs.Num_Columns() ||
            lhs.Num_Rows() != rhs.Num_Rows()) {
            std::cerr << "Matrices of different sizes!\n";
            exit(EXIT_FAILURE);
        }
        Matrix_t<T> res{lhs.Num_Rows(), lhs.Num_Columns()};
        for (size_t row = 0; row < lhs.Num_Rows(); ++row) {
            for (size_t column = 0; column < lhs.Num_Columns(); ++column) {
                res[row][column] = lhs[row][column] + rhs[row][column];
            }
        }
        return res;
    }

    bool Double_Equal(double rhs, double lhs) {
        if (std::abs(rhs - lhs) < PRESISION) {
            return true;
        } else {
            return false;
        }
    }

    template<typename T>
    const T &ProxyRow_t<T>::operator[](const size_t index) const {
        if (index > len_) {
            std::cerr << "Sigabrt error\n";
            exit(EXIT_FAILURE);
        }
        return row_[index];
    }

    template<typename T>
    T &ProxyRow_t<T>::operator[](const size_t index) {
        if (index > len_) {
            std::cerr << "Sigabrt error\n";
            exit(EXIT_FAILURE);
        }
        return row_[index];
    }

    template <typename T>
    Matrix_t<T> IdentityMatrix(size_t size) {
        Matrix_t<T> res{size};

        for (size_t i = 0; i < size; ++i) {
            res[i][i] = 1;
        }
        return res;
    }

    template<typename first, typename second>
    std::ostream& operator<<(std::ostream& os, std::pair<first, second> pair) {
        os << "[ " << pair.first << " " << pair.second << " ]";
        return os;
    }

    template <typename first, typename second>
    std::ostream& operator<<(std::ostream& os, std::vector<std::pair<first, second>> vec) {
        os << "{ ";
        for (auto& it : vec) {
            os << it << " ";
        }
        os << "}";
        return os;
    }
}