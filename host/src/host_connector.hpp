#ifndef HAF_HOST_HOST_CONNECTOR_INCLUDE_HPP
#define HAF_HOST_HOST_CONNECTOR_INCLUDE_HPP

#include <host_connector/include/ihost_connector.hpp>

namespace haf::host
{
class HostConnector final : public IHostConnector
{
public:
    HostConnector();
};

}  // namespace haf::host

#endif
