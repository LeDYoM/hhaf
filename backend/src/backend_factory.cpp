#include <backend/include/backend_factory.hpp>
#include <backend/include/backend_register.hpp>
#include <backend_dev/include/iwindow.hpp>

#include <agloader/include/loader.hpp>

#include "backend_factory_utils.hpp"

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
    for (auto&& loaded_module : loaded_modules_)
    {
        emptyFactories(loaded_module.second, &window_, &textureFactory_,
                       &ttfontFactory_, &shaderFactory_);
        loaded_module.second->finish();
        loaded_module.second.reset();

        loader_->unloadModule(loaded_module.first.c_str());
    }
    loaded_modules_.clear();

    agloader::destroyLoader();
    loader_ = nullptr;
}

bool BackendFactory::loadBackendFile(htps::str const& file_name)
{
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
            BackendRegisterUptr backend_register{muptr<BackendRegister>()};
            backend_register->setLibFuncs(fp_init_backend_client_library,
                                          fp_finish_backend_client_library);
            if (backend_register->init())
            {
                bool const result{fillFactories(
                    backend_register, &window_, &ttfontFactory_,
                    &textureFactory_, &shaderFactory_, &bmpFontFactory_)};

                if (result)
                {
                    loaded_modules_.emplace_back(file_name,
                                                 htps::move(backend_register));
                }
                return result;
            }
        }
    }
    return false;
}

bool BackendFactory::isWindowFactoryAvailable() const noexcept
{
    return window_ != nullptr;
}

bool BackendFactory::isRenderTargetAvailable() const noexcept
{
    return render_target_ != nullptr;
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

rptr<IRenderTarget> BackendFactory::getRenderTarget() const noexcept
{
    return render_target_;
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
