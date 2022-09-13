#include <backend/include/backend_factory.hpp>
#include <backend/include/backend_register.hpp>
#include <backend_dev/include/iwindow.hpp>

#include <agloader/include/loader.hpp>

#include "backend_log.hpp"

using namespace htps;

namespace haf::backend
{
BackendFactory::BackendFactory() :
    window_{nullptr},
    textureFactory_{nullptr},
    ttfontFactory_{nullptr},
    shaderFactory_{nullptr},
    bmpFontFactory_{nullptr},
    loader_{agloader::createLoader()}
{}

BackendFactory::~BackendFactory()
{
    BackendLogDisplayer::debug("Destroying backend factory");
    for (auto&& loaded_module : loaded_modules_)
    {
        BackendLogDisplayer::debug("Destroying backend loaded module: ",
                                   loaded_module->moduleName());
        loaded_module->emptyRegisteredFactories();
        loaded_module->finish();
        loader_->unloadModule(loaded_module->moduleName().c_str());
        loaded_module.reset();
    }
    loaded_modules_.clear();

    agloader::destroyLoader();
    loader_ = nullptr;
    BackendLogDisplayer::debug("backend factory destroyed");
}

bool BackendFactory::loadBackendFile(htps::str const& file_name)
{
    BackendLogDisplayer::debug("Going to load backend module: ", file_name);

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
    updateFactory(ttfontFactory_, backend_register->ttfontFactory_);
    updateFactory(bmpFontFactory_, backend_register->bmpFontFactory_);
    updateFactory(textureFactory_, backend_register->textureFactory_);
    updateFactory(shaderFactory_, backend_register->shaderFactory_);
}

bool BackendFactory::isWindowFactoryAvailable() const noexcept
{
    return window_ != nullptr;
}

bool BackendFactory::isTextureFactoryAvailable() const noexcept
{
    return textureFactory_ != nullptr;
}

bool BackendFactory::isShaderFactoryAvailable() const noexcept
{
    return shaderFactory_ != nullptr;
}

bool BackendFactory::isBMPFontFactoryAvailable() const noexcept
{
    return bmpFontFactory_ != nullptr;
}

bool BackendFactory::isTTFontFactoryAvailable() const noexcept
{
    return ttfontFactory_ != nullptr;
}

rptr<IWindow> BackendFactory::getWindow() const noexcept
{
    return window_;
}

rptr<ITextureFactory> BackendFactory::getTextureFactory() const noexcept
{
    return textureFactory_;
}

rptr<ITTFontFactory> BackendFactory::getTTFontFactory() const noexcept
{
    return ttfontFactory_;
}

rptr<IShaderFactory> BackendFactory::getShaderFactory() const noexcept
{
    return shaderFactory_;
}

rptr<IBMPFontFactory> BackendFactory::getBMPFontFactory() const noexcept
{
    return bmpFontFactory_;
}

ITextureFactory& BackendFactory::textureFactory() const
{
    return *getTextureFactory();
}

ITTFontFactory& BackendFactory::ttfontFactory() const
{
    return *getTTFontFactory();
}

IShaderFactory& BackendFactory::shaderFactory() const
{
    return *getShaderFactory();
}

IBMPFontFactory& BackendFactory::bmpFontFactory() const
{
    return *getBMPFontFactory();
}
}  // namespace haf::backend
