export module host:host_connector_impl;

import :host_internal;

namespace haf::host
{
class HostConnectorImpl final
{
public:
    HostConnectorImpl(HostInternal& host_internal) :
        host_internal_{host_internal}
    {}

    ~HostConnectorImpl() = default;

private:
    HostInternal& host_internal_;
};

}  // namespace haf::host
