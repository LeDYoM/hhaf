export module backend_dev:itexture;

import facil_math;
import htypes;

import :iresource_info;

namespace haf::backend
{
export class ITexture : public IResourceInfo
{
public:
    virtual ~ITexture()                     = default;
    virtual fmath::vector2du32 size() const = 0;
    virtual htps::u64 uniqueId() const      = 0;
    virtual void bind() const               = 0;
};
}  // namespace haf::backend
