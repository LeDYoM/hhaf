#include "host_connector.hpp"
#include "host_connectorimpl.hpp"

namespace haf::host
{
HostConnector::HostConnector(
    htps::uptr<HostConnectorImpl> host_connector_impl) :
    host_connector_impl_{std::move(host_connector_impl)}
{}

HostConnector::~HostConnector() = default;

bool HostConnector::loadApplication(htps::str const& app_name)
{
    (void)(app_name);
    return true;
}

}  // namespace haf::host
