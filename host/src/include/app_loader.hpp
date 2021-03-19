#ifndef HAF_HOST_APP_LOADER_INCLUDE_HPP
#define HAF_HOST_APP_LOADER_INCLUDE_HPP

#include "managed_app.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/str.hpp>

namespace haf::host
{
/**
 * @brief Class to perform a load of an app in memory.
 * This class does not manage the memory of the loaded app or initializes it.
 */
class AppLoader final
{
public:
    ///
    /// @return

    /**
     * @brief Method to load an app.
     *
     * @param file File name
     * @return ManagedApp Instance of the loaded app or nullptr
     * in case of failure.
     */
    ManagedApp loadApp(const htps::str& file) const;
    ManagedApp loadApp(p_initApp init_app, p_finishApp finish_app) const;
    bool unloadApp(ManagedApp& managed_app) const;
};
}  // namespace haf::host

#endif
