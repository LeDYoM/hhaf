export module backend_dev:iresource_manager;

import :iresource_descriptor;
import :itexture;

import htypes;

namespace haf::backend
{
class IResourceManager
{
protected:
    ~IResourceManager() = default;

public:
    virtual bool loadResourceForResource(
        IResourceDescriptor const& resource_descriptor)               = 0;
    virtual bool setExternalTexture(htps::str const& resource_id,
                                    backend::ITexture const* texture) = 0;
};
}  // namespace haf::backend
