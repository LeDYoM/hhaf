#ifndef HAF_HOST_SYSTEM_CONTROLLER_LOADER_INCLUDE_HPP
#define HAF_HOST_SYSTEM_CONTROLLER_LOADER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/system/include/isystemcontroller.hpp>

namespace agloader
{
class Loader;
}

namespace haf::host
{
class SystemControllerLoader final
{
public:
    using CreateSystemController_t  = ISystemController* (*)();
    using DestroySystemController_t = void (*)(ISystemController*);

    SystemControllerLoader() = default;
    ~SystemControllerLoader();

    enum class ResultType
    {
        Success = 0,
        CannotCreateLoader,
        ObjectNotFound,
        CreateNotFound,
        DestroyNotFound,
        NoFunctionsFound
    };

    ResultType loadFunctions();
    bool create();
    void destroy();
    htps::rptr<ISystemController> systemController() noexcept;
    htps::rptr<ISystemController const> systemController() const noexcept;

private:
    htps::rptr<agloader::Loader> loader_{nullptr};
    htps::rptr<ISystemController> system_controller_{nullptr};
    CreateSystemController_t fp_haf_create_system_controller_;
    DestroySystemController_t fp_haf_destroy_system_controller_;
};
}  // namespace haf::host

#endif
