#ifndef HAF_HOST_HOST_CONNECTOR_INCLUDE_HPP
#define HAF_HOST_HOST_CONNECTOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <host_connector/include/ihost_connector.hpp>

namespace haf::host
{
class HostConnectorImpl;

class HostConnector final : public IHostConnector
{
public:
    HostConnector(htps::uptr<HostConnectorImpl> host_connector_impl);
    ~HostConnector() override;

    bool loadApplication(htps::str const& app_name) override;

private:
    htps::uptr<HostConnectorImpl> host_connector_impl_;
};

}  // namespace haf::host

#endif
