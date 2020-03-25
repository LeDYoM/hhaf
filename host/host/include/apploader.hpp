#pragma once

#ifndef LIB_HOST_APP_LOADER_INCLUDE_HPP
#define LIB_HOST_APP_LOADER_INCLUDE_HPP

#include "hosted_app/include/iapp.hpp"
#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/str.hpp>

namespace lib::sys
{
struct ManagedApp
{
    mtps::rptr<IApp> app{nullptr};
    p_initApp init_app{nullptr};
    p_finishApp finish_app{nullptr};
};

/// Class to perform a load of an app in memory.
/// This class does not manage the memory of the
/// loaded app or initializes it.
class AppLoader final
{
public:
    /// Method to load an app.
    /// @return Instance of the loaded app or nullptr
    ///     in case of failure.
    ManagedApp loadApp(const mtps::str &file) const;
    ManagedApp loadApp(p_initApp init_app, p_finishApp finish_app) const;
    bool unloadApp(ManagedApp &managed_app) const;
};
} // namespace lib::sys

#endif
