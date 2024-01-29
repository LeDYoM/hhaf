#include <backend/include/backend_factory.hpp>
#include <backend/include/backend_register.hpp>
#include <backend_dev/include/iwindow.hpp>

#include <agloader/include/loader.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::backend
{
BackendFactory::BackendFactory() :
    window_{nullptr}, loader_{agloader::createLoader()}
{}

BackendFactory::~BackendFactory()
{
    logger::DisplayLog::debug(StaticTypeName, ": Destroying backend factory");
    for (auto&& loaded_module : loaded_modules_)
    {
        logger::DisplayLog::debug(StaticTypeName,
                                  ": Destroying backend loaded module: ",
                                  loaded_module->moduleName());
        loaded_module->emptyRegisteredFactories();
        loaded_module->finish();
        loader_->unloadModule(loaded_module->moduleName().c_str());
        loaded_module.reset();
    }
    loaded_modules_.clear();

    agloader::destroyLoader();
    loader_ = nullptr;
    logger::DisplayLog::debug(StaticTypeName, ": backend factory destroyed");
}

bool BackendFactory::loadBackendFile(htps::str const& file_name)
{
    logger::DisplayLog::debug(StaticTypeName,
                              ": Going to load backend module: ", file_name);

    if (loader_->loadModule(file_name.c_str()))
    {
        // Get the function pointer to load and unload the backend module
        auto const fp_init_backend_client_library{
            loader_->loadMethod<p_initBackendClient>(file_name.c_str(),
                                                     "init_lib")};
        auto const fp_finish_backend_client_library{
            loader_->loadMethod<p_initBackendClient>(file_name.c_str(),
                                                     "finish_lib")};

        if (fp_init_backend_client_library != nullptr &&
            fp_finish_backend_client_library != nullptr)
        {
            // The loaded client library contains init and destroy
            BackendRegisterUptr backend_register{
                muptr<BackendRegister>(file_name)};

            backend_register->setLibFuncs(fp_init_backend_client_library,
                                          fp_finish_backend_client_library);
            if (backend_register->init())
            {
                bool const result{backend_register->fillRegisteredFactories()};

                if (result)
                {
                    selectFactoriesToUse(backend_register);
                    loaded_modules_.push_back(htps::move(backend_register));
                }
                return result;
            }
        }
    }
    return false;
}

template <typename T>
void updateFactory(T*& global_factory, T* const registered_factory) noexcept
{
    if (global_factory == nullptr)
    {
        global_factory = registered_factory;
    }
}

void BackendFactory::selectFactoriesToUse(
    BackendRegisterUptr const& backend_register) noexcept
{
    updateFactory(window_, backend_register->window_);
}

bool BackendFactory::isWindowFactoryAvailable() const noexcept
{
    return window_ != nullptr;
}

rptr<IWindow> BackendFactory::getWindow() const noexcept
{
    return window_;
}

}  // namespace haf::backend
