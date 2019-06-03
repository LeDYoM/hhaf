#pragma once

#ifndef LIB_HOST_APP_LOADER_INCLUDE_HPP
#define LIB_HOST_APP_LOADER_INCLUDE_HPP

#include <lib/include/iapp.hpp>
#include <mtypes/include/types.hpp>

namespace lib::core
{
    struct IAppDeleterFunctor
    {
        void operator()(IApp* iapp) const
        {
            delete iapp;
        }
    };

    using AppUniquePtr = uptr<IApp, IAppDeleterFunctor>;

    /// Class to perform a load of an app in memory.
    /// This class does not manage the memory of the
    /// loaded app or initializes it.
    class AppLoader final
    {
    public:
        /// Method to load an app.
        /// @return Instance of the loaded app or nullptr
        ///     in case of failure.
        AppUniquePtr loadApp(const str& file) const;
    };
}

#endif
