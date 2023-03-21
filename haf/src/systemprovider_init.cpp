#include <system/system_controller.hpp>
#include <hlog/include/hlog.hpp>

#ifdef _WIN32
#define HAF_SYSTEM_API extern "C" __declspec(dllexport)
#else
#define HAF_SYSTEM_API extern "C" __attribute__((visibility("default")))
#endif

HAF_SYSTEM_API haf::sys::ISystemController* createSystemController()
{
    return new haf::sys::SystemController();
}
