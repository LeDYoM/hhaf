export module host:app_loader;

import :managed_app;
import htypes;
import agloader;

namespace haf::host
{
/**
 * @brief Class to perform a load of an app in memory.
 * This class does not manage the memory of the loaded app or initializes it.
 */
class AppLoader final
{
public:
    AppLoader() : loader_{agl::createLoader()} {}

    ~AppLoader()
    {
        loader_ = nullptr;
        agl::destroyLoader();
    }

    /**
     * @brief Method to load an app.
     *
     * @param file File name
     * @return ManagedApp Instance of the loaded app or nullptr
     * in case of failure.
     */
    ManagedApp loadApp(htps::str const& file)
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

    /**
     * @brief Method to unload an app and free its memory
     *
     * @param managed_app Object containing the app to unload
     * @return true App unloaded successfully
     * @return false Problem unloading the app
     */
    bool unloadApp(ManagedApp& managed_app) const
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

private:
    ManagedApp loadApp(p_initApp init_app,
                       p_finishApp finish_app,
                       htps::str const& origin_file) const
    {
        // Do the loading if parameters are correct.
        return {init_app ? init_app() : nullptr, init_app, finish_app,
                origin_file};
    }

    agl::Loader* loader_{nullptr};
};
}  // namespace haf::host
