#pragma once

#ifndef HAF_HOST_SYSTEM_CONTROLLER_LOADER_INCLUDE_HPP
#define HAF_HOST_SYSTEM_CONTROLLER_LOADER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/isystemcontroller.hpp>

namespace loader
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
    mtps::rptr<ISystemController> systemController() noexcept;
    mtps::rptr<ISystemController const> systemController() const noexcept;

private:
    mtps::rptr<loader::Loader> loader_{nullptr};
    mtps::rptr<ISystemController> system_controller_{nullptr};
    CreateSystemController_t fp_haf_create_system_controller_;
    DestroySystemController_t fp_haf_destroy_system_controller_;
};
}  // namespace haf::host

#endif
