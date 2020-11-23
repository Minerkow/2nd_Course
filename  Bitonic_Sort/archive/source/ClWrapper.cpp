#include "../include/ClWrapper.h"

namespace cl {

    Platforms_t::Platforms_t() {
        cl_int ret;

        ret = clGetPlatformIDs(0, nullptr, &numPlatforms_);
        Check_Error(ret);
        if (numPlatforms_  == 0) {
            std::cerr << "Platforms not found!!\n";
            exit(EXIT_FAILURE);
        }

        cl_platform_id *platforms = new cl_platform_id [numPlatforms_];
        ret = clGetPlatformIDs(numPlatforms_, platforms, nullptr);
        for (int i = 0; i < numPlatforms_; ++i) {
            platforms_.push_back(platforms_[i]);
        }

        delete [] platforms;
        Check_Error(ret);
    }

    void Check_Error(cl_int ret) {
        std::string typeError;
        switch (ret) {
            case CL_SUCCESS:
                return;
            case CL_INVALID_VALUE:
                typeError = "invalid value";
                break;
            case CL_INVALID_DEVICE:
                typeError = "invalid device";
                break;
            case CL_OUT_OF_HOST_MEMORY:
                typeError = "out of host memory";
                break;
            case CL_OUT_OF_RESOURCES:
                typeError = "out of resources";
                break;
            default:
                assert(true && "ooooops in cl::Platforms_t::Check_Error");
        }

        std::cerr << "Error: " << typeError << ", code - " << ret << std::endl;
    }


    cl_platform_id Platforms_t::operator[](const size_t index) {
        return platforms_[index];
    }

    void Platforms_t::Print_Platform_Info(const size_t index) {
        cl_uint ret = 0;
        unsigned short STRING_BUFSIZE = 1024;
        char buf[STRING_BUFSIZE];

        ret = clGetPlatformInfo(platforms_[index], CL_PLATFORM_NAME, sizeof(buf), buf, nullptr);
        Check_Error(ret);
        std::cout << "Platform: " << buf << std::endl;
        ret = clGetPlatformInfo(platforms_[index], CL_PLATFORM_VERSION, sizeof(buf), buf, nullptr);
        Check_Error(ret);
        std::cout << "Version: " <<  buf << std::endl;
        ret = clGetPlatformInfo(platforms_[index], CL_PLATFORM_PROFILE, sizeof(buf), buf, nullptr);
        Check_Error(ret);
        std::cout << "Profile: " << buf << std::endl;
        ret = clGetPlatformInfo(platforms_[index], CL_PLATFORM_VENDOR, sizeof(buf), buf, nullptr);
        Check_Error(ret);
        std::cout << "Vendor: " << buf << std::endl;
        ret = clGetPlatformInfo(platforms_[index], CL_PLATFORM_EXTENSIONS, sizeof(buf), buf, nullptr);
        Check_Error(ret);
        std::cout << "Extensions: " << buf << std::endl;
    }

    Devices_t::Devices_t(cl_platform_id platform) {
        cl_uint ret = 0;
        ret = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, nullptr, &numDevices_);
        Check_Error(ret);
        if (numDevices_  == 0) {
            std::cerr << "Devices not found!!\n";
            exit(EXIT_FAILURE);
        }
        cl_device_id *devices = new cl_device_id[numDevices_];
        ret = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, numDevices_, devices, nullptr);
        for (int i = 0; i < numDevices_; ++i) {
            devices_.push_back(devices[i]);
        }
        delete [] devices;
        Check_Error(ret);
    }

    cl_device_id Devices_t::operator[](const size_t index) {
        return devices_[index];
    }

    const std::vector<cl_device_id> &Devices_t::Devices() {
        return devices_;
    }

    cl_uint Devices_t::Num_Devices() {
        return numDevices_;
    }


    Context_t::Context_t(Devices_t devices, cl_context_properties *properties) {
        cl_int ret = 0;
        context_ = clCreateContext(properties, devices.Num_Devices(), devices.Devices().data(), nullptr, nullptr, &ret);
    }

    cl_context Context_t::Context() const {
        return context_;
    }


    Queue_t::Queue_t(cl_device_id device, Context_t context, cl_command_queue_properties properties) {
        cl_int ret = 0;
        cmdQueue_ = clCreateCommandQueue(context., device, CL_QUEUE_PROFILING_ENABLE, &ret);
    }


}
