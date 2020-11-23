#include <vector>
#include <iostream>
#include "Bitonic_sort.h"

int main() {
    std::vector<int> data{9, 8, 7, 6, 5, 4, 3, 2};
    std::vector<cl::Platform> platforms = bs::GetPlatforms();
    cl::Platform usePlatform = platforms[PLATFORM];

    std::vector<cl::Device> devices;
    usePlatform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    cl::Context context{devices};
    cl::CommandQueue commandQueue{context};
    cl::Buffer buf{context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                data.size(), data.data()};

    std::ifstream fs("/home/bibi/Desktop/Programm/Semestr_2_C++/2nd_Course/ Bitonic_Sort/bitonic_sort.cl");
    if (!fs.is_open()) {
        std::cerr << "File not open" << std::endl;
    }
    std::string gpuCode;
    std::string line;
    while (std::getline(fs, line))
        gpuCode += line;
    fs.close();

    cl::Program program(context, gpuCode);
    program.build();

    cl::Kernel kernel(program, "bitonic_sort");
    kernel.setArg(0, data.data());
    kernel.setArg(1, nullptr);
    cl::NDRange ndRange;
    commandQueue.enqueueNDRangeKernel(kernel, )
}