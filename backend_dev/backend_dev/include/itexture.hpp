#ifndef HAF_BACKEND_ITEXTURE_HPP
#define HAF_BACKEND_ITEXTURE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include "iresourceinfo.hpp"

namespace haf::backend
{
class ITexture : public IResourceInfo
{
protected:
    virtual ~ITexture() = default;
public:
    virtual htps::vector2du32 size() const = 0;
};
}  // namespace haf::backend

#endif
