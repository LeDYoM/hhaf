#include <backend/include/backendfactory.hpp>
#include <backend/include/backendregister.hpp>
#include <backend_dev/include/iwindow.hpp>

#include <loader/include/loader.hpp>

namespace haf::backend
{
using namespace mtps;

template <typename FactoryType>
inline bool fillFactory(const uptr<BackendRegister>& backend_register,
                        FactoryType** factory_to_fill)
{
    if (auto factory(backend_register->getFactory<IFactoryOf<FactoryType>>());
        factory)
    {
        (*factory_to_fill) = factory->create();
        return (*factory_to_fill) != nullptr;
    }
    return false;
}

template <typename FactoryType>
inline bool emptyFactory(const uptr<BackendRegister>& backend_register,
                         FactoryType** factory_to_empty)
{
    if (auto factory(backend_register->getFactory<IFactoryOf<FactoryType>>());
        factory)
    {
        if (factory_to_empty && *factory_to_empty)
        {
            factory->destroy(*factory_to_empty);
            (*factory_to_empty) = nullptr;
            return true;
        }
    }
    return false;
}

BackendFactory::BackendFactory()
{
    using namespace loader;
    auto* loader(createLoader());

    static const char* sh_name = "bsfml";
    if (loader->loadModule(sh_name))
    {
        auto fp_init_lib =
            static_cast<p_initLib>(loader->loadMethod(sh_name, "init_lib"));
        auto fp_finish_lib =
            static_cast<p_initLib>(loader->loadMethod(sh_name, "finish_lib"));

        if (fp_init_lib && fp_finish_lib)
        {
            backend_register_ = muptr<BackendRegister>();
            backend_register_->setLibFuncs(fp_init_lib, fp_finish_lib);
            backend_register_->init();
        }

        bool result{fillFactory(backend_register_, &m_windowProviderInfo)};
        result &= fillFactory(backend_register_, &m_window);
        result &= fillFactory(backend_register_, &m_ttfontFactory);
        result &= fillFactory(backend_register_, &m_textureFactory);
        result &= fillFactory(backend_register_, &m_shaderFactory);
    }
}

BackendFactory::~BackendFactory()
{
    bool result{emptyFactory(backend_register_, &m_windowProviderInfo)};
    result &= emptyFactory(backend_register_, &m_window);
    result &= emptyFactory(backend_register_, &m_textureFactory);
    result &= emptyFactory(backend_register_, &m_ttfontFactory);
    result &= emptyFactory(backend_register_, &m_shaderFactory);
    backend_register_->finish();

    backend_register_.reset();

    loader::destroyLoader();
}

IWindow* haf::backend::BackendFactory::getWindow()
{
    return m_window;
}

IWindowProviderInfo* BackendFactory::getWindowProviderInfo() const noexcept
{
    return m_windowProviderInfo;
}

ITextureFactory* BackendFactory::getTextureFactory() const noexcept
{
    return m_textureFactory;
}

ITTFontFactory* BackendFactory::getTTFontFactory() const noexcept
{
    return m_ttfontFactory;
}

IShaderFactory* BackendFactory::getShaderFactory() const noexcept
{
    return m_shaderFactory;
}

IBMPFontFactory* BackendFactory::getBMPFontFactory() const noexcept
{
    return m_bmpFontFactory;
}

IWindowProviderInfo& BackendFactory::windowProviderInfo() const
{
    return *getWindowProviderInfo();
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
