#include <backend/include/backendfactory.hpp>
#include <backend/include/backendregister.hpp>
#include <backend_dev/include/iwindow.hpp>

#include <agloader/include/loader.hpp>

using namespace htps;

namespace haf::backend
{
namespace
{
template <typename FactoryType>
bool fillFactory(const uptr<BackendRegister>& backend_register,
                 FactoryType** factory_to_fill)
{
    if (auto factory(backend_register->getFactory<IFactoryOf<FactoryType>>());
        factory != nullptr)
    {
        (*factory_to_fill) = factory->create();
        return (*factory_to_fill) != nullptr;
    }
    return false;
}

template <typename FactoryType>
bool emptyFactory(const uptr<BackendRegister>& backend_register,
                  FactoryType** factory_to_empty)
{
    if (auto factory(backend_register->getFactory<IFactoryOf<FactoryType>>());
        factory != nullptr)
    {
        if (factory_to_empty != nullptr && *factory_to_empty != nullptr)
        {
            factory->destroy(*factory_to_empty);
            (*factory_to_empty) = nullptr;
            return true;
        }
    }
    return false;
}
}  // namespace

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
        const auto fp_init_haf =
            reinterpret_cast<p_initBackendClient>(loader->loadMethod(sh_name, "init_lib"));
        const auto fp_finish_haf =
            reinterpret_cast<p_initBackendClient>(loader->loadMethod(sh_name, "finish_lib"));

        if (fp_init_haf != nullptr && fp_finish_haf != nullptr)
        {
            backend_register_ = muptr<BackendRegister>();
            backend_register_->setLibFuncs(fp_init_haf, fp_finish_haf);
            backend_register_->init();
        }

        bool result{fillFactory(backend_register_, &window_)};
        result &= fillFactory(backend_register_, &ttfontFactory_);
        result &= fillFactory(backend_register_, &textureFactory_);
        result &= fillFactory(backend_register_, &shaderFactory_);
    }
}

BackendFactory::~BackendFactory()
{
    bool result{emptyFactory(backend_register_, &window_)};
    result &= emptyFactory(backend_register_, &textureFactory_);
    result &= emptyFactory(backend_register_, &ttfontFactory_);
    result &= emptyFactory(backend_register_, &shaderFactory_);
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
