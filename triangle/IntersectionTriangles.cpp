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
        Cube_t mainCube = Cube_t{{minX, minY, minZ}, lenEdge};
        Node_t topNode{mainCube, triangles, 0};

        octree_ = Octree_t{topNode};
    }


    void Octree_t::Split_Cube(Node_t* top) {
        if (top->data_.size() <=  MIN_TRIANGLES_IN_CUBE) {
            return;
        }

        double childLenEdge = top->cube_.Len_Edge() / 2;
        unsigned childLevel = top->level_ + 1;

        gmtr::Point_t leftBottom = top->cube_.Left_Bottom();
        std::vector<gmtr::Point_t> leftBottoms{8};
        leftBottoms.push_back(leftBottom);
        leftBottoms.emplace_back(leftBottom.X() + childLenEdge, leftBottom.Y(),
                                    leftBottom.Z());
        leftBottoms.emplace_back(leftBottom.X(), leftBottom.Y() + childLenEdge,
                                  leftBottom.Z());
        leftBottoms.emplace_back(leftBottom.X() + childLenEdge,
                                  leftBottom.Y() + childLenEdge, leftBottom.Z());
        leftBottoms.emplace_back(leftBottom.X(), leftBottom.Y(),
                                  leftBottom.Z() + childLenEdge);
        leftBottoms.emplace_back(leftBottom.X() + childLenEdge, leftBottom.Y(),
                                  leftBottom.Z() + childLenEdge);
        leftBottoms.emplace_back(leftBottom.X(), leftBottom.Y() + childLenEdge,
                                  leftBottom.Z() + childLenEdge);
        leftBottoms.emplace_back(leftBottom.X() + childLenEdge,
                                   leftBottom.Y() + childLenEdge,
                                   leftBottom.Z() + childLenEdge);


        for (int i = 0; i < 8; ++i) {
            top->children_[i] = new Node_t{{leftBottoms[i], childLenEdge},
                                           childLevel};
        }

        auto children = top->children_;

        for (auto& it : top->data_) {
            bool check = false;
            for (int i = 0; i < 8; ++i) {
                if (children[i]->cube_.Is_Cube_Triangle(*it)) {
                    children[i]->data_.push_back(it);
                    check = true;
                    break;
                }
            }
            if (check) {
                break;
            } else {
                top->unassigned_.push_back(it);
            }
        }
        if (childLevel == LEVELS) {
            return;
        }
        for (int i = 0; i < 8; ++i) {
            Split_Cube(children[i]);
        }
    }

    bool Cube_t::Is_Cube_Triangle(gmtr::Triangle_t trig) {
        if (trig.MinX() >= leftBottom_.X() && trig.MaxX() <= leftBottom_.X() + lenEdge_ &&
            trig.MinZ() >= leftBottom_.Z() && trig.MaxZ() <= leftBottom_.Z() + lenEdge_ &&
            trig.MinY() >= leftBottom_.Y() && trig.MaxY() <= leftBottom_.Y() + lenEdge_)
        {
            return true;
        } else {
            return false;
        }
    }


}