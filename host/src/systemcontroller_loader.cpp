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
    fp_haf_create_system_controller_{nullptr},
    fp_haf_destroy_system_controller_{nullptr}
{}

SystemControllerLoader::~SystemControllerLoader()
{
    DisplayLog::debug("SystemControllers created: ", created_);
    DisplayLog::debug("SystemControllers deleted: ", deleted_);
    LogAsserter::log_assert(
        created_ == deleted_,
        "Different number of created and deleted system controllers: ",
        created_, " and ", deleted_);

    if (loader_)
    {
        loader_->unloadModule(haf_library);
        loader_ = nullptr;
    }

    fp_haf_create_system_controller_  = nullptr;
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

sys::DestructibleSystemController SystemControllerLoader::create()
{
    if (fp_haf_create_system_controller_ != nullptr)
    {
        sys::DestructibleSystemController result{
            (*fp_haf_create_system_controller_)(),
            [this](sys::ISystemController* system_controller) {
                if (system_controller != nullptr)
                {
                    ++deleted_;
                    destroy(system_controller);
                }
            }};
        ++created_;
        return result;
    }
    return nullptr;
}

void SystemControllerLoader::destroy(sys::ISystemController* system_controller)
{
    if (system_controller != nullptr)
    {
        if (fp_haf_destroy_system_controller_ != nullptr)
        {
            (*fp_haf_destroy_system_controller_)(system_controller);
        }
        else
        {
            DisplayLog::error("Cannot destroy a system loader because the "
                              "destruction function is not loaded");
        }
        system_controller = nullptr;
    }
}

}  // namespace haf::host
