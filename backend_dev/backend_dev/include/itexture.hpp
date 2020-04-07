#pragma once

#ifndef HAF_BACKEND_ITEXTURE_HPP
#define HAF_BACKEND_ITEXTURE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

namespace haf::backend
{
class ITexture
{
public:
    ITexture() {}
    virtual ~ITexture() {}

    virtual mtps::vector2du32 size() const = 0;
};
} // namespace haf::backend

#endif
