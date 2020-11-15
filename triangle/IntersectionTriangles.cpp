#include "IntersectionTriangles.h"

namespace trs {

    Triangles_t::Triangles_t(size_t numTriangles, std::istream& is) {

        double minX = std::numeric_limits<double>::max() ,
                minY = minX,
                minZ = minX;
        double maxX = std::numeric_limits<double>::min(),
                maxY = maxX,
                maxZ = maxX;
        std::vector<triangleIterator> triangles;
        data_.reserve(numTriangles);
        for (size_t i = 0; i < numTriangles; ++i) {
            gmtr::Point_t a, b, c;
            is >> a >> b >> c;
            gmtr::Triangle_t tr{a, b, c, i};
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

        octree_ = Octree_t{mainCube, triangles, 0};

        octree_.Split_Cube();
    }

    Triangles_t::Triangles_t(std::vector<gmtr::Triangle_t> &data) {
        double minX = std::numeric_limits<double>::max() ,
                minY = minX,
                minZ = minX;
        double maxX = std::numeric_limits<double>::min(),
                maxY = maxX,
                maxZ = maxX;

        std::vector<triangleIterator> triangles;
        data_.reserve(data.size());

        for (auto& tr : data) {

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
        Cube_t mainCube = Cube_t{gmtr::Point_t{minX, minY, minZ}, lenEdge};

        octree_ = Octree_t{mainCube, triangles, 0};

        octree_.Split_Cube();
    }

    void Triangles_t::Output_Intersecting_Triangles() {
        std::unordered_set<size_t> res;
        std::set<size_t> resSet;
        octree_.Post_Order(res);
        for (auto& it : res) {
            resSet.emplace(it);
        }
        for (auto& it : resSet) {
            std::cout << it << "\n";
        }
    }

    std::unordered_set<size_t> Triangles_t::Intersecting_Triangles() {
        std::unordered_set<size_t> res;
        octree_.Post_Order(res);
        return res;
    }

    void Octree_t::Split_Cube(Node_t* top) {
        if (top->data_.size() <=  MIN_TRIANGLES_IN_CUBE) {
            for (auto& it : top->data_) {
                top->unassigned_.push_back(it);
            }
            return;
        }

        double childLenEdge = top->cube_.Len_Edge() / 2;
        unsigned childLevel = top->level_ + 1;

        gmtr::Point_t leftBottom = top->cube_.Left_Bottom();
        std::vector<gmtr::Point_t> leftBottoms;
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
            Cube_t cube{leftBottoms[i], childLenEdge};
            top->children_[i] = new Node_t( cube, childLevel);
        }


        for (auto& it : top->data_) {
            bool check = false;
            for (int i = 0; i < 8; ++i) {
                if (top->children_[i]->cube_.Is_Cube_Triangle(*it)) {
                    top->children_[i]->data_.push_back(it);
                    check = true;
                    break;
                }
            }
            if (!check) {
                top->unassigned_.push_back(it);
            }
        }
        if (childLevel == LEVELS) {
            return;
        }
        for (int i = 0; i < 8; ++i) {
            Split_Cube(top->children_[i]);
        }
    }

    void Octree_t::Post_Order(Node_t *top, std::unordered_set<size_t>& res) {
        if (top == nullptr) {
            return;
        }
        for (int i = 0; i < 8; ++i) {
            Post_Order(top->children_[i], res);
        }
        if (top->level_ == LEVELS || top->unassigned_.empty()) {
            Triangles_IntersectionN2(top->data_, res);
            return;
        }
        for (auto& itUn : top->unassigned_) {
            for (auto& itData : top->data_) {
                if (itUn->Id() == itData->Id()) {
                    continue;
                }
                if (itUn->Triangles_Intersection(*itData)) {
                    if (res.count(itUn->Id()) == 0) {
                        res.emplace(itUn->Id());
                    }
                    if (res.count(itData->Id()) == 0) {
                        res.emplace(itData->Id());
                    }
                }
            }
        }

    }

    Octree_t::~Octree_t() {
        Delete_Node(&top_);
    }

    void Octree_t::Delete_Node(Node_t *top) {
        if (top == nullptr || top->level_ == 0) {
            return;
        }
        for (auto& it : top->children_) {
            Delete_Node(it);
        }
        delete top;
    }


    bool Cube_t::Is_Cube_Triangle(gmtr::Triangle_t& trig) {
        if (trig.MinX() >= leftBottom_.X() && trig.MaxX() <= leftBottom_.X() + lenEdge_ &&
            trig.MinZ() >= leftBottom_.Z() && trig.MaxZ() <= leftBottom_.Z() + lenEdge_ &&
            trig.MinY() >= leftBottom_.Y() && trig.MaxY() <= leftBottom_.Y() + lenEdge_)
        {
            return true;
        } else {
            return false;
        }
    }

    void Triangles_IntersectionN2(std::vector<triangleIterator>& data, std::unordered_set<size_t>& res) {
        if (data.empty()) {
            return;
        }
        for (int i = 0; i < data.size() - 1; ++i) {
            for (int j = i + 1; j < data.size(); ++j) {
                if (data[i]->Id() == data[j]->Id()) {
                    continue;
                }
                if (data[i]->Triangles_Intersection(*data[j])) {
                    if (res.count(data[i]->Id()) == 0) {
                        res.insert(data[i]->Id());
                    }
                    if (res.count(data[j]->Id()) == 0) {
                        res.insert(data[j]->Id());
                    }
                }
            }
        }
    }

    bool Unordered_Set_Equal(std::unordered_set<size_t>& us1, std::unordered_set<size_t>& us2) {
        if (us1.size() != us2.size()) {
            return false;
        }
        std::set<size_t> s1, s2;
        for (auto& it : us1) {
            s1.emplace(it);
        }
        for (auto& it : us2) {
            s2.emplace(it);
        }
        auto it1 = s1.begin();
        auto it2 = s2.begin();
        while (it1 != s1.end() || it2 != s2.end()) {
            if (*it1 != *it2) {
                return false;
            }
            it1 = std::next(it1);
            it2 = std::next(it2);
        }
        return true;
    }
}