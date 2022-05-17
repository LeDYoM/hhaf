#ifndef HAF_BACKEND_IRESOURCE_MANAGER_INCLUDE_HPP
#define HAF_BACKEND_IRESOURCE_MANAGER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <backend_dev/include/iresource_descriptor.hpp>
#include <backend_dev/include/itexture.hpp>

namespace haf::backend
{
class IResourceManager
{
protected:
    ~IResourceManager() = default;

public:
    virtual bool loadResourceForResource(
        IResourceDescriptor const& resource_descriptor) = 0;
//    virtual bool addExternalTexture(htps::rptr<ITexture const> texture) = 0;
};
}  // namespace haf::res

#endif
