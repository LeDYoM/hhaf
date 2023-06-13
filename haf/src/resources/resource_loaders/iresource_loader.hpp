HAF_PRAGMA_ONCE
#ifndef HAF_RESOURCES_IRESOURCES_LOADER_HPP
#define HAF_RESOURCES_IRESOURCES_LOADER_HPP

#include <haf/include/resources/resource_descriptor.hpp>

namespace haf::res
{
class IResourceLoader
{
protected:
    ~IResourceLoader() = default;

public:
    virtual bool loadResource(
        ResourceDescriptor const& resource_descriptor) = 0;
};
}  // namespace haf::res

#endif
