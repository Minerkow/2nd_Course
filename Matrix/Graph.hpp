#pragma once
#include "Matrix.hpp"
#include <regex>



namespace grph {
    class RTGraph_t final{
    public:
        RTGraph_t(std::istream& is);
        std::vector<double> Calculate_Potential();
    private:
        using MatrCoord_t = std::pair<size_t, size_t>;
        using GraphInfo_t = std::pair<double, double>;

        size_t sequential_elim(mtrx::Matrix_t<double>& mtrx);
        std::vector<double> reverse_sub(mtrx::Matrix_t<double> &mtrx);
        std::vector<double> Gaussian_Method(mtrx::Matrix_t<double> mtrx);

        mtrx::Matrix_t<GraphInfo_t> matr_;
        size_t numNode;
    };
}

grph::RTGraph_t::RTGraph_t(std::istream &is) {
    std::string line;
    std::cmatch result;
    size_t maxNumNode = 0;
    std::vector<std::pair<MatrCoord_t, GraphInfo_t>> matrInfo{};
    const std::regex regular("(\\d+)"
                             "(\\s*\\-\\-\\s*)"
                             "(\\d+)"
                             "(\\s*[,]\\s*)"
                             "(\\d+[.]?\\d*)"
                             "(\\s*[;]\\s*)"
                             "((\\-?\\d+[.]\\d)"
                             "([V]))?"
                       );
    while (getline(is, line, '\n')) {
        size_t grNode1, grNode2;
        std::pair<double, double> rv;
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

    matr_ = mtrx::Matrix_t<GraphInfo_t>{maxNumNode};
    numNode = maxNumNode;

    for (auto& it : matrInfo) {
        matr_[it.first.first - 1][it.first.second - 1] = it.second;
        matr_[it.first.second - 1][it.first.first - 1] = {it.second.first, -it.second.second};
    }
    std::cout << matr_ << std::endl;
}

std::vector<double> grph::RTGraph_t::Calculate_Potential() {
    if (matr_.empty())
        return std::vector<double>{};
    mtrx::Matrix_t<double> sysLinEq{numNode, numNode + 1};
    for (size_t i = 0; i < numNode; ++i) {
        for (size_t j = 0; j < numNode; j++) {
            if (i == j) {
                double resist = 0.0;
                for (size_t k = 0; k < numNode; ++k) {
                    if (matr_[i][k].first != 0) {
                        resist += 1 / matr_[i][k].first;
                    }
                }
                sysLinEq[i][j] = resist;
            } else {
                if (matr_[i][j].first != 0)
                    sysLinEq[i][j] = - 1 / matr_[i][j].first;
            }
            if (matr_[i][j].first != 0) {
                sysLinEq[i][numNode + 1] += matr_[i][j].second * (1 / matr_[i][j].first);
                std::cout << "_" << sysLinEq[i][numNode+1] << "_";
            }
        }
    }
    std::cout << sysLinEq << std::endl;

    std::vector<double> res = Gaussian_Method(sysLinEq);

    for (auto& it : res) {
        std::cout << it << " ";
    }

    return std::vector<double>{};
}

std::vector<double> grph::RTGraph_t::Gaussian_Method(mtrx::Matrix_t<double> mtrx) {
    if (mtrx.Num_Rows() + 1 != mtrx.Num_Columns()) {
        //have not solution
        //TODO::
    }
    size_t n = mtrx.Num_Rows();
    int singularFlag = sequential_elim(mtrx);

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

    return reverse_sub(mtrx);
}

std::vector<double> grph::RTGraph_t::reverse_sub(mtrx::Matrix_t<double> &mtrx) {
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

size_t grph::RTGraph_t::sequential_elim(mtrx::Matrix_t<double> &mtrx) {
    for (int k = 0; k < mtrx.Num_Rows(); ++k)
    {
        int iMax = k;
        int vMax = mtrx[iMax][k];

        for (int i = k + 1; i < mtrx.Num_Rows(); ++i)
            if (std::abs(mtrx[i][k]) > vMax)
                vMax = mtrx[i][k], iMax = i;

        if (mtrx[k][iMax] != 0.0)
            return k; // Matrix is singular

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



