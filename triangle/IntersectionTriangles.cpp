#include "IntersectionTriangles.h"

namespace trs {
    Triangles_t::Triangles_t(size_t numTriangles) {

        double minX = std::numeric_limits<double>::max() ,
               minY = minX,
               minZ = minX;
        double maxX = std::numeric_limits<double>::min(),
               maxY = maxX,
               maxZ = maxX;
        std::vector<triangleIterator> triangles;
        data_.resize(numTriangles);
        for (size_t i = 0; i < numTriangles; ++i) {
            gmtr::Triangle_t tr;
            std::cin >> tr;
            data_.push_back(tr);
            triangles.push_back(std::prev(data_.end()));

            minX = std::min(minX, tr.MinX());
            minY = std::min(minY, tr.MinY());
            minZ = std::min(minZ, tr.MinZ());

            maxX = std::max(maxX, tr.MaxX());
            maxY = std::max(maxY, tr.MaxY());
            maxZ = std::max(maxZ, tr.MaxZ());
        }

        double lenEdge = std::max(maxX - minX,
                                  std::max(maxY - minY, maxZ - minZ));
        Cube_t mainCube = Cube_t{{minX, minY, minZ}, lenEdge, triangles};
        octree_.top_.cube_ = std::move(mainCube);
        octree_.top_.level_ = 0;
    }


    void Octree_t::Split_Cube(Node_t* top) {
        if (top->level_ == 3)
            return;

        double childLenEdge =  top->cube_.lenEdge_ / 2;

        for (int i = 0; i < 8; ++i) {
            top->children_[i] = new Node_t;
            top->children_[i]->level_ = top->level_ + 1;
            top->children_[i]->cube_.lenEdge_ = childLenEdge;
        }

        top->children_[0]->cube_.leftBottom_ = top->cube_.leftBottom_;
        top->children_[1]->cube_.leftBottom_ = top->cube_.leftBottom_ + gmtr::Point_t{childLenEdge, 0, 0};
        top->children_[2]->cube_.leftBottom_ = top->cube_.leftBottom_ + gmtr::Point_t{0, childLenEdge, 0};
        top->children_[3]->cube_.leftBottom_ = top->cube_.leftBottom_ + gmtr::Point_t{childLenEdge, childLenEdge, 0};
        top->children_[4]->cube_.leftBottom_ = top->cube_.leftBottom_ + gmtr::Point_t{0, 0, childLenEdge};
        top->children_[5]->cube_.leftBottom_ = top->cube_.leftBottom_ + gmtr::Point_t{childLenEdge, 0, childLenEdge};
        top->children_[6]->cube_.leftBottom_ = top->cube_.leftBottom_ + gmtr::Point_t{0, childLenEdge, childLenEdge};
        top->children_[7]->cube_.leftBottom_ = top->cube_.leftBottom_ + gmtr::Point_t{childLenEdge, childLenEdge, childLenEdge};

        for (auto& it : top->cube_.data_) {
            for (int i = 0; i < 8; ++i) {
                //TODO::add to cubes correctly
            }
        }
    }

    bool Cube_t::Check_Add(triangleIterator triangle) {
        //TODO:: add triangle in cube
    }
}