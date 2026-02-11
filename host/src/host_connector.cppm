module;

#include <host_connector/include/ihost_connector.hpp>

export module host:host_connector;

import htypes;
import :host_connector_impl;

namespace haf::host
{

class HostConnector final : public IHostConnector
{
public:
    HostConnector(htps::uptr<HostConnectorImpl> host_connector_impl) :
        m_host_connector_impl{htps::move(host_connector_impl)}
    {}

    ~HostConnector() = default;

    bool loadApplication(htps::str const& app_name)
    {
        (void)(app_name);
        return true;
    }

private:
    htps::uptr<HostConnectorImpl> m_host_connector_impl;
};

}  // namespace haf::host
