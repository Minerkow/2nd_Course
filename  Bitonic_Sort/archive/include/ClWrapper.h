#pragma once

#include <CL/cl.h>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

namespace cl {

    void Check_Error(cl_int ret);

    class Platforms_t {
    protected:
        cl_uint numPlatforms_;
        std::vector<cl_platform_id> platforms_;
    public:
        Platforms_t();

        cl_platform_id operator[](const size_t index);
        void Print_Platform_Info(const size_t index);
    };

    class Devices_t {
    protected:
        cl_uint numDevices_;
        std::vector<cl_device_id> devices_;
    public:
        Devices_t(cl_platform_id platform);

        cl_device_id operator[](const size_t index);
        const std::vector<cl_device_id>& Devices();
        cl_uint Num_Devices();
    };

    class Context_t {
    protected:
        cl_context context_;
    public:
        Context_t(Devices_t devices, cl_context_properties *properties = nullptr);
        cl_context Context() const ;
    };

    class Queue_t {
    protected:
        cl_command_queue cmdQueue_;
    public:
        Queue_t(cl_device_id device, Context_t context, cl_command_queue_properties properties = 0);
    };

    class Buffer_t {
    protected:
    };
}