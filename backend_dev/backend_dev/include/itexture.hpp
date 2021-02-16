#ifndef HAF_BACKEND_ITEXTURE_HPP
#define HAF_BACKEND_ITEXTURE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include "iresourceinfo.hpp"

namespace haf::backend
{
class ITexture : public IResourceInfo
{
public:
    ITexture() {}
    virtual ~ITexture() {}

    virtual mtps::vector2du32 size() const = 0;
};
}  // namespace haf::backend

#endif
