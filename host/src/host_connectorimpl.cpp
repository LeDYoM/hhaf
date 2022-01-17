#include "host_connectorimpl.hpp"

namespace haf::host
{
HostConnectorImpl::HostConnectorImpl(HostInternal& host_internal) :
    host_internal_{host_internal}
{}

HostConnectorImpl::~HostConnectorImpl() = default;

}  // namespace haf::host
