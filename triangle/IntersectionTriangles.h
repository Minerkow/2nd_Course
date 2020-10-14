#pragma once

#include "Triangle.h"

#include <utility>
#include <vector>
#include <limits>
#include <array>
#include <map>
#include <list>
#include <unordered_set>
namespace trs {

    enum {LEVELS = 3, MIN_TRIANGLES_IN_CUBE = 3};

    using triangleIterator = std::vector<gmtr::Triangle_t>::iterator;

    class Cube_t;
    class Octree_t;
    class Triangles_t;
    struct Node_t;
    class Square_t;


    class Cube_t {
    public:
        Cube_t() : leftBottom_{}, lenEdge_(NAN) {}
        Cube_t(gmtr::Point_t leftBottom, double lenEdge) : leftBottom_(leftBottom),
                                                           lenEdge_(lenEdge) {}
        gmtr::Point_t Left_Bottom() const {return leftBottom_;}
        double Len_Edge() const {return lenEdge_;}
        bool Is_Cube_Triangle(gmtr::Triangle_t& trig);
    private:
        gmtr::Point_t leftBottom_;
        double lenEdge_;
    };

//------------------------------------------------------------------------------------------------------

    struct Node_t {
    public:
        Node_t(Cube_t cube, std::vector<triangleIterator> data, unsigned level)
                : cube_(cube), data_(std::move(data)),
                  level_(level), unassigned_(), children_{} {}
        Node_t() : cube_{}, data_{}, level_{}, children_() {}
        Node_t(Cube_t cube, unsigned level) : cube_(cube), data_{0},
                                              level_(level), unassigned_(0),
                                              children_{} {}

        Cube_t cube_;
        std::vector<triangleIterator> data_;
        std::array<Node_t*, 8> children_;
        unsigned level_;
        std::vector<triangleIterator> unassigned_;
    };

//---------------------------------------------------------------------------------------

    class Octree_t {
    public:
        Octree_t() : top_{} {}
        Octree_t(Node_t top) : top_(top) {}
        void Split_Cube(Node_t* top);
        void Split_Cube() {Split_Cube(&top_);}
        void Post_Order(Node_t* top, std::unordered_set<size_t>& res);
        void Post_Order(std::unordered_set<size_t>& res) {Post_Order(&top_, res);}
        void Delete_Node(Node_t* top);
        ~Octree_t();
    private:
        Node_t top_;
    };

//------------------------------------------------------------------------------------------------------

    class Triangles_t {
    public:
        Triangles_t(size_t numTriangles);
        Triangles_t(std::vector<gmtr::Triangle_t>& data);

        void Output_Intersecting_Triangles();
        std::unordered_set<size_t> Intersecting_Triangles();
        size_t Triangle_Number(triangleIterator triangle) {return triangle - data_.begin();}
    private:
        std::vector<gmtr::Triangle_t> data_;
        Octree_t octree_;
    };

//------------------------------------------------------------------------------------------------------

    void Triangles_IntersectionN2(std::vector<triangleIterator>& data,
                                  std::unordered_set<size_t>& res);
}
