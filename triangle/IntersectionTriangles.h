#pragma once

#include "Triangle.h"

#include <vector>
#include <limits>
#include <array>
#include <map>

namespace trs {

    class Cube_t;
    class Octree_t;

        class Cube_t {
    public:
        using triangleIterator = std::vector<gmtr::Triangle_t>::iterator;

        Cube_t() : leftBottom_{}, lenEdge_(NAN) {}
        Cube_t(gmtr::Point_t leftBottom, double lenEdge) : leftBottom_(leftBottom),
                                                           lenEdge_(lenEdge) {}
    private:
        gmtr::Point_t leftBottom_;
        double lenEdge_;
        std::vector<triangleIterator> data_;
    };

//------------------------------------------------------------------------------------------------------

    class Triangles_t {
    public:
        using triangleIterator = std::vector<gmtr::Triangle_t>::iterator;

        explicit Triangles_t(size_t numTriangles);
        explicit Triangles_t(const std::vector<gmtr::Triangle_t>& data);

        friend Cube_t;
        friend Octree_t;
    private:
        std::vector<gmtr::Triangle_t> data_;

        std::multimap<double, triangleIterator> sortedByX_;
        std::multimap<double, triangleIterator> sortedByY_;
        std::multimap<double, triangleIterator> sortedByZ_;

        Cube_t mainCube_;
    };

//------------------------------------------------------------------------------------------------------

    class Octree_t {
    public:
        using triangleIterator = std::vector<gmtr::Triangle_t>::iterator;

        struct Node_t {
            Cube_t cube_;
            std::array<triangleIterator, 8> children_;
        };
    private:
        Node_t top_;
    };
}
