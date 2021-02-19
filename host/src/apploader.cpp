#include <host/include/apploader.hpp>
#include <loader/include/loader.hpp>

using namespace htps;

namespace haf::host
{
ManagedApp AppLoader::loadApp(const str &file) const
{
    using namespace loader;
    auto *loader(createLoader());

    if (loader->loadModule(file.c_str()))
    {
        auto fp_init_app = (p_initApp)loader->loadMethod(file.c_str(), "createApp");
        auto fp_destroy_app = (p_finishApp)loader->loadMethod(file.c_str(), "destroyApp");

        return loadApp(fp_init_app, fp_destroy_app);
    }
    return ManagedApp();
}

ManagedApp AppLoader::loadApp(p_initApp init_app, p_finishApp finish_app) const
{
    // Do the loading if parameters are correct.
    return {init_app ? init_app() : nullptr, init_app, finish_app};
}

bool AppLoader::unloadApp(ManagedApp &managed_app) const
{
    using namespace loader;

    bool result{false};

    if (managed_app.finish_app)
    {
        managed_app.finish_app(managed_app.app);
        result = true;
    }
    else if (managed_app.app)
    {
        delete managed_app.app;
        result = true;
    }

    managed_app.app = nullptr;
    managed_app.init_app = nullptr;
    managed_app.finish_app = nullptr;
    destroyLoader();
    return result;
}

} // namespace haf::sys
