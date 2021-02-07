#pragma once
#include "Matrix.hpp"
#include <regex>



namespace grph {
    class RTGraph_t final{
    public:
        RTGraph_t(std::istream& is);
        std::vector<double> Calculate_Potential();
        size_t Num_Nodes();
        size_t Num_Edges();

    private:
        using MatrCoord_t = std::pair<size_t, size_t>;
        using EdgeInfo_t = std::pair<double, double>;

        mtrx::Matrix_t<std::vector<EdgeInfo_t>> matr_;
    };


    std::vector<double> Gaussian_Method(mtrx::Matrix_t<double> mtrx);
    size_t sequential_elim(mtrx::Matrix_t<double> &mtrx);
    std::vector<double> reverse_sub(mtrx::Matrix_t<double> &mtrx);
}

grph::RTGraph_t::RTGraph_t(std::istream &is) {
    std::string line;
    std::cmatch result;
    size_t maxNumNode = 0;
    std::vector<std::pair<MatrCoord_t, EdgeInfo_t>> matrInfo{};
    const std::regex regular("(\\d+)"
                             "(\\s*\\-\\-\\s*)"
                             "(\\d+)"
                             "(\\s*[,]\\s*)"
                             "(\\d+[.]?\\d*)"
                             "(\\s*[;]\\s*)"
                             "((\\-?\\d+([.]\\d)?)"
                             "([V]))?"
                       );
    while (getline(is, line, '\n')) {
        size_t grNode1, grNode2;
        EdgeInfo_t rv;
        if (std::regex_search(line.c_str(), result, regular)) {
            grNode1 = std::atoi(result[1].str().c_str());
            grNode2 = std::atoi(result[3].str().c_str());

            maxNumNode = std::max(maxNumNode, std::max(grNode1, grNode2));

            rv.first = std::atof(result[5].str().c_str());
            if (result.size() < 8) {
                rv.second = 0.0;
            } else {
                rv.second = std::atof(result[7].str().c_str());
            }
            matrInfo.push_back({{grNode1, grNode2}, rv});
        } else {
            throw std::regex_error(std::regex_constants::error_collate);
        }
    }

    matr_ = mtrx::Matrix_t<std::vector<EdgeInfo_t>>{maxNumNode, matrInfo.size()};
    for (size_t i = 0; i < matrInfo.size(); ++i) {
        matr_[matrInfo[i].first.first - 1][i].push_back(matrInfo[i].second);
        matr_[matrInfo[i].first.second - 1][i].emplace_back(matrInfo[i].second.first,
                                                          matrInfo[i].second.second);
    }
    std::cout << matr_ << std::endl;
}

std::vector<double> grph::RTGraph_t::Calculate_Potential() {
    if (matr_.empty())
        return std::vector<double>{};
    mtrx::Matrix_t<double> sysLinEq{Num_Nodes(), Num_Nodes() + 1};
    std::vector<double> res(Num_Nodes());

    for (size_t i = 0; i < sysLinEq.Num_Rows(); ++i) {
        for (size_t j = 0; j < sysLinEq.Num_Rows(); ++j) {
            if (i == j) {
                continue;
            }
            double conductivity = 0;
            for (auto& it : matr_[i][j]) {
                conductivity += 1 / it.first;
            }
        }
    }

    std::cout << sysLinEq << std::endl;

    std::vector<double> res = grph::Gaussian_Method(sysLinEq);

    for (auto& it : res) {
        std::cout << it << " ";
    }

    return std::vector<double>{};
}

size_t grph::RTGraph_t::Num_Nodes() {
    return matr_.Num_Rows();
}

size_t grph::RTGraph_t::Num_Edges() {
    return matr_.Num_Columns();
}

std::vector<double> grph::Gaussian_Method(mtrx::Matrix_t<double> mtrx) {
    if (mtrx.Num_Rows() + 1 != mtrx.Num_Columns()) {
        //have not solution
        //TODO::
    }
    size_t n = mtrx.Num_Rows();
    int singularFlag = grph::sequential_elim(mtrx);

    if (singularFlag != -1)
    {
        printf("Singular Matrix.\n");

        if (mtrx[singularFlag][n])
            printf("Inconsistent System.");
        else
            printf("May have infinitely many "
                   "solutions.");

        //TODO
    }

    return grph::reverse_sub(mtrx);
}

std::vector<double> grph::reverse_sub(mtrx::Matrix_t<double> &mtrx) {
    std::vector<double> result(mtrx.Num_Rows());
    for (int i = mtrx.Num_Rows() - 1; i >= 0; --i)
    {
        result[i] = mtrx[i][mtrx.Num_Rows()];

        for (int j = i + 1; j < mtrx.Num_Rows(); ++j)
            result[i] -= mtrx[i][j] * result[j];


        result[i] = result[i] / mtrx[i][i];
    }

    return result;
}

size_t grph::sequential_elim(mtrx::Matrix_t<double> &mtrx) {
    for (int k = 0; k < mtrx.Num_Rows(); ++k)
    {
        int iMax = k;
        int vMax = mtrx[iMax][k];

        for (int i = k + 1; i < mtrx.Num_Rows(); ++i) {
            if (std::abs(mtrx[i][k]) > vMax) {
                vMax = mtrx[i][k];
                iMax = i;
            }
        }

        if (iMax != k)
            mtrx.Swap_Rows(k, iMax);

        for (int i = k + 1; i < mtrx.Num_Rows(); ++i)
        {
            double f = mtrx[i][k]/mtrx[k][k];

            for (int j = k + 1; j < mtrx.Num_Columns(); ++j)
                mtrx[i][j] -= mtrx[k][j]*f;

            mtrx[i][k] = 0;
        }
    }
    return -1;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& vec) {
    os << " {";
    for (auto& it : vec) {
        os << it << " ";
    }
    os << "}";
    return os;
}

