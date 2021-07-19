#ifndef HAF_HOST_IHOST_CONNECTOR_INCLUDE_HPP
#define HAF_HOST_IHOST_CONNECTOR_INCLUDE_HPP

#include <htypes/include/str.hpp>

namespace haf::host
{
class IHostConnector
{
public:
    /**
     * @brief Empty defaulted constexpr constructor.
     */
    constexpr IHostConnector() noexcept {}

//    bool loadApplication()

    /**
     * @brief Destroy the HostConnector object. This destructor is intended
     * to be empty in this class
     */
    virtual ~IHostConnector() {}

    virtual bool loadApplication(htps::str const& app_name) = 0;
};

}  // namespace haf::host

#endif
