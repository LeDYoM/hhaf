#include <backend/include/backendfactory.hpp>
#include <backend/include/backendregister.hpp>
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
    bmpFontFactory_{nullptr}
{
    auto* const loader{agloader::createLoader()};

    static const char* sh_name = "bsfml";
    if (loader->loadModule(sh_name))
    {
        // Get the function pointer to load and unload the backend module
        const auto fp_init_haf = reinterpret_cast<p_initBackendClient>(
            loader->loadMethod(sh_name, "init_lib"));
        const auto fp_finish_haf = reinterpret_cast<p_initBackendClient>(
            loader->loadMethod(sh_name, "finish_lib"));

        if (fp_init_haf != nullptr && fp_finish_haf != nullptr)
        {
            backend_register_ = muptr<BackendRegister>();
            backend_register_->setLibFuncs(fp_init_haf, fp_finish_haf);
            backend_register_->init();
        }

        fillFactories(backend_register_, &window_, &ttfontFactory_,
                      &textureFactory_, &shaderFactory_);
    }
}

BackendFactory::~BackendFactory()
{
    emptyFactories(backend_register_, &window_, &textureFactory_,
                   &ttfontFactory_, &shaderFactory_);
    backend_register_->finish();
    backend_register_.reset();

    agloader::destroyLoader();
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
