#include <Bitonic_sort.h>

namespace bs {
    std::vector<cl::Platform> GetPlatforms() {
        std::vector<cl::Platform> platforms;
        cl_uint numPlatforms;
        clGetPlatformIDs(0, nullptr, &numPlatforms);
        std::vector<cl_platform_id> ids(numPlatforms);
        platforms.resize(numPlatforms);
        for (size_t i = 0, e = ids.size(); i < e; ++i)
            platforms[i] = cl::Platform(ids[i], true);
        return platforms;
    }
}