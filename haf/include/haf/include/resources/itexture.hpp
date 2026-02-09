HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_ITEXTURE_INTERFACE_INCLUDE_HPP
#define HAF_SCENE_ITEXTURE_INTERFACE_INCLUDE_HPP

#include <facil_math/include/vector2d.hpp>

import htypes;

namespace haf::res
{
class ITexture
{
protected:
    ~ITexture() = default;

public:
    virtual fmath::vector2du32 size() const = 0;
};
}  // namespace haf::res

#endif
