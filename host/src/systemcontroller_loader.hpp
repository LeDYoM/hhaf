#ifndef HAF_HOST_SYSTEM_CONTROLLER_LOADER_INCLUDE_HPP
#define HAF_HOST_SYSTEM_CONTROLLER_LOADER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/system/isystemcontroller.hpp>

namespace agloader
{
class Loader;
}

namespace haf::host
{
class SystemControllerLoader final
{
public:
    using CreateSystemController_t  = haf::sys::ISystemController* (*)();
    using DestroySystemController_t = void (*)(haf::sys::ISystemController*);

    SystemControllerLoader() = default;
    ~SystemControllerLoader();

    enum class ResultType : htps::u32
    {
        Success            = 0,
        CannotCreateLoader = 1U,
        ObjectNotFound     = 2U,
        CreateNotFound     = 3U,
        DestroyNotFound    = 4U,
        NoFunctionsFound   = 5U
    };

    [[nodiscard]] ResultType loadFunctions();
    [[nodiscard]] bool create();
    void destroy();
    [[nodiscard]] htps::rptr<haf::sys::ISystemController> systemController() noexcept;
    [[nodiscard]] htps::rptr<haf::sys::ISystemController const> systemController()
        const noexcept;

private:
    htps::rptr<agloader::Loader> loader_{nullptr};
    htps::rptr<haf::sys::ISystemController> system_controller_{nullptr};
    CreateSystemController_t fp_haf_create_system_controller_;
    DestroySystemController_t fp_haf_destroy_system_controller_;
};
}  // namespace haf::host

#endif
