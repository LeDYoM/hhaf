#pragma once

#ifndef LIB_BACKEND_ITEXTURE_HPP
#define LIB_BACKEND_ITEXTURE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

namespace lib::backend
{
    class ITexture
    {
    public:
        ITexture() {}
        virtual ~ITexture() {}

        virtual vector2du32 size() const = 0;
    };
}

#endif
