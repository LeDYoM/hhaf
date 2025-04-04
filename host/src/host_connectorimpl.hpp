#ifndef HAF_HOST_HOST_CONNECTOR_IMPL_INCLUDE_HPP
#define HAF_HOST_HOST_CONNECTOR_IMPL_INCLUDE_HPP

#include "host_internal.hpp"

namespace haf::host
{
class HostConnectorImpl final
{
public:
    HostConnectorImpl(HostInternal& host_internal);
    ~HostConnectorImpl();

private:
    HostInternal& host_internal_;
};

}  // namespace haf::host

#endif
