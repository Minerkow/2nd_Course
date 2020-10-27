#include "IntersectionTriangles.h"

int main() {
    size_t numTriangles = 0;
    std:: cin >> numTriangles;
    std::vector<gmtr::Triangle_t> data;
    for (size_t i = 0; i < numTriangles; ++i) {
        gmtr::Point_t a, b, c;
        double ax, bx, cx;
        double ay, by, cy;
        double az, bz, cz;
        std::cin >> ax >> ay >> az;
        std::cin >> bx >> by >> bz;
        std::cin >> cx >> cy >> cz;
        data.push_back({{ax, ay, az}, {bx, by, bz}, {cx, cy, cz}, i});
    }
    trs::Triangles_t trgs{data};
    //std::unordered_set<size_t> res = trgs.Intersecting_Triangles();
    trgs.Output_Intersecting_Triangles();
    return 0;
}
