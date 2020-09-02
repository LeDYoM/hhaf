#include <backend_dev/include/client/interfaces.hpp>

#include "renderwindow.hpp"
#include "rendertarget.hpp"
#include "ttfontfactory.hpp"
#include "texturefactory.hpp"
#include "shaderfactory.hpp"

#ifdef _WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C" __attribute__((visibility("default")))
#endif

struct BackendManager : haf::backend::client::DefaultBackendManager
{
    void create() override
    {
        using namespace haf;
        using namespace haf::backend;
        using namespace haf::backend::client;
        using namespace haf::backend::sfmlb;

        createFactoryOfFactories<DefaultFactoryOf<IWindow, RenderWindow>>();
        createFactoryOfFactories<
            DefaultFactoryOf<IRenderTarget, RenderTarget>>();
        createFactoryOfFactories<
            DefaultFactoryOf<ITTFontFactory, TTFontFactory>>();
        createFactoryOfFactories<
            DefaultFactoryOf<ITextureFactory, TextureFactory>>();
        createFactoryOfFactories<
            DefaultFactoryOf<IShaderFactory, ShaderFactory>>();
    }
};

BackendManager* backend_manager{nullptr};

EXPORT bool init_lib(haf::backend::IBackendRegister* const ibackend_register)
{
    return haf::backend::client::default_init_function(&backend_manager,
                                                       ibackend_register);
}

EXPORT bool finish_lib(haf::backend::IBackendRegister* const ibackend_register)
{
    return haf::backend::client::default_finish_function(&backend_manager,
                                                         ibackend_register);
}
