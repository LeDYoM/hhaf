#include "sfml_backend_manager.hpp"
#include <backend_client/include/default_factory.hpp>

#include "sfml_render_window.hpp"
#include "sfml_render_target.hpp"
#include "sfml_ttfont_factory.hpp"
#include "sfml_texture_factory.hpp"
#include "sfml_shader_factory.hpp"

void SFMLBackendManager::create()
{
    using namespace haf::backend;
    using namespace haf::backend::client;
    using namespace haf::backend::sfmlb;

    createFactoryOfFactories<DefaultFactoryOf<IWindow, SFMLRenderWindow>>();
    createFactoryOfFactories<
        DefaultFactoryOf<IRenderTarget, SFMLRenderTarget>>();
    createFactoryOfFactories<
        DefaultFactoryOf<ITTFontFactory, SFMLTTFontFactory>>();
    createFactoryOfFactories<
        DefaultFactoryOf<ITextureFactory, SFMLTextureFactory>>();
    createFactoryOfFactories<
        DefaultFactoryOf<IShaderFactory, SFMLShaderFactory>>();
}
