#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "OpenCL-CLHPP/include/CL/opencl.hpp"

enum {PLATFORM = 0};

namespace bs {
    std::vector<cl::Platform> GetPlatforms();

}