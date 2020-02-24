#include <backend_dev/include/client/interfaces.hpp>

#include "renderwindow.hpp"
#include "ttfontfactory.hpp"
#include "texturefactory.hpp"
#include "shaderfactory.hpp"

#ifdef _WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C"
#endif

struct BackendManager : lib::backend::client::DefaultBackendManager
{
    void create() override
    {
        using namespace lib;
        using namespace lib::backend;
        using namespace lib::backend::client;
        using namespace lib::backend::sfmlb;

        createFactoryOfFactories<DefaultFactoryOf<IWindowProviderInfo, WindowBackendInfo>>(factories);
        createFactoryOfFactories<DefaultFactoryOf<IWindow, RenderWindow>>(factories);
        createFactoryOfFactories<DefaultFactoryOf<ITTFontFactory, TTFontFactory>>(factories);
        createFactoryOfFactories<DefaultFactoryOf<ITextureFactory, TextureFactory>>(factories);
        createFactoryOfFactories<DefaultFactoryOf<IShaderFactory, ShaderFactory>>(factories);
    }
};

BackendManager *backend_manager{nullptr};

EXPORT bool init_lib(lib::backend::IBackendRegister *const ibackend_register)
{
    return lib::backend::client::default_init_function(&backend_manager, ibackend_register);
}

EXPORT bool finish_lib(lib::backend::IBackendRegister *const ibackend_register)
{
    return lib::backend::client::default_finish_function(&backend_manager, ibackend_register);
}
