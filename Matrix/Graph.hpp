#pragma once
#include "Matrix.hpp"
#include <regex>



namespace grph {
    class RTGraph_t final{
    public:
        RTGraph_t(std::istream& is);
        std::vector<double> Calculate_Potential();
        void Calculate_Print_Amperage(std::ostream& os);
        size_t Num_Nodes();
        size_t Num_Edges();

    private:
        using MatrCoord_t = std::pair<size_t, size_t>;
        using EdgeInfo_t = std::pair<double, double>;

        mtrx::Matrix_t<double> incMtrx_;
        mtrx::Matrix_t<double> conductMtrx_;
        mtrx::Matrix_t<double> emfMtrx_;
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
                             "([V]?))?"
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

    incMtrx_ = mtrx::Matrix_t<int>{maxNumNode - 1, matrInfo.size()};
    conductMtrx_ = mtrx::Matrix_t<double>{matrInfo.size()};
    emfMtrx_ = mtrx::Matrix_t<double>{matrInfo.size(), 1};

    for (size_t i = 0; i < matrInfo.size(); ++i) {
        if (matrInfo[i].first.first != maxNumNode) {
            incMtrx_[matrInfo[i].first.first - 1][i] = 1;
        }
        if (matrInfo[i].first.second != maxNumNode) {
            incMtrx_[matrInfo[i].first.second - 1][i] = -1;
        }
        if (matrInfo[i].first.first == matrInfo[i].first.second)
            incMtrx_[matrInfo[i].first.first - 1][i] = 2;

        if (matrInfo[i].second.first != 0) {
            conductMtrx_[i][i] = 1 / matrInfo[i].second.first;
        }
        emfMtrx_[i][0] = matrInfo[i].second.second;
    }
#ifdef DEBUG
    std::cout << incMtrx_ << std::endl
              << conductMtrx_ << std::endl
              << emfMtrx_ << std::endl;
#endif
}

std::vector<double> grph::RTGraph_t::Calculate_Potential() {
    mtrx::Matrix_t<double> incMtrxT = incMtrx_.Transposition();
    mtrx::Matrix_t<double> systEq = incMtrx_.Matrix_Mult(conductMtrx_).Matrix_Mult(incMtrxT);

    mtrx::Matrix_t<double> freeColumn = - incMtrx_.Matrix_Mult(conductMtrx_).Matrix_Mult(emfMtrx_);
#ifdef DEBUG
    std::cout << systEq << std::endl << freeColumn << std::endl;
#endif
    std::vector<double> res = Gaussian_Method(systEq.Add_Column(freeColumn));
    return res;
}

size_t grph::RTGraph_t::Num_Nodes() {
    return incMtrx_.Num_Rows() + 1;
}

size_t grph::RTGraph_t::Num_Edges() {
    return emfMtrx_.Num_Rows();
}

void grph::RTGraph_t::Calculate_Print_Amperage(std::ostream& os) {
    std::vector<double> pot = Calculate_Potential();
    for (size_t i = 0; i < Num_Edges(); ++i) {
        size_t gNode1 = 0;
        size_t gNode2 = 0;
        for (size_t j = 0; j < Num_Nodes() - 1; ++j) {
            if (mtrx::Double_Equal(incMtrx_[j][i], 1)) {
                gNode1 = j + 1;
            }
            if (mtrx::Double_Equal(incMtrx_[j][i], -1)) {
                gNode2 = j + 1;
            }
        }
        if (gNode1 == 0) {
            gNode1 = Num_Nodes();
        }
        if (gNode2 == 0) {
            gNode2 = Num_Nodes();
        }

        double voltage = pot[gNode1 - 1] - pot[gNode2 - 1] + emfMtrx_[i][0];
        double amperage = voltage * conductMtrx_[i][i];

        os << gNode1 << " -- " << gNode2 << ": "
                  << amperage << " A" << std::endl;
    }
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
    std::vector<double> result(mtrx.Num_Rows() + 1);
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

