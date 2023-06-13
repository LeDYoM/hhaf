#include "sfml_backend_manager.hpp"
#include <backend_client/include/default_factory.hpp>

#include "sfml_render_window.hpp"

void SFMLBackendManager::create()
{
    using namespace haf::backend;
    using namespace haf::backend::client;
    using namespace haf::backend::sfmlb;

    createFactoryOfFactories<DefaultFactoryOf<IWindow, SFMLRenderWindow>>();
}
