module;

#include <host_haf_interface/include/isystem_controller.hpp>

export module host:system_controller_loader;

import htypes;
import agloader;

namespace
{
constexpr char const haf_library[] = "haf";
}

namespace haf::host
{
class SystemControllerLoader final
{
public:
    using CreateSystemController_t = haf::sys::ISystemController* (*)();

    SystemControllerLoader() :
        loader_{nullptr}, fp_haf_create_system_controller_{nullptr}
    {}

    ~SystemControllerLoader()
    {
        /*
            DisplayLog::debug("SystemControllers created: ", created_);
            DisplayLog::debug("SystemControllers deleted: ", deleted_);
            LogAsserter::log_assert(
                created_ == deleted_,
                "Different number of created and deleted system controllers: ",
                created_, " and ", deleted_);
        */
        if (loader_)
        {
            loader_->unloadModule(haf_library);
        }
        agl::destroyLoader();

        fp_haf_create_system_controller_ = nullptr;
    }

    enum class ResultType : htps::u32
    {
        Success            = 0U,
        CannotCreateLoader = 1U,
        ObjectNotFound     = 2U,
        CreateNotFound     = 3U,
    };

    [[nodiscard]] ResultType loadFunctions()
    {
        ResultType result{ResultType::Success};

        if (fp_haf_create_system_controller_ == nullptr)
        {

            if (loader_ == nullptr)
            {
                loader_ = agl::createLoader();
            }

            if (!loader_)
            {
                return ResultType::CannotCreateLoader;
            }

            if (loader_->loadModule(haf_library))
            {
                fp_haf_create_system_controller_ =
                    reinterpret_cast<CreateSystemController_t>(
                        loader_->loadMethod(haf_library,
                                            "createSystemController"));

                if (!fp_haf_create_system_controller_)
                {
                    result = ResultType::CreateNotFound;
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

    [[nodiscard]] sys::UptrSystemController create()
    {
        if (fp_haf_create_system_controller_ != nullptr)
        {
            sys::UptrSystemController result{
                (*fp_haf_create_system_controller_)()};
            return result;
        }
        return nullptr;
    }

private:
    htps::rptr<agl::Loader> loader_;
    CreateSystemController_t fp_haf_create_system_controller_;
};
}  // namespace haf::host
