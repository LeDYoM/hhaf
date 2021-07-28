#ifndef HAF_HOST_APP_LOADER_INCLUDE_HPP
#define HAF_HOST_APP_LOADER_INCLUDE_HPP

#include "managed_app.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/str.hpp>
#include <agloader/include/loader.hpp>

namespace haf::host
{
/**
 * @brief Class to perform a load of an app in memory.
 * This class does not manage the memory of the loaded app or initializes it.
 */
class AppLoader final
{
public:
    AppLoader();
    ~AppLoader();
    /**
     * @brief Method to load an app.
     *
     * @param file File name
     * @return ManagedApp Instance of the loaded app or nullptr
     * in case of failure.
     */
    ManagedApp loadApp(htps::str const& file);

    /**
     * @brief Method to unload an app and free its memory
     *
     * @param managed_app Object containing the app to unload
     * @return true App unloaded successfully
     * @return false Problem unloading the app
     */
    bool unloadApp(ManagedApp& managed_app) const;

private:
    ManagedApp loadApp(p_initApp init_app,
                       p_finishApp finish_app,
                       htps::str const& origin_file) const;
    agloader::Loader* loader_{nullptr};
};
}  // namespace haf::host

#endif
