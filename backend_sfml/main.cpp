#include <backend_dev/include/interfaces.hpp>

#include "renderwindow.hpp"
#include "ttfontfactory.hpp"
#include "texturefactory.hpp"
#include "shaderfactory.hpp"

#ifdef _WIN32
    #define EXPORT   extern "C" __declspec( dllexport )
#else
    #define EXPORT   extern "C"
#endif

template <typename T>
void createFactoryOfFactories(lib::vector<lib::uptr<lib::backend::IAutoRegisterFactory>> &factories)
{
    auto f(lib::muptr<lib::backend::AutoRegisterFactory<T::Interface>>());
    f.get()->create(lib::muptr<T>());
    factories.push_back(std::move(f));
}

struct BackendManager final : lib::backend::IBackendManager
{
    lib::vector<lib::uptr<lib::backend::IAutoRegisterFactory>> factories;

    void create() override
    {
        using namespace lib;
        using namespace lib::backend;
        using namespace lib::backend::sfmlb;

        createFactoryOfFactories<DefaultFactoryOf<IWindowProviderInfo, WindowBackendInfo>>(factories);
        createFactoryOfFactories<DefaultFactoryOf<IWindow, RenderWindow>>(factories);
        createFactoryOfFactories<DefaultFactoryOf<ITTFontFactory, TTFontFactory>>(factories);
        createFactoryOfFactories<DefaultFactoryOf<ITextureFactory, TextureFactory>>(factories);
        createFactoryOfFactories<DefaultFactoryOf<IShaderFactory, ShaderFactory>>(factories);
    }

    void setFactories(lib::backend::IBackendRegister*const backend_register) override
    {
        for (const auto &factory : factories)
        {
            factory.get()->setFactory(backend_register);
        }
    }

    void resetFactories(lib::backend::IBackendRegister*const backend_register) override
    {
        for (const auto &factory : factories)
        {
            factory.get()->resetFactory(backend_register);
        }
    }

    void destroy()  override
    {
        for (const auto &factory : factories)
        {
            factory.get()->destroy();
        }
    }

    ~BackendManager() override
    {
        destroy();
    }
};

BackendManager *backend_manager{ nullptr };

EXPORT bool init_lib(lib::backend::IBackendRegister*const ibackend_register)
{
    if (!backend_manager)
    {
        backend_manager = new BackendManager;
        backend_manager->create();

        backend_manager->setFactories(ibackend_register);
        return true;
    }
    return false;
}

EXPORT bool finish_lib(lib::backend::IBackendRegister*const ibackend_register)
{
    if (backend_manager)
    {
        backend_manager->resetFactories(ibackend_register);
        backend_manager->destroy();
        delete backend_manager;
        backend_manager = nullptr;
        return true;
    }

    return false;
}
