#include "IntersectionTriangles.h"

namespace trs {
    Triangles_t::Triangles_t(size_t numTriangles) {

        double minX = std::numeric_limits<double>::max() ,
               minY = minX,
               minZ = minX;
        double maxX = std::numeric_limits<double>::min(),
               maxY = maxX,
               maxZ = maxX;

        data_.resize(numTriangles);
        for (size_t i = 0; i < numTriangles; ++i) {
            gmtr::Triangle_t tr;
            std::cin >> tr;
            data_.push_back(tr);

            minX = std::min(minX, tr.MinX());
            minY = std::min(minY, tr.MinY());
            minZ = std::min(minZ, tr.MinZ());

            maxX = std::max(maxX, tr.MaxX());
            maxY = std::max(maxY, tr.MaxY());
            maxZ = std::max(maxZ, tr.MaxZ());
        }

        double lenEdge = std::max(maxX - minX,
                                  std::max(maxY - minY, maxZ - minZ));
        mainCube_ = Cube_t{{minX, minY, minZ}, lenEdge};
    }

    Triangles_t::Triangles_t(const std::vector<gmtr::Triangle_t>& data) {

        double minX = std::numeric_limits<double>::max() ,
                minY = minX,
                minZ = minX;
        double maxX = std::numeric_limits<double>::min(),
                maxY = maxX,
                maxZ = maxX;
        data_ = data;
        for (auto& it : data_) {

            minX = std::min(minX, it.MinX());
            minY = std::min(minY, it.MinY());
            minZ = std::min(minZ, it.MinZ());

            maxX = std::max(maxX, it.MaxX());
            maxY = std::max(maxY, it.MaxY());
            maxZ = std::max(maxZ, it.MaxZ());
        }

        double lenEdge = std::max(maxX - minX,
                                  std::max(maxY - minY, maxZ - minZ));
        mainCube_ = Cube_t{{minX, minY, minZ}, lenEdge};
    }

}