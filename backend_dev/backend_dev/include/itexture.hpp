#ifndef HAF_BACKEND_ITEXTURE_HPP
#define HAF_BACKEND_ITEXTURE_HPP

#include <facil_math/include/vector2d.hpp>

#include "iresourceinfo.hpp"

import htypes;

namespace haf::backend
{
class ITexture : public IResourceInfo
{
public:
    virtual ~ITexture()                     = default;
    virtual fmath::vector2du32 size() const = 0;
    virtual htps::u64 uniqueId() const      = 0;
    virtual void bind() const               = 0;
};
}  // namespace haf::backend

#endif
