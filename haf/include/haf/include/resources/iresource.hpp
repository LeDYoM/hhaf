HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_IRESOURCE_INCLUDE_HPP
#define HAF_RESOURCES_IRESOURCE_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/resources/resource_codes.hpp>

namespace haf::res
{
class IResource
{
public:
    virtual constexpr ResourceType resourceType() const noexcept
    {
        return ResourceType::Unknown;
    }

    virtual ~IResource() = default;

    virtual bool isValid() const { return true; }
};

}  // namespace haf::res

#endif
