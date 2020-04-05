#pragma once

#ifndef LIB_BACKEND_ISHADER_INTERFACE_INCLUDE_HPP
#define LIB_BACKEND_ISHADER_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>

#include "itexture.hpp"

namespace haf::backend
{
class IShader
{
public:
    IShader() {}
    virtual ~IShader() {}

    virtual void setUniform(const mtps::str &name, mtps::vector2df v) = 0;
    virtual void setUniform(const mtps::str &name, ITexture *texture) = 0;
};
} // namespace haf::backend

#endif
