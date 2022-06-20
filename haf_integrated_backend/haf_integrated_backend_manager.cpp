#include "haf_integrated_backend_manager.hpp"
#include "default_bmp_font_factory.hpp"

#include <backend_client/include/default_factory.hpp>
#include <backend_dev/include/ibmp_font.hpp>

void HafIntegratedBackendManager::create()
{
    using namespace haf::backend;
    using namespace haf::backend::client;

    createFactoryOfFactories<
        DefaultFactoryOf<IBMPFontFactory, haf::res::DefaultBMPFontFactory>>();
}
