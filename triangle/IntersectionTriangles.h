#pragma once

#include "Triangle.h"

#include <utility>
#include <vector>
#include <limits>
#include <array>
#include <map>

namespace trs {

    enum {LEVELS = 3};

    using triangleIterator = std::vector<gmtr::Triangle_t>::iterator;

    class Cube_t;
    class Octree_t;
    class Triangles_t;
    class Node_t;

    class Cube_t {
    public:
        Cube_t() : leftBottom_{}, lenEdge_(NAN), data_(0) {}
        Cube_t(gmtr::Point_t leftBottom, double lenEdge,
               std::vector<triangleIterator> data) : leftBottom_(leftBottom),
                                                     lenEdge_(lenEdge),
                                                     data_(std::move(data)) {}
        bool Check_Add(triangleIterator triangle);
    public:
        gmtr::Point_t leftBottom_;
        double lenEdge_;
        std::vector<triangleIterator> data_;
    };

//------------------------------------------------------------------------------------------------------

    struct Node_t {
        Cube_t cube_;
        std::array<Node_t*, 8> children_{};
        unsigned level_;
    };

//---------------------------------------------------------------------------------------

    class Octree_t {
    public:
        friend Triangles_t;

        void Split_Cube(Node_t* top);
        friend Node_t;
    private:
        Node_t top_;
    };

//------------------------------------------------------------------------------------------------------

    class Triangles_t {
    public:
        explicit Triangles_t(size_t numTriangles);

    private:
        std::vector<gmtr::Triangle_t> data_;
        Octree_t octree_;
    };

//------------------------------------------------------------------------------------------------------

}
