#pragma once

#ifndef HAF_HOST_PRIVATE_INCLUDE_HPP
#define HAF_HOST_PRIVATE_INCLUDE_HPP

#include <hosted_app/include/iapp.hpp>
#include <haf/system/include/isystemcontroller.hpp>
#include <loader/include/loader.hpp>
#include <mtypes/include/parpar.hpp>
#include <mtypes/include/object.hpp>

using namespace mtps;

namespace haf::sys
{
class Host::HostPrivate final
{
public:
    HostPrivate(const int argc, char const* const argv[]) :
        argc_{argc},
        argv_{argv},
        params_{parpar::create(argc, argv)},
        // Hardcoded default configuration
        // TODO
        configuration_{{}}
    {}

    bool parseCommandLineParameters()
    {
        if (params_.hasParameters())
        {
        }
        return true;
    }
    parpar::ParametersParser params_;

    Dictionary<str> configuration_;
    rptr<IApp> iapp_{nullptr};
    SystemControllerLoader system_loader_;

    inline rptr<ISystemController> systemController() noexcept
    {
        return system_loader_.systemController();
    }

    inline rptr<ISystemController const> systemController() const noexcept
    {
        return system_loader_.systemController();
    }

    int const argc_;
    char const* const* const argv_;
};

}  // namespace haf::sys

#endif
