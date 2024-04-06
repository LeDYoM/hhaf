#ifndef HAF_SYSTEM_CONTROLLER_INCLUDE_HPP
#define HAF_SYSTEM_CONTROLLER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
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
class SystemController final : public ISystemController, private SystemProvider
{
public:
    SystemController();
    ~SystemController() override;

    SystemController(SystemController const&) = delete;
    SystemController& operator=(SystemController const&) = delete;
    SystemController(SystemController&&)                 = default;
    SystemController& operator=(SystemController&&) = default;

    void init(core::rptr<IApp> iapp,
              core::rptr<host::IHostConnector> const host_connector,
              core::rptr<backend::BackendFactory> const backend_factory,
              int const argc,
              char const* const argv[]) override;
    bool preUpdate() override;
    bool update() override;
    bool postUpdate() override;
    void terminate() override;
};

}  // namespace haf::sys

#endif
