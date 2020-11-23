#include <CL/opencl.h>
#include <string>

namespace cl {
    namespace detail {
        template<typename T>
        struct ReferenceHandler {
        };

        template<>
        struct ReferenceHandler<cl_mem> {
            static cl_int retain(cl_mem memory) { return ::clRetainMemObject(memory); }

            static cl_int release(cl_mem memory) { return ::clReleaseMemObject(memory); }
        };

        template<>
        struct ReferenceHandler<cl_device_id> {
            static cl_int retain(cl_device_id deviceId) { return ::clRetainDevice(deviceId); }

            static cl_int release(cl_device_id deviceId) { return ::clReleaseDevice(deviceId); }
        };

        template<>
        struct ReferenceHandler<cl_platform_id> {
            static cl_int retain(cl_platform_id platformId) { return CL_SUCCESS; }

            static cl_int release(cl_platform_id deviceId) { return CL_SUCCESS; }
        };

        template<typename cl_type>
        class Wrapper {
        protected:
            cl_type object_;
        public:
            cl_int release() const {
                if (!object_) return CL_SUCCESS;
                return ReferenceHandler<cl_type>::release(object_);
            }

            cl_int retain() const {
                if (!object_) return CL_SUCCESS;
                return ReferenceHandler<cl_type>::retain(object_);
            }

            const cl_type &operator()() const { return object_; }

            cl_type &operator()() { return object_; }

            Wrapper() : object_(nullptr) {}

            Wrapper(cl_type object, bool retainObject);

            ~Wrapper() { release(); }

            cl_type get() const { return object_; }
        };

        template<typename T, cl_int Name>
        struct param_traits {
        };

        template<>
        struct param_traits<cl_platform_info, CL_PLATFORM_NAME> {
            enum {
                value = CL_PLATFORM_NAME
            };
            using type = std::string;
        };

    }

    class Device : public detail::Wrapper<cl_device_id> {
        Device(const Device &dev) : detail::Wrapper<cl_device_id>(dev) {}

        Device &operator=(const Device &dev) {
            detail::Wrapper<cl_device_id>::operator=(dev);
            return *this;
        }

        explicit Device(const cl_device_id &device,
                        bool retainObject = false) :
                detail::Wrapper<cl_device_id>(device, retainObject) {}

        template<cl_device_info name>
        typename detail::param_traits<cl_device_info, name>::type
        getInfo(cl_int *err = NULL) const {
            typename detail::param_traits<cl_device_info, name>::param_type param;
            cl_int result = getInfo(name, &param);
            if (err != nullptr) {
                *err = result;
            }
            return param;
        }

    };

    class Platform : public detail::Wrapper<cl_platform_id> {
        Platform(const Platform &platform) : detail::Wrapper<cl_platform_id>(platform) {}

        Platform &operator=(const Platform &plat) {
            detail::Wrapper<cl_platform_id>::operator=(plat);
            return *this;
        }

        explicit Platform(const cl_platform_id &platform,
                          bool retainObject = false) :
                detail::Wrapper<cl_platform_id>(platform, retainObject) {}
    };


    namespace detail {
        template<typename cl_type>
        Wrapper<cl_type>::Wrapper(cl_type object, bool retainObject) {
            if (retainObject) {
                retain();
            }
        }
    }
}
