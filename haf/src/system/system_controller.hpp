#ifndef HAF_SYSTEM_CONTROLLER_INCLUDE_HPP
#define HAF_SYSTEM_CONTROLLER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include "system_provider.hpp"
#include <haf/include/system/isystem_controller.hpp>

namespace haf::backend
{
class BackendFactory;
}

namespace haf::host
{
class IHostConnector;
}

namespace haf::sys
{
class SystemController final : public ISystemController, SystemProvider
{
public:
    SystemController();
    ~SystemController() override;

    void init(htps::rptr<IApp> iapp,
              htps::rptr<host::IHostConnector> const host_connector,
              htps::rptr<backend::BackendFactory> const backend_factory,
              int const argc,
              char const* const argv[]) override;
    bool preUpdate() override;
    bool update() override;
    bool postUpdate() override;
    void terminate() override;
};
}  // namespace haf::sys

#endif
