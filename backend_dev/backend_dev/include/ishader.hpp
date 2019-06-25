#pragma once

#ifndef LIB_BACKEND_ISHADER_INTERFACE_INCLUDE_HPP
#define LIB_BACKEND_ISHADER_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>

#include "itexture.hpp"

namespace lib::backend
{
    class IShader
    {
    public:
        IShader() {}
        virtual ~IShader() {}

        virtual void setUniform(const str &name, vector2df v) = 0;
        virtual void setUniform(const str &name, ITexture *texture) = 0;

    };
}

#endif
