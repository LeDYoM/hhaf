#include "systemcontroller_loader.hpp"

#include <hlog/include/hlog.hpp>
#include <agloader/include/loader.hpp>

using namespace htps;

namespace
{
constexpr char const haf_library[] = "haf";
}

namespace haf::host
{
SystemControllerLoader::SystemControllerLoader() :
    loader_{nullptr},
    system_controller_{nullptr},
    fp_haf_create_system_controller_{nullptr},
    fp_haf_destroy_system_controller_{nullptr}
{}

SystemControllerLoader::~SystemControllerLoader()
{
    destroy();

    if (loader_)
    {
        loader_->unloadModule(haf_library);
        loader_ = nullptr;
    }
    fp_haf_create_system_controller_ = nullptr;
    fp_haf_destroy_system_controller_ = nullptr;
    agloader::destroyLoader();
}

SystemControllerLoader::ResultType SystemControllerLoader::loadFunctions()
{
    ResultType result{ResultType::Success};

    if (fp_haf_create_system_controller_ == nullptr &&
        fp_haf_destroy_system_controller_ == nullptr)
    {

        if (loader_ == nullptr)
        {
            loader_ = agloader::createLoader();
        }

        if (!loader_)
        {
            return ResultType::CannotCreateLoader;
        }

        if (loader_->loadModule(haf_library))
        {
            fp_haf_create_system_controller_ =
                reinterpret_cast<CreateSystemController_t>(
                    loader_->loadMethod(haf_library, "createSystemController"));

            if (!fp_haf_create_system_controller_)
            {
                result = ResultType::CreateNotFound;
            }

            fp_haf_destroy_system_controller_ =
                reinterpret_cast<DestroySystemController_t>(loader_->loadMethod(
                    haf_library, "destroySystemController"));

            if (!fp_haf_destroy_system_controller_)
            {
                fp_haf_create_system_controller_ = nullptr;
                result = (result == ResultType::CreateNotFound)
                    ? ResultType::NoFunctionsFound
                    : ResultType::DestroyNotFound;
            }

            if (result != ResultType::Success)
            {
                loader_->unloadModule(haf_library);
            }
        }
        else
        {
            result = ResultType::ObjectNotFound;
        }
    }
    return result;
}

bool SystemControllerLoader::create()
{
    if (fp_haf_create_system_controller_ != nullptr)
    {
        system_controller_ = (*fp_haf_create_system_controller_)();
    }

    return (system_controller_ != nullptr);
}

void SystemControllerLoader::destroy()
{
    if (system_controller_ != nullptr)
    {
        if (fp_haf_destroy_system_controller_)
        {
            (*fp_haf_destroy_system_controller_)(system_controller_);
        }
        system_controller_ = nullptr;
    }
    fp_haf_destroy_system_controller_ = nullptr;
}

rptr<haf::sys::ISystemController>
SystemControllerLoader::systemController() noexcept
{
    return system_controller_;
}

rptr<haf::sys::ISystemController const>
SystemControllerLoader::systemController() const noexcept
{
    return system_controller_;
}

}  // namespace haf::host
