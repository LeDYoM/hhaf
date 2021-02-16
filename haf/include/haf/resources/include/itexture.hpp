#ifndef HAF_SCENE_ITEXTURE_INTERFACE_INCLUDE_HPP
#define HAF_SCENE_ITEXTURE_INTERFACE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

namespace haf::res
{
class ITexture
{
public:
    virtual ~ITexture() {}
    virtual mtps::vector2du32 size() const = 0;
};
}  // namespace haf::res

#endif
