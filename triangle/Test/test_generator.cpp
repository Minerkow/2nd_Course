#include "test_generator.h"

namespace trgtest {
    TrianglesGenerator_t::TrianglesGenerator_t() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> disX{MINX, MAXX};
        std::uniform_real_distribution<> disY{MINY, MAXY};
        std::uniform_real_distribution<> disZ{MINZ, MAXZ};
        std::uniform_real_distribution<> disR{0.0, MAX_RADIUS};

        std::vector<gmtr::Sphere_t> spheres;
        for (int i = 0; i < NUM_TRIANGLES; ++i) {
            gmtr::Point_t centre{disX(gen), disY(gen), disY(gen)};
            double radius = disR(gen);
            gmtr::Sphere_t sphere{radius, centre};
            triangles_.emplace_back(sphere.Random_Point(),
                                    sphere.Random_Point(),
                                    sphere.Random_Point(), i);
        }
    }



    std::ostream &operator<<(std::ostream &os, TrianglesGenerator_t& trg) {
        for (auto& it : trg.triangles_) {
            os << " " << it.A()
               << " " << it.B() << " " << it.C() << "\n";
        }
        return os;
    }

}
