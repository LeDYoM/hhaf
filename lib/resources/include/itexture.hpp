#pragma once

#ifndef HAF_SCENE_ITEXTURE_INTERFACE_INCLUDE_HPP
#define HAF_SCENE_ITEXTURE_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

namespace haf::scene
{
    class ITexture
    {
    public:
        virtual ~ITexture() {}
        virtual mtps::vector2du32 size() const = 0;
    };
}

#endif
