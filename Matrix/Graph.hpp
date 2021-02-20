#pragma once
#include "Matrix.hpp"
#include <regex>
#include <set>



namespace grph {
    class RTGraph_t final{
        using MatrCoord_t = std::pair<size_t, size_t>;
        using EdgeInfo_t = std::pair<double, double>;
    public:

        RTGraph_t(std::istream& is);
        std::vector<double> Calculate_Potential();
        std::vector<std::pair<MatrCoord_t, double>> Calculate_Amperage(std::ostream& os);
        mtrx::Matrix_t<int> Find_Cycles();
        size_t Num_Nodes();
        size_t Num_Edges();

    private:
        void Depth_Walk(mtrx::Matrix_t<int>& contourMtrx, std::set<size_t>& climbedNodes, mtrx::Matrix_t<int> newRow,
                        const size_t currentNode);

        mtrx::Matrix_t<double> incMtrx_;
        std::vector<double> resistMtrx_;
        mtrx::Matrix_t<double> emfMtrx_;
        std::vector<size_t> loops_;
    };


    std::vector<double> Gaussian_Method(mtrx::Matrix_t<double> mtrx);
    size_t Sequential_Elim(mtrx::Matrix_t<double> &mtrx);
    std::vector<double> Reverse_Sub(mtrx::Matrix_t<double> &mtrx);
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

    incMtrx_ = mtrx::Matrix_t<int>(maxNumNode, matrInfo.size());
    resistMtrx_ = std::vector<double>(matrInfo.size());
    emfMtrx_ = mtrx::Matrix_t<double>(matrInfo.size(), 1);

    for (size_t i = 0; i < matrInfo.size(); ++i) {
        incMtrx_[matrInfo[i].first.first - 1][i] += 1;
        incMtrx_[matrInfo[i].first.second - 1][i] += -1;
        if (matrInfo[i].first.first == matrInfo[i].first.second) {
            incMtrx_[matrInfo[i].first.first - 1][i] = 0;
            loops_.emplace_back(matrInfo[i].first.first);
        }
        resistMtrx_[i] = matrInfo[i].second.first;
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
    mtrx::Matrix_t<double> conductMtrx{mtrx::ConvertDiagMtrx(resistMtrx_)};
    for (size_t i = 0; i < conductMtrx.Num_Columns(); ++i) {
        conductMtrx[i][i] = 1 / conductMtrx[i][i];
    }
    mtrx::Matrix_t<double> incMtrxWithoutMaxNode = incMtrx_.Without_Row(incMtrx_.Num_Rows() - 1);

    mtrx::Matrix_t<double> systEq = incMtrxWithoutMaxNode.Matrix_Mult(conductMtrx).Matrix_Mult(incMtrxWithoutMaxNode);

    mtrx::Matrix_t<double> freeColumn = - incMtrx_.Matrix_Mult(conductMtrx).Matrix_Mult(emfMtrx_);
#ifdef DEBUG
    std::cout << systEq << std::endl << freeColumn << std::endl;
#endif
    std::vector<double> res = Gaussian_Method(systEq.Connect_Column(freeColumn));
    return res;
}

size_t grph::RTGraph_t::Num_Nodes() {
    return incMtrx_.Num_Rows() + 1;
}

size_t grph::RTGraph_t::Num_Edges() {
    return emfMtrx_.Num_Rows();
}

std::vector<std::pair<grph::RTGraph_t::MatrCoord_t, double>> grph::RTGraph_t::Calculate_Amperage(std::ostream &os) {
    std::vector<std::pair<MatrCoord_t, double>> res(Num_Edges());

}

mtrx::Matrix_t<int> grph::RTGraph_t::Find_Cycles() {
        mtrx::Matrix_t<int> contourMtrx;
        mtrx::Matrix_t<int> newRow{1, Num_Edges()};
        std::set<size_t> climbedNodes;
        size_t currentNode = 1;
        Depth_Walk( contourMtrx, climbedNodes, newRow, currentNode);
        std::cout << contourMtrx;
        return contourMtrx;
}

void grph::RTGraph_t::Depth_Walk( mtrx::Matrix_t<int>& contourMtrx, std::set<size_t>& climbedNodes,
                                  mtrx::Matrix_t<int> newRow, const size_t currentNode)
{
    std::cout << newRow << std::endl;
    if (climbedNodes.find(currentNode) != climbedNodes.end()) {
        return;
    }
    climbedNodes.insert(currentNode);
    for (size_t i = 0; i < Num_Edges(); ++i) {
        if (incMtrx_[currentNode - 1][i] == 1) {
            size_t j = 0;
            while (incMtrx_[j][i] != -incMtrx_[currentNode - 1][i]) {
                j++;
            }
            if (climbedNodes.find(j+1) == climbedNodes.end()) {
                newRow[0][i] = incMtrx_[currentNode - 1][i];
                Depth_Walk( contourMtrx, climbedNodes, newRow, j + 1);
            } else {
                newRow[0][i] = incMtrx_[currentNode - 1][i];
                std::cout << "Add new row:" << newRow;
                contourMtrx.Add_Row(newRow);
                std::cout << "MTRX:" << contourMtrx << std::endl << std::endl;
            }
        }
    }
}

std::vector<double> grph::Gaussian_Method(mtrx::Matrix_t<double> mtrx) {
    if (mtrx.Num_Rows() + 1 != mtrx.Num_Columns()) {
        //have not solution
        //TODO::
    }
    size_t n = mtrx.Num_Rows();
    int singularFlag = grph::Sequential_Elim(mtrx);

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

    return grph::Reverse_Sub(mtrx);
}

std::vector<double> grph::Reverse_Sub(mtrx::Matrix_t<double> &mtrx) {
    std::vector<double> result(mtrx.Num_Rows() + 1);
    for (int i = mtrx.Num_Rows() - 1; i >= 0; --i)
    {
        result[i] = mtrx[i][mtrx.Num_Rows()];

        for (int j = i + 1; j < mtrx.Num_Rows(); ++j)
            result[i] -= mtrx[i][j] * result[j];

        if (!mtrx::Double_Equal(mtrx[i][i], 0)) {
            result[i] = result[i] / mtrx[i][i];
        }
    }

    return result;
}

size_t grph::Sequential_Elim(mtrx::Matrix_t<double> &mtrx) {
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
            if (!mtrx::Double_Equal(mtrx[k][k], 0)) {
                double f = mtrx[i][k] / mtrx[k][k];
                for (int j = k + 1; j < mtrx.Num_Columns(); ++j)
                    mtrx[i][j] -= mtrx[k][j] * f;
            }
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

