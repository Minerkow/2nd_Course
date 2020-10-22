#pragma once

#include "../Triangle.h"
#include <vector>
#include <random>

namespace trgtest {
    const double MINX = -0.5;
    const double MINY = -0.5;
    const double MINZ = -0.5;

    const double MAXX = 0.5;
    const double MAXY = 0.5;
    const double MAXZ = 0.5;

    const double MAX_RADIUS = 1.0;

    const unsigned NUM_TRIANGLES = 5;

    class TrianglesGenerator_t {
    public:
        TrianglesGenerator_t();

        friend std::ostream& operator<<(std::ostream& os, TrianglesGenerator_t& trg);
    //private:
        std::vector <gmtr::Triangle_t> triangles_;
    };

}