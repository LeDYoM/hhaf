#ifndef HAF_HOST_SYSTEM_CONTROLLER_LOADER_INCLUDE_HPP
#define HAF_HOST_SYSTEM_CONTROLLER_LOADER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <host_haf_interface/include/isystem_controller.hpp>

namespace agloader
{
class Loader;
}

namespace haf::host
{
class SystemControllerLoader final
{
public:
    using CreateSystemController_t = haf::sys::ISystemController* (*)();

    SystemControllerLoader();
    ~SystemControllerLoader();

    enum class ResultType : htps::u32
    {
        Success            = 0U,
        CannotCreateLoader = 1U,
        ObjectNotFound     = 2U,
        CreateNotFound     = 3U,
    };

    [[nodiscard]] ResultType loadFunctions();
    [[nodiscard]] sys::UptrSystemController create();

private:
    htps::rptr<agloader::Loader> loader_;
    CreateSystemController_t fp_haf_create_system_controller_;
};
}  // namespace haf::host

#endif
