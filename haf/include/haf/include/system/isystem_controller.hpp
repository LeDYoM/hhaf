HTPS_PRAGMA_ONCE
#ifndef HAF_ISYSTEMCONTROLLER_INTERFACE_INCLUDE_HPP
#define HAF_ISYSTEMCONTROLLER_INTERFACE_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf
{
class IApp;
}

namespace haf::host
{
class IHostConnector;
}

namespace haf::backend
{
class BackendFactory;
}

namespace haf::sys
{
class ISystemController
{
public:
    virtual ~ISystemController() {}

    virtual void init(htps::rptr<haf::IApp> iapp,
                      htps::rptr<host::IHostConnector> const host_connector,
                      htps::rptr<backend::BackendFactory> const backend_factory,
                      int const argc,
                      char const* const argv[]) = 0;
    virtual bool preUpdate()                    = 0;
    virtual bool update()                       = 0;
    virtual bool postUpdate()                   = 0;
    virtual void terminate()                    = 0;
};

using UptrSystemController = htps::uptr<sys::ISystemController>;

}  // namespace haf::sys

#endif
