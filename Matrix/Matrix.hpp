#pragma once

#include <vector>
#include <iostream>
#include <future>
#include <exception>

namespace mtrx {

    const double PRESISION = 0.00001;

    enum {NUM_ELEM_SMALL_MATRIX = 10000};

    template <typename T>
    struct ProxyRow_t {
        T* row_;
        size_t len_;
        const T& operator[](const size_t index) const;
        T& operator[](const size_t index);
    };

    template<typename T>
    class Matrix_t {
    public:
        using rows_t = std::vector<T>;

        Matrix_t() : data_(nullptr), rows_(nullptr),
                     numRows_(0), numColumns_(0) {}
        Matrix_t(size_t numRows, size_t numColumns);
        Matrix_t(const Matrix_t<T>& matrix);
        explicit Matrix_t(const std::vector<rows_t>& rows);

        size_t Num_Rows() const {return numRows_;}
        size_t Num_Columns() const {return numColumns_;}

        Matrix_t<T> Transposition();

        double Determinant();

        Matrix_t<T> Matrix_Mult(Matrix_t<T>& other);

        Matrix_t<T>& operator=(const Matrix_t<T>& rhs) = default;
        Matrix_t<T>& operator+=(const Matrix_t<T>& rhs);

        template<typename coefficientT>
        Matrix_t<T>& operator*=(coefficientT coeff);

        ProxyRow_t<T>& operator[](const size_t index);
        const ProxyRow_t<T>& operator[](const size_t index) const;

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

    template<typename T>
    Matrix_t<T> operator+(Matrix_t<T>& lhs, Matrix_t<T>& rhs);

    bool Double_Equal(double rhs, double lhs);
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
    double Matrix_t<T>::Determinant() {
        //TODO
    }

    template<typename T>
    Matrix_t<T> Matrix_t<T>::Matrix_Mult(Matrix_t<T> &other) {
        if (other.numRows_ != numColumns_) {
            std::cerr << "Matrix_Mult ERROR!\n";
            exit(EXIT_FAILURE);
        }

        /* [m*n] * [n*k] = [m*k] */

        Matrix_t<T> res{numRows_, other.numColumns_};
        if (other.numColumns_*other.numRows_ <= NUM_ELEM_SMALL_MATRIX) {
            Matrix_t<T> othT = other.Transposition();
            std::vector<std::future<void>> futures;
            for (size_t m = 0; m < numRows_; ++m) {
                const ProxyRow_t<T>& row = rows_[m];
                futures.push_back(std::async([&othT, m, &row, &res] {
                    for (size_t k = 0; k < othT.numRows_; ++k) {
                        for (size_t n = 0; n < othT.numColumns_; ++n) {
                            res[m][k] += row[n] * othT[k][n];
                        }
                    }
                }));
            }
            for (auto& it : futures) {
                it.get();
            }
            return res;
        }


        std::vector<std::future<void>> futures;
        for (size_t m = 0; m < numRows_; ++m) {
            const ProxyRow_t<T>& row = rows_[m];
            futures.push_back(std::async([&row, &other, &res, m] {
                for (size_t k = 0; k < other.numColumns_; ++k) {
                    for (size_t n = 0; n < other.numRows_; ++n) {
                        res[m][k] += row[n] * other[n][k];
                        double tmp = res[m][k];
                    }
                }
            }));
        }
        for (auto& it : futures) {
            it.get();
        }
        return res;
    }

    template<typename T>
    Matrix_t<T>::Matrix_t(const Matrix_t<T> &matrix) : Matrix_t{matrix.numRows_, matrix.numColumns_}
    {
        for (int i = 0; i < numColumns_*numRows_; ++i) {
            data_[i] = matrix.data_[i];
        }
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
            os << "( ";
            for (size_t column = 0; column < matrix.Num_Columns(); ++column) {
                os << matrix[row][column] << " ";
            }
            os << ")\n";
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
}