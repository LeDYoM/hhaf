#include "app_loader.hpp"

using namespace htps;

namespace haf::host
{
AppLoader::AppLoader() : loader_{agl::createLoader()}
{}

AppLoader::~AppLoader()
{
    loader_ = nullptr;
    agl::destroyLoader();
}

ManagedApp AppLoader::loadApp(const str& file)
{
    if (loader_->loadModule(file.c_str()))
    {
        p_initApp fp_init_app =
            loader_->loadMethod<p_initApp>(file.c_str(), "createApp");
        p_finishApp fp_destroy_app =
            loader_->loadMethod<p_finishApp>(file.c_str(), "destroyApp");

        return loadApp(fp_init_app, fp_destroy_app, file);
    }

    return ManagedApp();
}

ManagedApp AppLoader::loadApp(p_initApp init_app,
                              p_finishApp finish_app,
                              str const& origin_file) const
{
    // Do the loading if parameters are correct.
    return {init_app ? init_app() : nullptr, init_app, finish_app, origin_file};
}

bool AppLoader::unloadApp(ManagedApp& managed_app) const
{
    using namespace agl;

    bool result{false};

    if (managed_app.finish_app)
    {
        managed_app.finish_app(managed_app.app);
        if (loader_ != nullptr)
        {
            result = loader_->unloadModule(managed_app.origin_file.c_str());
        }
        result = true;
    }
    else if (managed_app.app)
    {
        delete managed_app.app;
        result = true;
    }

    managed_app.app        = nullptr;
    managed_app.init_app   = nullptr;
    managed_app.finish_app = nullptr;
    return result;
}

}  // namespace haf::host
