#include "IntersectionTriangles.h"

int main() {
    size_t numTriangles = 0;
    std:: cin >> numTriangles;
    trs::Triangles_t trgs{numTriangles};
    trgs.Output_Intersecting_Triangles();
    return 0;
}
