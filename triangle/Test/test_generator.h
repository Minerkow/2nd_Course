#pragma once

#include "../Triangle.h"
#include <vector>
#include <random>

namespace trgtest {
    const double MINX = 0;
    const double MINY = 0;
    const double MINZ = 0;

    const double MAXX = 2000;
    const double MAXY = 2000;
    const double MAXZ = 2000;

    const double MAX_RADIUS = 100.0;

    const unsigned NUM_TRIANGLES = 10000;

    class TrianglesGenerator_t {
    public:
        TrianglesGenerator_t();

        friend std::ostream& operator<<(std::ostream& os, TrianglesGenerator_t& trg);
    //private:
        std::vector <gmtr::Triangle_t> triangles_;
    };

}