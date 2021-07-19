#include "host_connectorimpl.hpp"

namespace haf::host
{
HostConnectorImpl::HostConnectorImpl(Host::HostPrivate& host_private) :
    host_private_{host_private}
{}

HostConnectorImpl::~HostConnectorImpl() = default;

}  // namespace haf::host
